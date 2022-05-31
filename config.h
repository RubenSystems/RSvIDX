//
//  config.h
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 20/05/2022.
//

#ifndef config_h
#define config_h

#define LSH_INDEXING_TYPE unsigned char

struct ID {
	ID () {}
	
	ID (const std::string & string) {
		const char * newData = string.c_str();
		memmove(data, newData, 10);
	}
	
	ID(const ID & copy) {
		memcpy(data, copy.data, 10);
	}
	
	char data[10];
};

#define LSH_ID_TYPE ID

#endif /* config_h */
