//
//  LSHIndex.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 19/05/2022.
//

#ifndef LSHIndex_hpp
#define LSHIndex_hpp

#define LSH_INDEXING_TYPE char

#include "../core/HashArray.h"
#include "Math.hpp"
#include <stdio.h>
#include <string>

namespace rs::rsvidx {
	class LSHIndex {
		
		
		public :
			typedef char id_type[10];
		
			LSHIndex(int numberOfTables, int hashSize, std::string filename);
				
			void add(const math::Vector &, id_type);
		
			core::Array<id_type> get(const math::Vector &);
		
			void remove(const math::Vector &, id_type);
			
		private:
		int numberOfTables, hashSize, dimensions;
		rs::core::HashArray<id_type> * tables;
//		math::Matrix projections;
	};
}

#endif /* LSHIndex_hpp */
