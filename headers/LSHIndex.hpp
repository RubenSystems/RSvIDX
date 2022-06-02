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

#include <unordered_map>

namespace rs::rsvidx {
	class LSHIndex {
		
		
		public :
		
			/**
			 LSH Index initaliser
			 
			 - parameter Number of tables: the number of tables to create.

			 */
			LSHIndex(int, int, std::string);
		
			~LSHIndex();
				
			void add( math::Vector &, LSH_ID_TYPE);
		
			core::Array<LSH_ID_TYPE> get(math::Vector &);
		
			void remove(const math::Vector &, LSH_ID_TYPE);
			
		std::unordered_map<int, int> x;
		
		private:
		int numberOfTables, dimensions;
		LSHTable ** tables;
	};
}

#endif /* LSHIndex_hpp */
