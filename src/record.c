//
//  record.c
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 02/02/2023.
//

#include <stdlib.h>
#include <string.h>

#include "include/record.h"

struct record * init_record(struct id_record * uid, DATA_TYPE * data, size_t data_size) {
	void * _init_rec = malloc(sizeof(struct id_record) + data_size);
	memmove(_init_rec, uid, sizeof(struct id_record));
	memmove(_init_rec + sizeof(struct id_record), data, data_size);
	return _init_rec;
}
