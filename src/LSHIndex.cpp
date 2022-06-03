//
//  LSHIndex.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 19/05/2022.
//

#include "LSHIndex.hpp"
#include "../headers/Math.hpp"

#include <future>
#include <vector>
#include <unordered_set>
#include <string>

using namespace rs::rsvidx;


LSHIndex::LSHIndex(int numberOfTables, int dimensions, std::string filename): numberOfTables(numberOfTables), dimensions(dimensions) {
	
	//c.
	tables = new LSHTable* [numberOfTables];
	
	for (int i = 0; i < numberOfTables; i ++) {
		tables[i] = new LSHTable(dimensions);
		tables[i]->setFoldername(filename + "/" + std::to_string(i) + "/");
	}
}

LSHIndex::~LSHIndex() {
	for(int i = 0; i < numberOfTables; i ++) {
		delete tables[i];
	}
	delete [] tables;
}



void LSHIndex::add( math::Vector & vec, ID id) {
	for (int i = 0; i < numberOfTables; i ++) {
		std::async(std::launch::async, [this, i, &vec, &id](){
			tables[i]->add(vec, id);
		});
	}
}

rs::core::Array<ID> LSHIndex::get(math::Vector & vec) {
	std::vector<std::future<rs::core::Array<ID> *>> futures;
	futures.resize(numberOfTables);
	for (int i = 0; i < numberOfTables; i ++) {
		futures[i] = std::async(std::launch::async, [this, i, &vec](){
			return tables[i]->get(vec);
		});
	}
	rs::core::Array<ID> array;
	std::unordered_set<std::string> ids;
	for(int i = 0; i < futures.size(); i++) {
		rs::core::Array<ID> * resultshard = futures[i].get();
		for (int i = 0; i < resultshard->size(); i ++) {
			resultshard->operator[](i).data[ID::idsize - 1] = 0;
			std::string element = std::string(resultshard->operator[](i).data);
			
			if (ids.find(element) == ids.end()) {
				array.add(resultshard->operator[](i));
				ids.insert(element);
			}
			
		}
	
	}
	
	return array;
}

void LSHIndex::remove(rs::math::Vector & vec, ID id){
	for (int i = 0; i < numberOfTables; i ++) {
		std::async(std::launch::async, [this, i, &vec, &id](){
			tables[i]->remove(vec, id);
		});
	}
}
