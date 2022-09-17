//
//  binding.cpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 11/09/2022.
//


#include "similarity/LSHIndex.hpp"

extern "C" {
	
	// MARK: - LSH Bindings
	const int table_size = 16;
	const int table_bucket_size = 64;
	
	
	/**
	 Create and initalise a new or existing index at the specified path.
	 
	 - parameter path: the path to the index.
	 - parameter dimensions: the dimensions of the vector that should be indexed.
	 - parameter number_of_tables: the number of duplicates. (increase for more general results but more storage)
	 - returns: a pointer to an LSH index
	 - warning: path must exist. Will not create folders
	 
	 # Notes: #
	 1. This can be used to generate a new LSH index, however, similarity_generate should be called to generate the new index. If it is not called, the index will be null initalised so all data will go to the same hash bucket.
	 */
	rsvidx::LSHIndex<table_size, table_bucket_size> * init_similarity(
																	  const char * path,
																	  int dimensions,
																	  int number_of_tables
																	) {
		return new rsvidx::LSHIndex<table_size, table_bucket_size>(path, number_of_tables, dimensions);
	}
	
	/**
	 Generate the projections and null initalises the index. This should be called only once on a new index.
	 
	 - parameter index: the index to be actioned.
	 - warning: If it is called on a current index, it will rehash everything and all existing records will be corrupted.
	 
	 # Notes: #
	 1. This should be called with init_similarity when creating the index.
	 */
	void generate_similarity(rsvidx::LSHIndex<table_size, table_bucket_size> * index) {
		index->generate();
	}
	
	
	/**
	 Add record to a similarity index
	 
	 - parameter index: the index to be actioned.
	 - parameter data: the vector that should be used indexed.
	 - parameter data_size: the size of the data
	 - parameter id: the id of the data.
	 - warning: the id will be truncated to IDSIZE (see /similarity/LSHIndex.hpp)
	 - warning: the original vector is not stored
	 */
	void add_similarity(
						rsvidx::LSHIndex<table_size, table_bucket_size> * index,
						rsvidx::math::Vector::v_val * data,
						unsigned int data_size,
						const char * id
					) {

		rsvidx::math::Vector vector_data (data_size, data);
		rsvidx::LSHRecord record (id);
		
		index->add(vector_data, record);
	}
	
	
	/**
	 Get candidates for similar indexes.
	 
	 - parameter index: the index to query.
	 - parameter data: the data to find similar vectors for
	 - parameter data_szie: the size of the data
	 - returns: A pointer to an array.
	 - warning: results are not ordered as the index does not store the original vectors

	 */
	core::Array<rsvidx::LSHRecord> * get(
										 rsvidx::LSHIndex<table_size, table_bucket_size> * index,
										 rsvidx::math::Vector::v_val * data,
										 unsigned int data_size
										 ) {
		
		rsvidx::math::Vector vector_data (data_size, data);
		core::Array<rsvidx::LSHRecord> result = index->get(vector_data);
		
		core::Array<rsvidx::LSHRecord> * heap_result = new core::Array<rsvidx::LSHRecord>(&(result[0]), result.size());
		
		return heap_result; 
		
	}
	
	
	
}
