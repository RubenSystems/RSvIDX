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

struct index_lsh init_lsh(const char * mapping_filename, const char * data_filename, size_t hash_size, size_t dimensions) ;

void lsh_add(struct index_lsh *, struct id_record * uid, struct dynamic_ndarray * value);

size_t lsh_get(struct index_lsh *, struct dynamic_ndarray * value, size_t max_buffer_size, struct id_record * result_buffer);


#endif /* index_lsh_h */
