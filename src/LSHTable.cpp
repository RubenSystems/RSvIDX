//
//  LSHTable.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 28/05/2022.
//

#include "../headers/LSHTable.hpp"


using namespace rsvidx;

LSHTable::LSHTable(int dimensions) : projections(sizeof(LSH_INDEXING_TYPE) * 8, dimensions), PersistantMultimap<ID>(math::power(2, (sizeof(LSH_INDEXING_TYPE) * 8))) {
	math::generateProjections(projections);

}

LSHTable::~LSHTable() {
	projections.save(this->foldername + "projections");
}

void LSHTable::add(math::Vector & vector, ID id) {
	LSH_INDEXING_TYPE hash = math::hash(&projections, &vector);
	this->PersistantMultimap<ID>::add((unsigned int)hash, id);
}

core::Array<ID> * LSHTable::get(math::Vector & vector) {
	LSH_INDEXING_TYPE hash = math::hash(&projections, &vector);
	return this->PersistantMultimap<ID>::get((unsigned int)hash);
}

void LSHTable::setFoldername(const std::string & foldername) {
	this->PersistantMultimap<ID>::setFoldername(foldername);
	projections.load(this->foldername + "projections");
}


void LSHTable::remove(math::Vector & vector, ID id) {
	LSH_INDEXING_TYPE hash = math::hash(&projections, &vector);
	core::Array<ID> * bucket = this->PersistantMultimap<ID>::get((unsigned int)hash);
	
	for (int i = 0; i < bucket->size(); i ++) {
		if (bucket->operator[](i) == id) {
			bucket->remove(i);
			return;
		}
	}
}
