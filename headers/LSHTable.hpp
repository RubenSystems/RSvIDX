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
#include "ID.h"

namespace rs::rsvidx {
	class LSHTable: public PersistantMultimap<ID> {
		public:
		
			LSHTable(int);
		
			~LSHTable();
		
			void add( rs::math::Vector &, ID);
		
			rs::core::Array<ID> * get(rs::math::Vector &);
		
			void remove(rs::math::Vector &, ID);
		
			void setFoldername(const std::string &) override;
						
		private:
			PersistantMatrix projections;
	};
}

#endif /* LSHTable_hpp */
