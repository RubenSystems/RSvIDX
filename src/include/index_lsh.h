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

#include "../../smac-alloc/src/include/allocator.h"


bool lsh_required_equal(struct id_record rhs, struct id_record lhs);

TYPED_ALLOCATOR_DEF(lsh, struct id_record, 10);

struct index_lsh {
	struct lsh_allocator allocator;
};

struct index_lsh init_lsh(const char * filename, size_t hash_size, size_t dimensions) ;

void lsh_add(struct index_lsh *, struct id_record * uid, struct dynamic_ndarray * value);
//
//void lsh_get();
//
//void lsh_delete();

#endif /* index_lsh_h */
