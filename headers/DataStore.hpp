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
#include "../Output.h"

namespace rs::rsvidx {
	
	struct Record {

		Record () = default;
		
		Record(const ID & id, const std::string & data):
			id (id), data(data) {
				size.data = (int)data.size();
		}
		
		~Record() {
		}
		
		ID id;

		struct {
			int data;
		} size;
		
		std::string data;
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
