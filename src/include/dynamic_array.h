//
//  dynamic_array.h
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 03/01/2023.
//

#ifndef dynamic_array_h
#define dynamic_array_h

#include <stdio.h>
#include "config.h"
#include "ndarray.h"

struct dynamic_ndarray {
	struct ndarray_shape shape;
	DATA_TYPE * data;
};

struct dynamic_ndarray init_dynamic_ndarray(ROW_COLUMN_TYPE rows, ROW_COLUMN_TYPE columns, DATA_TYPE * data);

void free_dynamic_ndarray(struct dynamic_ndarray * array);

DATA_TYPE * dynamic_ndarray_get(struct dynamic_ndarray * array, ROW_COLUMN_TYPE row, ROW_COLUMN_TYPE column);

#endif /* dynamic_array_h */
