//
//  LSHTable.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 28/05/2022.
//

#include "LSHTable.hpp"


using namespace rs::rsvidx;

LSHTable::LSHTable(int hashSize, int dimensions) : projections(hashSize, dimensions), PersistantMultimap<LSH_ID_TYPE>(sizeof(LSH_INDEXING_TYPE)) {
	rs::math::generateProjections(projections);
	
	projections.load(this->foldername + "projections");
	
	for(int i = 0; i < projections.size().rows; i ++) {
		for(int c = 0; c < projections.size().columns; c++) {
			out(projections.get(i, c));
		}
	}
}

LSHTable::~LSHTable() {
	
	projections.save(this->foldername + "projections");
}

void LSHTable::add(rs::math::Vector & vector, LSH_ID_TYPE id) {
	LSH_INDEXING_TYPE hash = rs::math::hash(&projections, &vector);
	this->PersistantMultimap<LSH_ID_TYPE>::add((unsigned int)hash, id);
}

rs::core::Array<LSH_ID_TYPE> * LSHTable::get(rs::math::Vector & vector) {
	LSH_INDEXING_TYPE hash = rs::math::hash(&projections, &vector);
	out((unsigned int )hash);
	return this->PersistantMultimap<LSH_ID_TYPE>::get((unsigned int)hash);
}
