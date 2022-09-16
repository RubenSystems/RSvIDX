//
//  PMultiMap.h
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 02/09/2022.
//

#ifndef PMultiMap_h
#define PMultiMap_h


#include "PAlloc.h"
#include "PArray.h"
#include "../RSCore/Array.h"

#include <future>
#include <vector>

namespace rsvidx {
//	namespace persistance {
//		
//		template <class T, int _NumberOfBuckets, int _BucketSize>
//		struct PMultiMapNode {
//			int size;
//			T data [_NumberOfBuckets * _BucketSize];
//		};
//		
//		template <class T, int _BucketSize = 10>
//		class PMultiMap {
//			public:
//				PMultiMap(const std::string & path, int number_of_buckets) : buckets(path + ".rsmultimap") {
//					buckets.resize(number_of_buckets);
//				}
//				
//				core::Array<T> operator[](typename PAlloc<T>::index_type index) {
//					PMultiMapNode<T> & node = buckets[index];
//					return core::Array<T>(node.data, node.size);
//					
//				}
//				
//				void add(typename PAlloc<T>::index_type index, const T & item) {
//					PMultiMapNode<T> & node = buckets[index];
//					
//					if (node.size + 1 > _BucketSize) {
//						throw std::runtime_error("[PMULTMAP] - bucket is full");
//					}
//					node.data[node.size ++] = item;
//				}
//						
//			private:
//				PArray<PMultiMapNode<T>> buckets;
//		};
//	}
}


#endif /* PMultiMap_h */
