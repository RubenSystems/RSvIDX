//
//  InvertedIndex.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 03/06/2022.
//

#include "InvertedIndex.hpp"


using namespace rs::rsvidx;

InvertedIndex::InvertedIndex (int bucketCount) : PersistantMultimap<InvertedIndexNode>(bucketCount) {
	
}


void InvertedIndex::add(InvertedIndexNode item) {
	int index = hash(item.id);
	this->PersistantMultimap<InvertedIndexNode>::add(index, item);
}

const char * InvertedIndex::get(const ID & id) {
	int index = hash(id);
	rs::core::Array<InvertedIndexNode> * result = this->PersistantMultimap<InvertedIndexNode>::get(index);
	for(int i = 0; i < result->size(); i ++) {
		InvertedIndexNode & item = result->operator[](i);
		out(item.id.data);
		if (item.id == id) {
			return item.data;
		}
	}
	return nullptr;
}

void InvertedIndex::remove(const ID & id) {
	
}

unsigned int InvertedIndex::hash(const ID & id) {
	//	DJB2 algo;
	unsigned int hash;
	int c;

	hash = 5381;
	for (int i = 0; i < ID::idsize; i ++) {
		c = id.data[i];
		hash = ((hash << 5) + hash) + c;
		/* hash * 33 + c */
	}
	return (hash % this->size);
 }

