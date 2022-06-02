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
// TODO: - Add shrinking

namespace rs::core {
	
	template<class T>
	class Array {
		
		
	public:
			
			Array(int initialSize = 2, bool resizable = true) : maximumSize (initialSize), currentPosition(0), resizable(resizable) {

				data = new T[initialSize];

			}
		
			~Array() {
				delete[] data;
			}
			
			T & operator[](int index) {
				return data[index];
			}
				
			void add(const T & value) {
				//Enlarge here
				if (currentPosition + 1 >= maximumSize && resizable == false) {
					throw std::runtime_error("[error] - cannot insert into a full non-resizable array");
				}
				data[currentPosition++] = value;
				if (currentPosition >= maximumSize) {
					enlarge();
				}
				
			}
			
			void remove() {
				data[currentPosition--].~T();
			}
			
			int size() {
				return currentPosition;
			}
		
			int containerSize() {
				return maximumSize;
			}
		
			void emplaceBack(Array<T> * arr) {
				this->resize(arr->size() + this->maximumSize);
				memmove( data + currentPosition , arr->data, arr->size() * sizeof(T));
			}
		
			
		
			
		
		protected:
			int maximumSize;
			int currentPosition;
			bool resizable;
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
		
			void resize(int newSize = 2) {
				/*
				 
				 There is a *new* kid on the block
				 
				*/
				//data = (T *)realloc(data, newSize * sizeof(T));
				
				T* newData = new T[newSize];
				memmove(newData, data, currentPosition * sizeof(T));
				delete [] data;
				data = newData;
			}
		
			
	};
	
};

#endif /* Array_hpp */
