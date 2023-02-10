//
//  id_record.h
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 06/01/2023.
//

#ifndef id_record_h
#define id_record_h

#include <stdbool.h>
#include "config.h"

struct id_record {
	char uid[ID_SIZE];
};

struct record {
	struct id_record 	uid;
	DATA_TYPE * 		data;
};

#include <string.h>
struct record * init_record(struct id_record * uid, DATA_TYPE * data, size_t data_size);


#endif /* id_record_h */
