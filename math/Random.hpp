//
//  Random.hpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 02/09/2022.
//

#ifndef Random_hpp
#define Random_hpp

#include <stdio.h>
#include <random>

namespace rsvidx {
	namespace math {
		class Random {
			public:
				typedef float r_type;
			
				static Random shared;
				
				Random ();
			
				r_type generate() ;
			
			private:
				std::default_random_engine generator;
				std::uniform_real_distribution<r_type> distribution;
		};
	}
}

#endif /* Random_hpp */
