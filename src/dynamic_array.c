//
//  dynamic_array.c
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 03/01/2023.
//

#include "include/dynamic_array.h"
#include <stdlib.h>
#include <string.h>
struct dynamic_ndarray init_dynamic_ndarray(ROW_COLUMN_TYPE rows, ROW_COLUMN_TYPE columns, DATA_TYPE * data) {
	struct dynamic_ndarray _init_arr = {
		{
			.rows = rows,
			.columns = columns,
		},
		.data = calloc(rows * columns, sizeof(ROW_COLUMN_TYPE))
	};
	if (data != NULL) {
		memmove(_init_arr.data, data, rows * columns * sizeof(DATA_TYPE));
	}
	
	return _init_arr;
}

void free_dynamic_ndarray(struct dynamic_ndarray * array) {
	free(array);
}

DATA_TYPE * dynamic_ndarray_get(struct dynamic_ndarray * array, ROW_COLUMN_TYPE row, ROW_COLUMN_TYPE column) {
	return &array->data[column + (row * array->shape.columns)];
}
