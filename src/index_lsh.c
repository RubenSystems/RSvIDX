//
//  index_lsh.c
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 06/01/2023.
//

#include "include/index_lsh.h"
#include <math.h>

#include "../smac-alloc/src/include/palloc.h"

TYPED_ALLOCATOR_IMPL(lsh, struct id_record, 10);

/*
 Specalisation functions
 */
bool lsh_required_equal(struct id_record rhs, struct id_record lhs) {
	for (int i = 0; i < ID_SIZE; i ++) {
		if (rhs.uid[i] != lhs.uid[i]) {
			return false;
		}
	}
	return true;
}


/*
 Concrete stuff
 */

struct index_lsh init_lsh(const char * mapping_filename, const char * data_filename, size_t hash_size, size_t dimensions) {
	int fd = _open_file(data_filename);
	DATA_TYPE * projections = NULL;
	
	if (_file_size(fd) == 0) {
		// generate projections
		projections = calloc(dimensions * hash_size, sizeof(DATA_TYPE));
		generate_planes(projections, dimensions * hash_size);
	}
	
	struct index_lsh _init_alloc = {
		init_phash_table(mapping_filename),
		init_lsh_allocator_pre_open(fd, projections, hash_size * dimensions * sizeof(DATA_TYPE)),
		hash_size,
		dimensions
	};
	
	if (projections != NULL) {
		free(projections);
	}
	
	return _init_alloc;
}

void lsh_add(struct index_lsh * index, struct id_record * uid, struct dynamic_ndarray * value) {
	
	struct ndarray_shape planes_shape = {
		index->hash_size,
		index->dimensions
	};

	size_t hash_val = hash((DATA_TYPE *)index->storage.raw_data, planes_shape, value->data, value->shape);
	size_t get_value;
	enum bucket_operation_response get_response = hash_table_get(&index->mapper, hash_val, &get_value);
	if (get_response == BUCKET_DOES_NOT_EXIST) {
		// no block in datastore to represent bucket.
		size_t block_index = lsh_allocator_alloc(&index->storage, 1);
		lsh_allocator_add(&index->storage, block_index, uid);
		hash_table_add(&index->mapper, hash_val, block_index);
	} else {
		// blocke in datastore to respresent bucket.
		lsh_allocator_add(&index->storage, get_value, uid);
	}
}


size_t lsh_get(struct index_lsh * index, struct dynamic_ndarray * value, size_t max_buffer_size, struct id_record * result_buffer) {
	struct ndarray_shape planes_shape = {
		index->hash_size,
		index->dimensions
	};
	
	size_t hash_val = hash((DATA_TYPE *)index->storage.raw_data, planes_shape, value->data, value->shape);
	
	size_t get_value;
	enum bucket_operation_response get_response = hash_table_get(&index->mapper, hash_val, &get_value);
	if (get_response == BUCKET_DOES_NOT_EXIST) {
		return 0;
	} else {
		return lsh_allocator_get(&index->storage, get_value, max_buffer_size, result_buffer);
	}
}

void lsh_delete(struct index_lsh * index, struct id_record * id_to_delete) {
	
	for (size_t bucket = 0; bucket < index->mapper.allocated; bucket ++) {
		if (buckets(&index->mapper)[bucket].status == BUCKET_OCCUPIED) {
			int64_t value = buckets(&index->mapper)[bucket].value;
			lsh_allocator_delete(&index->storage, value, id_to_delete);
			// TODO: - CHECK IF BUCKET SIZE == 0 and DELETE REFERENCE. 
		}
	}
}


// shrinkFLATION Shrinking to a format from the latent space of autoencoder transformers to an intermediate optimised ndimensional vector
