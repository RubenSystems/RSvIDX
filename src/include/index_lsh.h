//
//  index_lsh.h
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 06/01/2023.
//

#ifndef index_lsh_h
#define index_lsh_h

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "config.h"
#include "record.h"
#include "operators.h"
#include "dynamic_array.h"
#include "hash_table.h"

#include "../../smac-alloc/src/include/allocator.h"


#define LSH_BLOCK_SIZE 10


struct index_lsh {
	struct hash_table mapper;
	struct smac_allocator storage;
	size_t hash_size, dimensions;
	pthread_mutex_t mutex;
};

struct index_lsh init_lsh(const char * mapping_filename, const char * data_filename, size_t hash_size, size_t dimensions);

struct index_lsh * init_lsh_heap(const char * mapping_filename, const char * data_filename, size_t hash_size, size_t dimensions);

void lsh_add(struct index_lsh *, struct id_record * uid, DATA_TYPE * value);

void lsh_custom_hash_add(struct index_lsh *, struct id_record * uid, DATA_TYPE * value, size_t hash);

size_t lsh_get(struct index_lsh *, DATA_TYPE * value, size_t max_buffer_size, void * result_buffer);

void lsh_delete(struct index_lsh *, struct id_record * id_to_delete);

void lsh_delete_helper(struct index_lsh * index, char * id_to_delete );

void lsh_free(struct index_lsh *);

void lsh_heap_free(struct index_lsh *);

unsigned long lsh_get_uid_from_result(struct index_lsh * lsh, void * result, size_t index, char * uid);

void lsh_get_vector_from_result(struct index_lsh * lsh, void * result, size_t index, DATA_TYPE * vector);

void debug_print(struct index_lsh *);

#endif /* index_lsh_h */
