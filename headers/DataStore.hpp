//
//  DataStore.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 05/06/2022.
//

#ifndef DataStore_hpp
#define DataStore_hpp

#include <stdio.h>
#include <string>
#include "ID.h"
#include "Math.hpp"

namespace rs::rsvidx {
	
	struct Record {

		
		ID id;

		struct {
			int data;
			int vector;
		} size;
		
		char* data;
		rs::math::Vector vector;
	};
	
	class DataStore {
		public:
			
			DataStore(const std::string & );
		
			void set(const Record &);
		
			Record get(const ID &);
		
		private:
			std::string foldername;
			
	};
}

#endif /* DataStore_hpp */
