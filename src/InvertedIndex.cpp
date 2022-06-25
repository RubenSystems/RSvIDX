//
//  InvertedIndex.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 03/06/2022.
//

#include "../headers/InvertedIndex.hpp"


using namespace rsvidx;

InvertedIndex::InvertedIndex (int bucketCount) : PersistantMultimap<InvertedIndexNode>(bucketCount) {
	
}


void InvertedIndex::add(InvertedIndexNode item) {
	int index = hash(item.data);
	this->PersistantMultimap<InvertedIndexNode>::add(index, item);
}

core::Array<InvertedIndexNode> InvertedIndex::get(const char * data) {
	int index = hash(data);
	core::Array<InvertedIndexNode> * result = this->PersistantMultimap<InvertedIndexNode>::get(index);
	core::Array<InvertedIndexNode> results;
	for(int i = 0; i < result->size(); i ++) {
		InvertedIndexNode & item = result->operator[](i);
		
		if (strcmp(item.data, data) == 0) {
			results.add(item);
		}
	}
	return results;
}

void InvertedIndex::remove(InvertedIndexNode node) {
	// TODO: implement
	int index = hash(node.data);
	core::Array<InvertedIndexNode> * result = this->PersistantMultimap<InvertedIndexNode>::get(index);
	
	for(int i = 0; i < result->size(); i ++) {
		if (result->operator[](i).id == node.id) {
			result->remove(i);
		}
	}
}

unsigned int InvertedIndex::hash(const char * data) {
	//	DJB2 algo;
	unsigned int hash;
	int c;

	hash = 5381;
	for (int i = 0; i < strlen(data); i ++) {
		c = data[i];
		hash = ((hash << 5) + hash) + c;
		/* hash * 33 + c */
	}
	return (hash % this->size);
 }

