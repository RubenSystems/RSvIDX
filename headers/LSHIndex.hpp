//
//  LSHIndex.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 19/05/2022.
//

#ifndef LSHIndex_hpp
#define LSHIndex_hpp


#include "LSHTable.hpp"
#include "Math.hpp"
#include <stdio.h>
#include <string>
#include "ID.hpp"

namespace rsvidx {
	class LSHIndex {
		
		
		public :
		
			/**
			 LSH Index initaliser
			 
			 - parameter Number of tables: the number of tables to create.

			 */
			LSHIndex(int, int, std::string);
		
			~LSHIndex();
				
			void add( math::Vector &, ID);
		
			core::Array<ID> get(math::Vector &);
		
			void remove(math::Vector &, ID);
					

		private:
		int numberOfTables, dimensions;
		LSHTable ** tables;
	};
}

#endif /* LSHIndex_hpp */
