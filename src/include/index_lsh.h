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

#include "config.h"
#include "id_record.h"
#include "operators.h"
#include "dynamic_array.h"
#include "hash_table.h"

#include "../../smac-alloc/src/include/allocator.h"


bool lsh_required_equal(struct id_record rhs, struct id_record lhs);

TYPED_ALLOCATOR_DEF(lsh, struct id_record, 10);

struct index_lsh {
	struct hash_table mapper;
	struct lsh_allocator storage;
	size_t hash_size, dimensions;
	
};

struct index_lsh init_lsh(const char * mapping_filename, const char * data_filename, size_t hash_size, size_t dimensions);

struct index_lsh * init_lsh_heap(const char * mapping_filename, const char * data_filename, size_t hash_size, size_t dimensions);

void lsh_add(struct index_lsh *, struct id_record * uid, DATA_TYPE * value, size_t value_size);

size_t lsh_get(struct index_lsh *, DATA_TYPE * value, size_t value_size, size_t max_buffer_size, struct id_record * result_buffer);

void lsh_delete(struct index_lsh *, struct id_record * id_to_delete);

void lsh_delete_helper(struct index_lsh * index, char * id_to_delete );

void lsh_free(struct index_lsh *);

void lsh_heap_free(struct index_lsh *);

#endif /* index_lsh_h */
