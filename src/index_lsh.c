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

bool lsh_required_equal(struct id_record rhs, struct id_record lhs) {
	for (int i = 0; i < ID_SIZE; i ++) {
		if (rhs.uid[i] != lhs.uid[i]) {
			return false;
		}
	}
	return true;
}

struct index_lsh init_lsh(const char * filename, size_t hash_size, size_t dimensions) {
	int fd = _open_file(filename);
	DATA_TYPE * projections = NULL;
	
	if (_file_size(fd) == 0) {
		// generate projections
		projections = calloc(dimensions * hash_size, sizeof(DATA_TYPE));
		generate_planes(projections, dimensions * hash_size);
	}
	
	struct index_lsh _init_alloc = {
		init_lsh_allocator_pre_open(fd, projections, hash_size * dimensions * sizeof(DATA_TYPE))
	};
	
	if (projections != NULL) {
		free(projections);
		printf("%i\n", (int)pow(2, hash_size));
		lsh_allocator_alloc(&_init_alloc.allocator, (int)pow(2, hash_size));
	}
	
	return _init_alloc;
}

void lsh_add(struct index_lsh * index, struct id_record * uid, struct dynamic_ndarray * value) {
	hash(<#float *planes#>, <#struct ndarray_shape planes_shape#>, value->data, value->shape);
	
	lsh_allocator_add(index->allocator, <#size_t block_no#>, <#struct id_record *value#>)
	
}

// shrinkFLATION Shrinking to a format from the latent space of autoencoder transformers to a intermediate optimised ndimensional vector
