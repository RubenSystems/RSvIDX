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
#include "Math.hpp"

#include "../Output.h"

namespace rs::rsvidx {
	
	template <class T>
	class PersistantArray : public core::Array<T> {
		public:
			PersistantArray() : core::Array<T>(2, true) {
			}
		
			void save(const std::string & filename){
				StateMap state = {this->currentPosition, this->maximumSize, this->resizable};
				
				StandardDiskOperator file = StandardDiskOperator();
				file.open((filename + ".rsarray").c_str(), DiskOperator::OpenType::WRITE);
				file.seek(0);
				file.write(&state, sizeof(StateMap));
				file.seek(sizeof(StateMap));
				file.write(this->data, this->currentPosition * sizeof(T));
				file.close();

				
			}
		
			void load(const std::string & filename) {
				StateMap state;

				StandardDiskOperator file = StandardDiskOperator();
				file.open((filename + ".rsarray").c_str(), DiskOperator::OpenType::READ);
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
				
			struct StateMap {
				int currentPosition;
				int maximumSize;
				bool resizable;
			};
	};
	
	template <class T>
	class PersistantMultimap {
		public:
		
			PersistantMultimap(int n_size): size((n_size * 8) << 2) {
				buckets = new PersistantArray<T>* [this->size];
				memset(buckets, 0, sizeof(PersistantArray<T> *) * (this->size));
			}
		
			~PersistantMultimap() {
				
				for(int i = 0; i < size; i++){
					if (buckets[i] != NULL){
						if (foldername != "") {
							buckets[i]->save(foldername + std::to_string(i));
						}
						
						delete buckets[i];
					}
				}
				delete[] buckets;
			}
			
			void add(unsigned int index, const T & data) {
				loadBucket(index);
				PersistantArray<T> * bucket = buckets[index];
				bucket->add(data);
				
			}
		
			//This may look bad but it gets cleaned up later
			core::Array<T> * get(unsigned int index) {
				loadBucket(index);
				return buckets[index];
			}
		
			virtual void setFoldername(const std::string & foldername) {
				this->foldername = foldername;
			}
			
		protected:
			std::string foldername = "";
			
		private:
			int size;
			PersistantArray<T> ** buckets;
			
		
			/*
			 Performs cache op too so watch out
			 */
			void loadBucket(unsigned int index) {
				if (foldername == "") {
					throw std::runtime_error("[SAVE] - must specify a foldername in order to save/load");
				}
				
				PersistantArray<T> * bucket;
				
				if (buckets[index] == 0) {
					std::string path = foldername + std::to_string(index);
					bucket = new PersistantArray<T>();
					bucket->load(path);
					buckets[index] = bucket;
				}
			}
	};
	
	class PersistantMatrix : public rs::math::Matrix {
		public :
			PersistantMatrix(unsigned int n_rows, unsigned int n_columns) : rs::math::Matrix(n_rows, n_columns) {
				memset(data, 0, sizeof(m_val) * n_rows * n_columns);
			}
		
			void load(const std::string & filename) {
				StandardDiskOperator file = StandardDiskOperator();
				
				file.open((filename + ".rsmatrix").c_str(), DiskOperator::OpenType::READ);
				file.seek(0);
				file.read(data, sizeof(m_val) * rows * columns);
				file.close();
			}
			
			void save(const std::string & filename) {
				StandardDiskOperator file = StandardDiskOperator();
				
				file.open((filename + ".rsmatrix").c_str(), DiskOperator::OpenType::WRITE);
				file.seek(0);
				file.write(data, sizeof(m_val) * rows * columns);
				file.close();
			}

	};
	
}

#endif /* PersistantTypes_hpp */
