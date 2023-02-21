//
//  index_lsh.c
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 06/01/2023.
//

#include "include/index_lsh.h"
#include <math.h>

#include "../smac-alloc/src/include/palloc.h"


/*
 Specalisation functions
 */
static bool lsh_required_equal(void * rhs, void * lhs) {
	return strcmp(((struct id_record *)rhs)->uid, ((struct id_record *)lhs)->uid) == 0;
}


/*
 Concrete stuff
 */

static size_t __lsh_jump_size(struct index_lsh * index){
	return sizeof(struct id_record) + sizeof(DATA_TYPE) * index->dimensions;
}

struct index_lsh init_lsh(const char * mapping_filename, const char * data_filename, size_t hash_size, size_t dimensions) {
	int fd = _open_file(data_filename);
	DATA_TYPE * projections = NULL;
	
	if (_file_size(fd) == 0) {
		// generate projections
		projections = calloc(dimensions * hash_size, sizeof(DATA_TYPE));
		generate_planes(projections, dimensions * hash_size);
	}
	
	struct index_lsh _init_alloc = {
		.mapper = init_phash_table(mapping_filename),
		.storage = init_allocator(fd, projections, hash_size * dimensions * sizeof(DATA_TYPE), sizeof(struct id_record) + (sizeof(DATA_TYPE) * dimensions), LSH_BLOCK_SIZE),
		.hash_size = hash_size,
		.dimensions = dimensions,
		.mutex = PTHREAD_MUTEX_INITIALIZER
	};
	
	if (projections != NULL) {
		free(projections);
	}
	
	return _init_alloc;
}

struct index_lsh * init_lsh_heap(const char * mapping_filename, const char * data_filename, size_t hash_size, size_t dimensions) {
	struct index_lsh * index = malloc(sizeof(struct index_lsh));
	*index = init_lsh(mapping_filename, data_filename, hash_size, dimensions);
	return index;
}

void lsh_add(struct index_lsh * index, struct id_record * _uid, DATA_TYPE * value, size_t value_size) {
	void * rec = malloc(sizeof(struct id_record) + sizeof(DATA_TYPE) * value_size);
	memmove(rec, _uid->uid, ID_SIZE * sizeof(char));
	memmove(rec + ID_SIZE * sizeof(char), value, value_size * sizeof(DATA_TYPE));
	// Don't transpose its toooo slowwww
	struct ndarray_shape planes_shape = {
		index->dimensions,
		index->hash_size
	};
	
	struct ndarray_shape value_shape = {
		1,
		value_size,
	};

	size_t hash_val = hash((DATA_TYPE *)smac_pre_data(&index->storage), planes_shape, value, value_shape);
	size_t get_value;
	pthread_mutex_lock(&index->mutex);
	enum bucket_operation_response get_response = hash_table_get(&index->mapper, hash_val, &get_value);
	if (get_response == BUCKET_DOES_NOT_EXIST) {
		// no block in datastore to represent bucket.
		size_t block_index = smac_allocate(&index->storage, 1);
		smac_add(&index->storage, block_index, rec);
		hash_table_add(&index->mapper, hash_val, block_index);
	} else {
		// blocke in datastore to respresent bucket.
		smac_add(&index->storage, get_value, rec);
	}
	pthread_mutex_unlock(&index->mutex);
	free(rec);
}


size_t lsh_get(struct index_lsh * index, DATA_TYPE * value, size_t value_size, size_t max_buffer_size, void * result_buffer) {
	struct ndarray_shape planes_shape = {
		index->dimensions,
		index->hash_size,
	};
	
	struct ndarray_shape value_shape = {
		1,
		value_size,
	};

	size_t hash_val = hash((DATA_TYPE *)smac_pre_data(&index->storage), planes_shape, value, value_shape);
	size_t get_value;
	pthread_mutex_lock(&index->mutex);
	enum bucket_operation_response get_response = hash_table_get(&index->mapper, hash_val, &get_value);
	size_t res_value = 0;
	if (get_response != BUCKET_DOES_NOT_EXIST) {
		res_value = smac_get(&index->storage, get_value, max_buffer_size, 0, result_buffer);
	}
	pthread_mutex_unlock(&index->mutex);
	return res_value;
}

void lsh_delete(struct index_lsh * index, struct id_record * id_to_delete) {
	pthread_mutex_lock(&index->mutex);
	for (size_t bucket = 0; bucket < index->mapper.allocated; bucket ++) {
		if (buckets(&index->mapper)[bucket].status == BUCKET_OCCUPIED) {
			int64_t value = buckets(&index->mapper)[bucket].value;
			smac_delete(&index->storage, value, id_to_delete, lsh_required_equal);
			// TODO: - CHECK IF BUCKET SIZE == 0 and DELETE REFERENCE. 
		}
	}
	pthread_mutex_unlock(&index->mutex);
}

void lsh_delete_helper(struct index_lsh * index, char * id_to_delete ) {
	struct id_record rec;
	strncpy(rec.uid, id_to_delete, ID_SIZE - 1);
	lsh_delete(index, &rec);
}

void lsh_free(struct index_lsh * index) {
	smac_free(&index->storage);
	hash_table_free(&index->mapper);
}


void lsh_heap_free(struct index_lsh * index) {
	lsh_free(index);
	free(index);
}

//Int because it is boxed at 32 bytes
unsigned long lsh_get_uid_from_result(struct index_lsh * lsh, void * result, size_t index, char * uid) {
	
	size_t jump_size = __lsh_jump_size(lsh);
	
	memmove(uid, result + jump_size * index, sizeof(struct id_record));
	return strnlen(result + jump_size * index, ID_SIZE);
}

void lsh_get_vector_from_result(struct index_lsh * lsh, void * result, size_t index, DATA_TYPE * vector) {
	size_t jump_size = __lsh_jump_size(lsh);
	
	memmove(vector, result + jump_size * index + sizeof(struct id_record), sizeof(DATA_TYPE) * lsh->dimensions);
}



void debug_print(struct index_lsh * index) {
	static int max_buffer_size = 200;
	void * buffer = malloc(max_buffer_size * (sizeof(struct id_record) + sizeof(DATA_TYPE) * index->dimensions));
	unsigned long size = 0;
	char id[ID_SIZE];
	
	for (size_t i = 0; i < index->mapper.allocated; i ++) {
		if (buckets(&index->mapper)[i].status == BUCKET_OCCUPIED) {
			size_t value = 0;
			
			hash_table_get(&index->mapper, i, &value);
			
//			size_t res_size = lsh_allocator_get(&index->storage, value, max_buffer_size, buffer);
			size_t res_size = smac_get(&index->storage, value, max_buffer_size, 0, buffer);
			printf("Hash: %zu Bucket: %zu Size:%zu\n",i, value, res_size);
			for (size_t c = 0; c < res_size; c++) {
				
				lsh_get_uid_from_result(index, buffer, c, id);
				printf("\t%s\n", id);
			}
			size += res_size;
		}
	}
	printf("TOTAL_RECORDS: %lu \n", size);
	free(buffer);
}

// shrinkFLATION Shrinking to a format from the latent space of autoencoder transformers to an intermediate optimised ndimensional vector
