//
//  OrderedIndex.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 03/06/2022.
//

#include "../headers/OrderedIndex.hpp"

namespace rsvidx {
	OrderedIndex::OrderedIndex() : PersistantArray<OrderedIndexNode>() {}

	/*
	 These functions will return *than or equal to
	 */
	core::Array<OrderedIndexNode> OrderedIndex::getGreaterThan(OrderedIndexNode::orderednode_val value) {
		unsigned int index = search(value);
		return core::Array<OrderedIndexNode>(data, index, this->size());
	}

	core::Array<OrderedIndexNode> OrderedIndex::getLessThan(OrderedIndexNode::orderednode_val value) {
		unsigned int index = search(value);
		return core::Array<OrderedIndexNode>(data, 0, index);
	}

	void OrderedIndex::insert(OrderedIndexNode value) {
		unsigned int index = search(value.data);
		this->core::Array<OrderedIndexNode>::insert(index, value);
	}

	unsigned int OrderedIndex::search(OrderedIndexNode::orderednode_val value) {
		//binary search 
		int mid;
		int low = 0;
		int high = size();

		
		while (low < high) {
			mid = low + (high - low) / 2;

			if (value >= data[mid].data) {
				low = mid + 1;
			} else {
				high = mid;
			}
		}

		if(low < size() && data[low].data <= value) {
			low++;
		}

		return low;
	}
}
