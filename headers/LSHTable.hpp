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
#include "ID.hpp"

namespace rsvidx {
	class LSHTable: public PersistantMultimap<ID> {
		public:
		
			LSHTable(int);
		
			~LSHTable();
		
			void add( math::Vector &, ID);
		
			core::Array<ID> * get(math::Vector &);
		
			void remove(math::Vector &, ID);
		
			void setFoldername(const std::string &) override;
						
		private:
			PersistantMatrix projections;
	};
}

#endif /* LSHTable_hpp */
