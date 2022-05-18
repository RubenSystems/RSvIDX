//
//  Array.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//

#ifndef Array_hpp
#define Array_hpp

#include <stdlib.h>
#include "../Output.h"


// TODO: - Check allocations for errors

namespace rs::core {
	
	template<class T>
	class Array {
		
		
		public:
		
			Array(int initialSize = 2) : maximumSize (initialSize), currentPosition(0) {
				data = (T *)calloc(initialSize, sizeof(T));
			}
		
			~Array() {
				delete[] data;
			}
			
			T & operator[](int index) {
				return data[index];
			}
				
			void add(const T & value) {
				//Enlarge here
				
				data[currentPosition++] = value;
				if (currentPosition >= maximumSize) {
					enlarge();
				}
				
			}
			
			void remove() {
				data[currentPosition--].~T();
				
			}
			
			int size() {
				return (int)currentPosition;
			}
		
		private:
			int maximumSize;
			int currentPosition;
			T * data;
			
			const static int enlargementFactor = 2;
		
			void enlarge() {
				maximumSize *= enlargementFactor;
				resize(maximumSize);
			}
		
			void reduce() {
				maximumSize /= enlargementFactor;
				resize(maximumSize);
			}
		
			void resize(int newSize) {
				data = (T *)realloc(data, newSize * sizeof(T));
			}
	};
	
};

#endif /* Array_hpp */
