//
//  StandardDiskOperator.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 25/05/2022.
//

#ifndef StandardDiskOperator_hpp
#define StandardDiskOperator_hpp

#include <stdio.h>
#include "DiskOperator.h"


namespace rs::rsvidx {
	class StandardDiskOperator: public DiskOperator {
		
		public:

			void open(const char *, OpenType);
		
			void write(void *, int);
		
			void read(void *, int);
		
			void seek(int);
		
			void close();
		
			bool exists(const char *);
		
		private:
			void * file;
		
			void createDirectory(const char *) ;
	};
}

#endif /* StandardDiskOperator_hpp */
