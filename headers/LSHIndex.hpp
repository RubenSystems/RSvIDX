//
//  LSHIndex.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 19/05/2022.
//

#ifndef LSHIndex_hpp
#define LSHIndex_hpp

#define LSH_INDEXING_TYPE char

#include "LSHTable.hpp"
#include "Math.hpp"
#include <stdio.h>
#include <string>

namespace rs::rsvidx {
	class LSHIndex {
		
		
		public :
		
			LSHIndex(int numberOfTables, int hashSize, std::string filename);
				
			void add(const math::Vector &, LSH_ID_TYPE);
		
			core::Array<LSH_ID_TYPE> get(const math::Vector &);
		
			void remove(const math::Vector &, LSH_ID_TYPE);
			
		private:
		int numberOfTables, hashSize, dimensions;
		LSHTable * tables;
	};
}

#endif /* LSHIndex_hpp */
