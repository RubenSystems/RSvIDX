//
//  OrderedIndex.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 03/06/2022.
//

#ifndef OrderedIndex_hpp
#define OrderedIndex_hpp

#include <stdio.h>
#include "PersistantTypes.hpp"
#include "ID.hpp"

namespace rsvidx {
	struct OrderedIndexNode {
		typedef float orderednode_val;
		
		ID id;
		float data;
	};
	
	class OrderedIndex: public PersistantArray<OrderedIndexNode> {
		
		public:
			OrderedIndex();
		
			/*
			 
			 These functions will return *than or equal to
			 
			 */
			core::Array<OrderedIndexNode> getGreaterThan(OrderedIndexNode::orderednode_val);
		
			core::Array<OrderedIndexNode> getLessThan(OrderedIndexNode::orderednode_val);
		
			void insert(OrderedIndexNode);
		
		private:
			unsigned int search(OrderedIndexNode::orderednode_val);
		
	};
}

#endif /* OrderedIndex_hpp */
