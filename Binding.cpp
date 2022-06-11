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

extern "C" {

	/*
	 Bindings for ID
	 */
	const char * id_data(ID * id) {
		return id->data;
	}
	
	/*
	 Bindings for LSH
	 */
	void * lsh(int tables, int dimensions, const char * filename) {
		rsvidx::LSHIndex * index = new rsvidx::LSHIndex(tables, dimensions, filename);
		return index;
	}
	
	void lsh_add(
				 void * index,
				 const char * id,
				 unsigned int size,
				 math::Vector::v_val * data
				 ) {
		
		math::Vector vec (size, data);
		((rsvidx::LSHIndex*)index)->add(vec, ID(id));
	}
	
	void lsh_remove(
				 void * index,
				 const char * id,
				 unsigned int size,
				 math::Vector::v_val * data
				 ) {
		
		math::Vector vec (size, data);
		((rsvidx::LSHIndex*)index)->remove(vec, ID(id));
	}
	
	ID * lsh_get(
				 void * index,
				 unsigned int size,
				 math::Vector::v_val * data
				 ) {
		
		math::Vector vec (size, data);
		return &((rsvidx::LSHIndex*)index)->get(vec)[0];
		
		
	}
	
	
}

#endif /* Binding_hpp */
