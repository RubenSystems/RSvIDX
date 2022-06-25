//
//  DataStore.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 05/06/2022.
//

#ifndef DataStore_hpp
#define DataStore_hpp

#include <stdio.h>
#include <string>
#include "ID.hpp"
#include "Math.hpp"
#include "../Output.h"

namespace rsvidx {
	/*
	 This is ugly and coupled too tightly to vector
	 */
	struct Record {

		Record () = default;
		
		Record(const ID & id, const std::string & data, int vectorsize, math::Vector::v_val * vec):
			id (id), data(data) {
				size.data = (int)data.size();
				size.vector = vectorsize;
				setVector(vectorsize, vec);
				
		}
		
		void setVector(int vectorsize, math::Vector::v_val * vec) {
			allocateVector(vectorsize);
			memmove(vector, vec, sizeof(math::Vector::v_val) * vectorsize);
		}
		
		void allocateVector(int size) {
			vector = new math::Vector::v_val [size];
		}
		
		~Record() {
			delete [] vector;
		}
		
		ID id;

		struct {
			int data;
			int vector;
		} size;
		
		std::string data;
		math::Vector::v_val * vector = nullptr;
	};
	
	class DataStore {
		public:
			
			DataStore(const std::string & );
		
			void set(Record &);
		
			void get(const ID &, Record &);
		
			void remove(const ID &);
		
		private:
			std::string foldername;
			
	};
}

#endif /* DataStore_hpp */
