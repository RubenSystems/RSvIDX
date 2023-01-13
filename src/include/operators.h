//
//  operators.hpp
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 03/01/2023.
//

#ifndef operators_hpp
#define operators_hpp

#include <stdio.h>
#include "ndarray.h"
#include "config.h"
#include <stdint.h>

enum raw_dot_produt_result {
	RDP_SUCCESS,
	RDP_WRONG_SIZE
};

int __seed_random(void);

enum raw_dot_produt_result __raw_dot_product(DATA_TYPE * a, struct ndarray_shape a_shape, DATA_TYPE * b, struct ndarray_shape b_shape, DATA_TYPE * res, struct ndarray_shape res_shape);

void generate_planes(DATA_TYPE * res, size_t size);

HASH_SIZE hash(DATA_TYPE * planes, struct ndarray_shape planes_shape, DATA_TYPE * a, struct ndarray_shape a_shape) ;

#endif /* operators_hpp */
