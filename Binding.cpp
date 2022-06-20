//
//  Binding.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 11/06/2022.
//

#ifndef Binding_hpp
#define Binding_hpp

#include <stdio.h>


#include "headers/LSHIndex.hpp"
#include "headers/OrderedIndex.hpp"
#include "headers/InvertedIndex.hpp"
#include "headers/DataStore.hpp"

#include "Output.h"


extern "C" {


	
	
	
	
	/*
	 Required Bindings for Result arrays
	 */
	
	int lsh_result_get_size(core::Array<ID> * array) {
		return array->size();
	}
	
	int inverted_result_get_size(core::Array<rsvidx::InvertedIndexNode> * array) {
		return array->size();
	}
	
	
	const char * lsh_result_get_id(core::Array<ID> * array, int index) {
		return (const char *)&(array->operator[](index).data);
	}
	
	void lsh_result_delete(core::Array<ID> * array) {
		delete array;
	}
	
	void ordered_result_delete(core::Array<rsvidx::OrderedIndexNode> * array) {
		delete array;
	}
	
	void inverted_result_delete(core::Array<rsvidx::InvertedIndexNode> * array) {
		delete array;
	}
	
	int ordered_result_get_size(core::Array<rsvidx::OrderedIndexNode> * array) {
		return array->size();
	}

	const char * ordered_result_get_id(core::Array<rsvidx::OrderedIndexNode> * array, int index) {
		return (array->operator[](index).id.data);
	}
	
	const char * inverted_result_get_id(core::Array<rsvidx::InvertedIndexNode> * result, unsigned int index) {
		return result->operator[](index).id.data;
	}

	
	/*
	 Bindings for LSH
	 */
	
	rsvidx::LSHIndex * lsh(int tables, int dimensions, const char * filename) {
		return new rsvidx::LSHIndex(tables, dimensions, std::string(filename));
	}
	
	void lsh_add(
				 rsvidx::LSHIndex * index,
				 const char * id,
				 unsigned int size,
				 math::Vector::v_val * data
				 ) {

		math::Vector vec (size, data);
		index->add(vec, ID(id));
	}
	
	void lsh_remove(
				rsvidx::LSHIndex * index,
				const char * id,
				unsigned int size,
				math::Vector::v_val * data
				 ) {
		
		math::Vector vec (size, data);
		index->remove(vec, ID(id));
	}
	
	/*
	 Cleanup is your problem now
	 */
	core::Array<ID> * lsh_get (
				rsvidx::LSHIndex * index,
				unsigned int size,
				math::Vector::v_val * data
				 ) {
		
		math::Vector vec (size, data);
		core::Array<ID> result = index->get(vec);
		
		core::Array<ID> * out = new core::Array<ID>(result.size());
		out->emplaceBack(&result);
		
		return out;
	}
	
	
	
	/*
	 Bindings for OrderedIndex
	 */
	rsvidx::OrderedIndex * ordered(const char * filename) {
		rsvidx::OrderedIndex * index = new rsvidx::OrderedIndex;
		
		index->load(filename);
		return index;
	}
	
	void ordered_insert(
				rsvidx::OrderedIndex * index,
				const char * id,
				rsvidx::OrderedIndexNode::orderednode_val data) {
		
		rsvidx::OrderedIndexNode insert;
		insert.id = ID(id);
		insert.data = data;
		
		index->insert(insert);
	}
	
	core::Array<rsvidx::OrderedIndexNode> * ordered_get_greater(
																rsvidx::OrderedIndex * index,
																rsvidx::OrderedIndexNode::orderednode_val forValue
																) {
		core::Array<rsvidx::OrderedIndexNode> result = index->getGreaterThan(forValue);
		
		core::Array<rsvidx::OrderedIndexNode> * toReturn = new core::Array<rsvidx::OrderedIndexNode>(result.size());
		
		toReturn->emplaceBack(&result);
//		memmove(&(toReturn->operator[](0)), &(result[0]), result.size() * sizeof(rsvidx::OrderedIndexNode));
		
		return toReturn;
		
		
		
	}
	
	core::Array<rsvidx::OrderedIndexNode> * ordered_get_less(rsvidx::OrderedIndex * index,
															 rsvidx::OrderedIndexNode::orderednode_val forValue
															 ) {
		core::Array<rsvidx::OrderedIndexNode> result = index->getLessThan(forValue);
		
		core::Array<rsvidx::OrderedIndexNode> * toReturn = new core::Array<rsvidx::OrderedIndexNode>(result.size());
		
		toReturn->emplaceBack(&result);
//		memmove(&(toReturn->operator[](0)), &(result[0]), result.size() * sizeof(rsvidx::OrderedIndexNode));
		
		return toReturn;
	}
	
	/*
	 Bindings for InvertedIndex
	 */
	
	/**
	 Create inverted index.
	 
	 - parameter buckets: the number of buckets.
	 - parameter foldername: the folder (not file as it will create the file) name of the index
	 - returns: a pointer to an index
	 - warning: pointer must be freed using close

	 */
	rsvidx::InvertedIndex * inverted(int buckets, const char * foldername) {
		rsvidx::InvertedIndex * index = new rsvidx::InvertedIndex(buckets);
		index->setFoldername(foldername);
		
		return index;
	}
	
	//get add remove
	void inverted_add(rsvidx::InvertedIndex * index, const char * data, const char * id) {
		index->add({ID(id), data});
	}
	
	core::Array<rsvidx::InvertedIndexNode> * inverted_get(rsvidx::InvertedIndex * index,  const char * data) {
		core::Array<rsvidx::InvertedIndexNode> result = index->get(data);
		
		core::Array<rsvidx::InvertedIndexNode> * returnval = new core::Array<rsvidx::InvertedIndexNode>(result.size());
		
		
//		for(int i = 0; i < result.size(); i ++) {
			out(result[0].data);
//		}
		
		returnval->emplaceBack(&result);
//		memmove(&(returnval->operator[](0)), &(result[0]), result.size() * sizeof(rsvidx::InvertedIndexNode));
		
		return returnval;
	}
	
	/*
	 Bindings for datastore
	 */
	
	rsvidx::DataStore * datastore(const char * filename) {
		return new rsvidx::DataStore(filename);
	}
	
	void datastore_add(rsvidx::DataStore * index, const char * id, const char * data, math::Vector::v_val * vector, int vectorSize) {
		
		rsvidx::Record record(ID(id), data, vectorSize, vector);
		
		index->set(record);
		
	}
	
	rsvidx::Record * datastore_get(rsvidx::DataStore * index, const char * id) {
		rsvidx::Record * record = new rsvidx::Record();
		
		index->get(ID(id), *record);

		return record;
	}
	
	const char * datastore_result_get_data(rsvidx::Record * record) {
		return record->data.c_str();
	}
	
	int datastore_result_get_vec_size(rsvidx::Record * record) {
		return record->size.vector;
	}
	
	math::Vector::v_val datastore_result_get_vec(rsvidx::Record * record, int index) {

		return record->vector[index];
	}
	
	void datastore_result_delete(rsvidx::Record * array) {
		delete array;
	}
	
	
	/*
	 Cleanup functions
	 */
	void close_lsh(rsvidx::LSHIndex * pointer) {
		delete pointer;
	}
	
	void close_ordered(rsvidx::OrderedIndex * pointer, const char * filename) {
		pointer->save(filename);
		delete pointer;
	}
	
	void close_inverted(rsvidx::InvertedIndex * pointer) {
		delete pointer;
	}
	
	void close_datastore(rsvidx::DataStore * pointer) {
		delete pointer;
	}
	
	
}

#endif /* Binding_hpp */
