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
#include <stdio.h>

namespace rs::rsvidx {
	class LSHIndex {
		
		public :
			LSHIndex(int numberOfTables, int hashSize);
			
		private:
		int numberOfTables, hashSize, dimensions;
		rs::core::HashArray<char[10]> * tables;
	};
}

#endif /* LSHIndex_hpp */
