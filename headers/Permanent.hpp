//
//  Permanent.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 22/05/2022.
//

#ifndef Permanent_hpp
#define Permanent_hpp

#include <stdio.h>
#include <string>

namespace rs::rsvidx {
	class Permanent {
		public:
			Permanent();
		
			const static Permanent shared;
		
			void read(std::string, void *, int, int) const ;
		
			void write(std::string, void *, int, int) const;
	};
}

#endif /* Permanent_hpp */
