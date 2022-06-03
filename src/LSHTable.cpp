//
//  LSHTable.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 28/05/2022.
//

#include "LSHTable.hpp"


using namespace rs::rsvidx;

LSHTable::LSHTable(int dimensions) : projections(sizeof(LSH_INDEXING_TYPE) * 8, dimensions), PersistantMultimap<ID>(sizeof(LSH_INDEXING_TYPE)) {
	rs::math::generateProjections(projections);

}

LSHTable::~LSHTable() {
	projections.save(this->foldername + "projections");
}

void LSHTable::add(rs::math::Vector & vector, ID id) {
	LSH_INDEXING_TYPE hash = rs::math::hash(&projections, &vector);
	this->PersistantMultimap<ID>::add((unsigned int)hash, id);
}

rs::core::Array<ID> * LSHTable::get(rs::math::Vector & vector) {
	LSH_INDEXING_TYPE hash = rs::math::hash(&projections, &vector);
	return this->PersistantMultimap<ID>::get((unsigned int)hash);
}

void LSHTable::setFoldername(const std::string & foldername) {
	this->PersistantMultimap<ID>::setFoldername(foldername);
	projections.load(this->foldername + "projections");
}


