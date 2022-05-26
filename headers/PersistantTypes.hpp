//
//  PersistantTypes.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 23/05/2022.
//

#ifndef PersistantTypes_hpp
#define PersistantTypes_hpp

#include <stdio.h>
//#include <fstream>
#include "StandardDiskOperator.hpp"
#include "../core/Array.h"

#include "../Output.h"

namespace rs::rsvidx {
	
	template <class T>
	class PersistantArray : public core::Array<T> {
		public:
			PersistantArray(std::string n_filename) : filename(std::string(n_filename + ".rsarray")),  core::Array<T>(2, true) {
			}
		
			void save(){
				StateMap state = {this->currentPosition, this->maximumSize, this->resizable};
				
				StandardDiskOperator file = StandardDiskOperator();
				file.open(filename.c_str(), DiskOperator::OpenType::WRITE);
				file.seek(0);
				file.write(&state, sizeof(StateMap));
				file.seek(sizeof(StateMap));
				file.write(this->data, this->currentPosition * sizeof(T));
				file.close();

				
			}
		
			void load() {
				StateMap state;

				StandardDiskOperator file = StandardDiskOperator();
				file.open(filename.c_str(), DiskOperator::OpenType::READ);
				file.seek(0);
				file.read(&state, sizeof(StateMap));
				
				this->resize(state.maximumSize);
				this->currentPosition = state.currentPosition;
				this->maximumSize = state.maximumSize;
				this->resizable = state.resizable;
				
				file.seek(sizeof(StateMap));
				file.read(this->data, state.currentPosition * sizeof(T));
				file.close();

			}
		
			
		private:
			std::string filename;
				
			struct StateMap {
				int currentPosition;
				int maximumSize;
				bool resizable;
			};
	};
	
	template <class T>
	class PersistantMultimap {
		public:
			PersistantMultimap(std::string n_foldername, int n_size): foldername(n_foldername), size((n_size * 8) << 2) {
				buckets = new PersistantArray<T>* [this->size];
				memset(buckets, 0, sizeof(PersistantArray<T> *) * (this->size));
			}
		
			~PersistantMultimap() {
				
				for(int i = 0; i < size; i++){
					if (buckets[i] != NULL){
						buckets[i]->save();
						delete buckets[i];
					}
				}
				delete[] buckets;
			}
			
			void add(unsigned int index, const T & data) {
				PersistantArray<T> * bucket;
				if (buckets[index] == 0) {
					std::string path = foldername + std::to_string(index);
					bucket = new PersistantArray<T>(path);
					buckets[index] = bucket;
				} else {
					bucket = buckets[index];
				}
				bucket->add(data);
				
			}
			
		private:
			int size;
			std::string foldername;
			PersistantArray<T> ** buckets;
	};
	
}

#endif /* PersistantTypes_hpp */
