//
//  Array.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//

#ifndef Array_hpp
#define Array_hpp

#include <stdlib.h>
#include <cstring>
#include "../Output.h"
#include <system_error>



// TODO: - Check allocations for errors
// TODO: - Add shrinking

namespace core {
	
	template<class T>
	class Array {
		
		
	public:
			
			Array(int initialSize = 2, bool resizable = true) : maximumSize (initialSize), currentPosition(0), resizable(resizable) {

				data = new T[initialSize];

			}
		
			Array(T * buffer, int start, int end, bool resizable = true) :
				maximumSize((end - start) + 2), currentPosition(end - start), resizable(resizable) {
				data = new T[this->maximumSize];
					
					
				memmove(data, &(buffer[start]), (end - start) * sizeof(T));
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
		
			void insert(unsigned int at, const T & value) {
				if (currentPosition + 1 >= maximumSize && resizable == false) {
					throw std::runtime_error("[error] - cannot insert into a full non-resizable array");
				}
				currentPosition++;
				
				memmove(&(data[at + 1]), &(data[at]), (currentPosition - at - 1) * sizeof(T));
				data[at] = value;
				
				if (currentPosition >= maximumSize) {
					enlarge();
				}
			}
			
			void remove() {
				data[currentPosition--].~T();
				if (currentPosition < maximumSize / enlargementFactor) {
					reduce();
				}
			}
		
			void remove(unsigned int index) {
				data[index].~T();
				memmove(&(data[index]), &(data[index + 1]), (currentPosition - index - 1) * sizeof(T));
				currentPosition --;
				if (currentPosition < maximumSize / enlargementFactor) {
					reduce();
				}
			}
			
			int size() {
				return currentPosition;
			}
		
			int containerSize() {
				return maximumSize;
			}
		
			void emplaceBack(Array<T> * arr) {
				this->resize(arr->size() + maximumSize);
				memmove( &(data[currentPosition]) , arr->data, arr->size() * sizeof(T));
				this->currentPosition += arr->size();
			}
		
		protected:
			int maximumSize;
			int currentPosition;
			bool resizable;
			T * data;
			
			const static int enlargementFactor = 2;
		
			void enlarge() {
				resize(maximumSize * enlargementFactor);
			}
		
			void reduce() {
				resize(maximumSize / enlargementFactor);
			}
		
			void resize(int newSize = 2) {
				/*
				 There is a *new* kid on the block
				*/
				//data = (T *)realloc(data, newSize * sizeof(T));
				maximumSize = newSize;
				T* newData = new T[newSize];
				memmove(newData, data, currentPosition * sizeof(T));
				delete [] data;
				data = newData;
				
			}
		
			
	};
	
};

#endif /* Array_hpp */
