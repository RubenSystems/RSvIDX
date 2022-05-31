//
//  LSHTable.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 28/05/2022.
//

#ifndef LSHTable_hpp
#define LSHTable_hpp

#include <stdio.h>
#include "PersistantTypes.hpp"
#include "../config.h"
#include "Math.hpp"

namespace rs::rsvidx {
	class LSHTable: public PersistantMultimap<LSH_ID_TYPE> {
		public:
			LSHTable(int);
		
			~LSHTable();
		
			void add( rs::math::Vector &, LSH_ID_TYPE);
		
			rs::core::Array<LSH_ID_TYPE> * get(rs::math::Vector &);
		
			void setFoldername(const std::string &) override;
				
		private:
			PersistantMatrix projections;
	};
}

#endif /* LSHTable_hpp */
