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

#include "Output.h"


extern "C" {

	/*
	 Bindings for ID
	 */
	const char * id_data(ID * id) {
		return id->data;
	}
	
	/*
	 Required Bindings for Array
	 */
	const char * array_get_id(core::Array<ID> * array, int index) {
		return (const char *)&(array->operator[](index).data);
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
	
	
}

#endif /* Binding_hpp */
