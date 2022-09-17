//
//  LSHIndex.hpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 05/09/2022.
//

#ifndef LSHIndex_hpp
#define LSHIndex_hpp

#include <stdio.h>
#include"../persistance/PMultiMap.h"
#include"../persistance/PMatrix.h"
#include "../math/Vector.hpp"
#include "../math/Matrix.hpp"
#include "../math/Operators.hpp"

#include <math.h>
#include <future>
#include <vector>
#include <unordered_set>


#define IDSIZE 8

namespace rsvidx {
	struct LSHRecord {
		LSHRecord() {
			memset(id, 0, IDSIZE - 1);
		}
		
		LSHRecord(const char * string) {
			strncpy(id, string, IDSIZE - 1);
		}
		
		bool operator == (const LSHRecord & rhs) const {
			return strcmp(id, rhs.id) == 0;
		}
		
		char 	id [IDSIZE];
	};
}

namespace std {
	template <>
	struct std::hash<rsvidx::LSHRecord> {
		
		
		size_t operator()(const rsvidx::LSHRecord & record) const {
			unsigned long int hash;
			int c;
			
			hash = 5381;
			for (int i = 0; i < IDSIZE; i ++) {
				if (record.id[i] == 0) {
					break;
				}
				c = record.id[i];
				hash = ((hash << 5) + hash) + c;
			}
			return hash;
		}
	};
}


namespace rsvidx {
	

	
	
	template <int _Size, int _BucketSize>
	struct LSHTable {
		
		LSHTable() {
			
		}
		
		void add(const LSHRecord & rec, unsigned long index) {
			if (index > _Size) {
				throw std::runtime_error("[LSH] - out of bounds");
			} else if (sizes[index] + 1 > _BucketSize) {
				throw std::runtime_error("[LSH] - attempting to add to a full bucket");
			}
			table[(index * _BucketSize) + sizes[index]++] = rec;
		}
		
		core::Array<LSHRecord> get(unsigned long index) {
			return core::Array<LSHRecord>(&(table[(index * _BucketSize)]), sizes[index]);
		}
		
		void print_sizes() {
			for (int i = 0; i < _Size; i ++) {
				std::cout << sizes[i] << " - " << table[(i * _BucketSize)].id << " - " << (int)i << std::endl;
			}
		}
		
		int 		sizes[_Size];
		LSHRecord 	table[_Size * _BucketSize];
	};
	
	
	
	template <int _TableSize, int _TableBucketSize>
	class LSHIndex {
		public:
			typedef unsigned char hash_type;
		
			//		size(pow(2, sizeof(LSHIndex::hash_type) * 8) - 1),
			LSHIndex(const std::string & path, int _number_of_tables, int dimensions) :
				tables( path ),
				number_of_tables(_number_of_tables),
				planes(_number_of_tables) {
					tables.resize(number_of_tables);
					planes.resize(number_of_tables);
					for (int i = 0; i < number_of_tables; i ++) {
						planes[i] = new persistance::PMatrix( path + std::to_string(i), sizeof(hash_type) * 8, dimensions);
					}
			}
		
			void generate() {
				for (int i = 0; i < number_of_tables; i ++) {
					
					memset(tables[i].sizes, 0, _TableSize);
					memset(tables[i].table, 0, _TableSize * _TableBucketSize);
					
					math::generateProjections(*planes[i]);
				}
			}
		
			void add(math::Vector & vec, LSHRecord & record){
				
				std::vector<std::future<void>> futures;
				futures.resize(number_of_tables);
				
				for (int i = 0; i < number_of_tables; i ++) {
					futures[i] = std::async(std::launch::async, [this, i, &vec, &record](){
						persistance::PMatrix * projection = planes[i];
						hash_type hash = math::hash<hash_type>(projection, &vec);
						tables[i].add(record, hash);
					});
				}
				for(int i = 0; i < futures.size(); i ++) {
					futures[i].get();
				}
				
			}
		
			core::Array<rsvidx::LSHRecord> get(math::Vector & vec)  {
				
				std::unordered_set<LSHRecord> included;
				std::vector<std::future<core::Array<LSHRecord>>> futures;
				futures.resize(number_of_tables);
				core::Array<rsvidx::LSHRecord> result( 2 );
				

				for (int i = 0; i < number_of_tables; i ++) {
					futures[i] = std::async(std::launch::async, [this, i, &vec](){
						
						persistance::PMatrix * projection = planes[i];
						hash_type hash = math::hash<hash_type>(projection, &vec);
						core::Array<rsvidx::LSHRecord> bucket = tables[i].get(hash);
						return bucket;
					});
				}
				
				for (int i = 0; i < futures.size(); i ++ ) {
					core::Array<LSHRecord> table_results = futures[i].get();
					for (int i = 0; i < table_results.size(); i ++) {
						if (included.find(table_results[i]) == included.end()) {
							result.add(table_results[i]);
							included.insert(table_results[i]);
						}
					}
				}
				
				return result;
			}
		
			void remove(math::Vector & vec, LSHRecord & id);
		
		private:
			persistance::PArray<LSHTable<_TableSize, _TableBucketSize>> tables;
			core::Array<persistance::PMatrix *> planes;
			int number_of_tables;
	};
	
	
	
	
	// MARK: - IMPL

	/*
	

	template <int _NumberOfTables>
	void LSHIndex<_NumberOfTables>::remove(math::Vector & vec, LSHRecord & id) {
		hash_type hash = math::hash<hash_type>(&planes, &vec);
		core::ArrayWindow<LSHRecord> ids = base::operator[]((persistance::PAlloc<LSHRecord>::index_type)hash);
		for (int i = 0; i < ids.size(); i ++) {
			if (strcmp(id.id, ids[i].id) == 0) {
				memset(&ids[i], 0, IDSIZE);
			}
		}
		return ;
	}
	 */
}

#endif /* LSHIndex_hpp */
