//
//  operators.cpp
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 03/01/2023.
//

#include "include/operators.h"
#include <future>

void __dot_cell(DATA_TYPE * sum, DATA_TYPE * a, ndarray_shape * a_shape, DATA_TYPE * b, ndarray_shape * b_shape, ROW_COLUMN_TYPE row, ROW_COLUMN_TYPE column) {
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
