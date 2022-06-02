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
	delete[] tables;
}



void LSHIndex::add( math::Vector & vec, LSH_ID_TYPE id) {
	for (int i = 0; i < numberOfTables; i ++) {
		std::async(std::launch::async, [this, i, &vec, &id](){
			tables[i]->add(vec, id);
		});
	}
}

rs::core::Array<LSH_ID_TYPE> LSHIndex::get(math::Vector & vec) {
	std::vector<std::future<rs::core::Array<LSH_ID_TYPE> *>> futures;
	futures.resize(numberOfTables);
	for (int i = 0; i < numberOfTables; i ++) {
		futures[i] = std::async(std::launch::async, [this, i, &vec](){
			return tables[i]->get(vec);
		});
	}
	rs::core::Array<LSH_ID_TYPE> array;
	
	for(int i = 0; i < futures.size(); i++) {
		rs::core::Array<LSH_ID_TYPE> * resultshard = futures[i].get();
		out(resultshard->size());
		for (int i = 0; i < resultshard->size(); i ++) {
			resultshard->operator[](i).data[7] = 0;
			out(resultshard->operator[](i).data << "-");
			
		}
		out("");
		array.emplaceBack(resultshard);
	}
	
	return array;
}

void LSHIndex::remove(const rs::math::Vector &, LSH_ID_TYPE){
	
}
