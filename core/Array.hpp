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


namespace rs::core {
	
	template<class T>
	class Array {
		
		
		public:
		
			Array(int initialSize = 2) : maximumSize (initialSize), currentPosition(0) {
				data = (T *)malloc(sizeof(T) * initialSize);
			}
			
			T & operator[](int index) {
				return data[index];
			}
				
			void add(const T & value) {
				//Enlarge here
				
				if (currentPosition > maximumSize) {
					enlarge();
				}
				data[currentPosition++] = value;
				
			}
			
			void remove() {
				currentPosition --;
				//Reduce here
			}
			
			int size() {
				return currentPosition;
			}
		
		private:
			int maximumSize;
			int currentPosition;
			T * data;
			
			const static int enlargementFactor = 2;
		
			void enlarge() {
				out("[realloc]");
				maximumSize *= enlargementFactor;
				data = (T *)realloc(data, maximumSize);
			}
		
			void reduce() {
				maximumSize /= enlargementFactor;
				data = (T *)realloc(data, maximumSize);
			}
	};
	
};

#endif /* Array_hpp */
