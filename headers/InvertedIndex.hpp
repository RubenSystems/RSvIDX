//
//  InvertedIndex.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 03/06/2022.
//

#ifndef InvertedIndex_hpp
#define InvertedIndex_hpp

#include "../config.h"

#include "PersistantTypes.hpp"
#include "ID.hpp"
#include <stdio.h>



namespace rsvidx {
	
	struct InvertedIndexNode {
		
		
		InvertedIndexNode() {}
		
		
		InvertedIndexNode(ID n_id, const char * n_data) : id(n_id){
			memcpy(data, n_data, STRING_SIZE * sizeof(char));
		}
		
		InvertedIndexNode(const InvertedIndexNode & other){
			id = other.id;
			
			memcpy(data, other.data, STRING_SIZE * sizeof(char));
		}
		
		ID id;
		char data[STRING_SIZE];
	};
	
	
	class InvertedIndex: public PersistantMultimap<InvertedIndexNode> {
		
		public:
			InvertedIndex(int);
		
			void add(InvertedIndexNode);
		
			core::Array<InvertedIndexNode> get(const char *);
		
			void remove(InvertedIndexNode);
		
		private:
		
			unsigned int hash(const char * );
		
			
			
	};
}

#endif /* InvertedIndex_hpp */
