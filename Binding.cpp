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

#include "Output.h"


extern "C" {

	/*
	 Required bindings for OrderedNode
	 */
	const char * ordered_node_get_id(rsvidx::OrderedIndexNode * node) {
		return node->id.data;
	}
	
	rsvidx::OrderedIndexNode::orderednode_val ordered_node_get_value(rsvidx::OrderedIndexNode * node) {
		return node->data;
	}
	
	
	
	/*
	 Required Bindings for Array
	 */
	const char * array_get_id(core::Array<ID> * array, int index) {
		return (const char *)&(array->operator[](index).data);
	}

	void * array_get_node(core::Array<rsvidx::OrderedIndexNode> * array, int index) {
		return &(array->operator[](index));
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
		memmove(&(out->operator[](0)), &(result[0]), sizeof(ID) * result.size());
		
		return out;
	}
	
	void close(rsvidx::LSHIndex * pointer) {
		delete pointer;
	}
	
	/*
	 Bindings for OrderedIndex
	 */
	rsvidx::OrderedIndex * ordered() {
		return new rsvidx::OrderedIndex;
	}
	
	void insert(
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
		
		memmove(&(toReturn->operator[](0)), &(result[0]), result.size() * sizeof(rsvidx::OrderedIndexNode));
		
		return toReturn;
		
		
		
	}
	
	core::Array<rsvidx::OrderedIndexNode> * ordered_get_less(rsvidx::OrderedIndex * index,
															 rsvidx::OrderedIndexNode::orderednode_val forValue
															 ) {
		core::Array<rsvidx::OrderedIndexNode> result = index->getLessThan(forValue);
		
		core::Array<rsvidx::OrderedIndexNode> * toReturn = new core::Array<rsvidx::OrderedIndexNode>(result.size());
		
		memmove(&(toReturn->operator[](0)), &(result[0]), result.size() * sizeof(rsvidx::OrderedIndexNode));
		
		return toReturn;
	}
	
	
}

#endif /* Binding_hpp */
