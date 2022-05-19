//
//  HashArray.h
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 18/05/2022.
//

#ifndef HashArray_h
#define HashArray_h

#include "Array.h"

namespace rs::core {
	
	template <class T>
	class HashArray : public Array<Array<T>> {
		public:
			HashArray(int size) : Array<Array<T>>(size, false) {}
		
		
			void add(int hash, const T & value) {
				Array<T> & array = this->operator[](hash);
				
				
				if (array.containerSize() == 0) {
				}
				out(array.containerSize());
				array.add(value);
			}
	};
	
}

#endif /* HashArray_h */
