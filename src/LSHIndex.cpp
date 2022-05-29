//
//  LSHIndex.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 19/05/2022.
//

#include "LSHIndex.hpp"
#include "../headers/Math.hpp"

using namespace rs::rsvidx;


LSHIndex::LSHIndex(int numberOfTables, int hashSize, std::string filename): numberOfTables(numberOfTables), hashSize(hashSize) {
		
//	tables =  new LSHTable[numberOfTables](numberOfTables, hashSize);
	
	for (int i = 0; i < numberOfTables; i ++) {
		tables[i].setFoldername(std::to_string(i));
	}
	
	
}


void LSHIndex::add(const math::Vector &, LSH_ID_TYPE) {
	
}

//rs::core::Array<LSH_ID_TYPE> LSHIndex::get(const math::Vector &) {
//	
//}

void LSHIndex::remove(const rs::math::Vector &, LSH_ID_TYPE){
	
}
