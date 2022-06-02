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
	const static int idsize = 8;
	
	ID () {}
	
	ID (const std::string & string) {
		const char * newData = string.c_str();
		memmove(data, newData, idsize);
	}
	
	ID(const ID & copy) {
		memcpy(data, copy.data, idsize);
	}
	
	char data[idsize];
};

#define LSH_ID_TYPE ID

#endif /* config_h */
