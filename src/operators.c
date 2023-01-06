//
//  operators.cpp
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 03/01/2023.
//

#include "include/operators.h"

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


int __seed_random() {
	static bool random_seeded = false;
	if (random_seeded) {
		return 1;
	}
	srand((unsigned int)time(0));
	return 0;
}

void __dot_cell(DATA_TYPE * sum, DATA_TYPE * a, struct ndarray_shape * a_shape, DATA_TYPE * b, struct ndarray_shape * b_shape, ROW_COLUMN_TYPE row, ROW_COLUMN_TYPE column) {
	*sum = 0;
	for(unsigned int ab_index = 0; ab_index <= a_shape->rows; ab_index ++) {
		*sum += a[ab_index + (row * a_shape->columns)] * b[column + (ab_index * b_shape->columns)];
	}
}


enum raw_dot_produt_result __raw_dot_product(DATA_TYPE * a, struct ndarray_shape a_shape, DATA_TYPE * b, struct ndarray_shape b_shape, DATA_TYPE * res, struct ndarray_shape res_shape) {
	if (a_shape.rows != res_shape.rows || b_shape.columns != res_shape.columns) {
		return RDP_WRONG_SIZE;
	}
	DATA_TYPE sum = 0;
	for (unsigned int row = 0; row < res_shape.rows; row ++) {
		for (unsigned int column = 0; column < res_shape.columns; column++) {
			__dot_cell(&sum, a, &a_shape, b, &b_shape, row, column);
			res[column + (row * res_shape.columns)] = sum;
		}
	}
	return RDP_SUCCESS;
}

void generate_planes(DATA_TYPE * res, struct ndarray_shape res_shape){
	for (unsigned int index = 0; index < res_shape.columns * res_shape.rows; index ++) {
		res[index] = (2 *(float)rand() / RAND_MAX) - 1;
	}
}

HASH_SIZE hash(DATA_TYPE * planes, struct ndarray_shape planes_shape, DATA_TYPE * a, struct ndarray_shape a_shape) {
	if (a_shape.columns != 1) {
		return -1;
	}
	DATA_TYPE * raw_hash = calloc(planes_shape.rows, sizeof(DATA_TYPE));
	struct ndarray_shape hash_shape = {planes_shape.rows, 1};
	__raw_dot_product(planes, planes_shape, a, a_shape, raw_hash, hash_shape);
	
	HASH_SIZE hash = 0;
	for (unsigned int i = 0; i < hash_shape.rows; i ++) {
		printf("%f\n", raw_hash[i]);
		hash += raw_hash[i] > 0 ? (1 << i) : 0;
	}
	free(raw_hash);
	return hash;
}
