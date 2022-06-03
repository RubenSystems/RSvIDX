//
//  ID.h
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 03/06/2022.
//

#ifndef ID_h
#define ID_h


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
	
	bool operator == (const ID & rhs) {
		for (int i = 0; i < idsize; i ++) {
			if (data[i] != rhs.data[i]) {
				return false;
			}
		}
		return true;
	}
	
	char data[idsize];
};


#endif /* ID_h */
