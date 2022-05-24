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
#include <functional>
#include <fstream>

namespace rs::rsvidx {
	class Permanent {
		public:
			Permanent();
		
			const static Permanent shared;
		
			void filescope(std::function<void(std::fstream &)>) const;
		
			void read(std::fstream &, void *, int, int) const ;
		
			enum WriteType {
				overwrite,
				append
			};
			
			void write(std::fstream &, void *, int, int) const;
			
	};
	
	
	
	class Persistable {
		public:
			virtual void save() = 0;
			
			virtual void load() = 0;
	};
	
	
}

#endif /* Permanent_hpp */
