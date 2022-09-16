//
//  Vector.hpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 02/09/2022.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>
#include <initializer_list>

namespace rsvidx {
	namespace math {
		class Vector {
			public:
				typedef float v_val;
			
				Vector(unsigned int size, v_val * data);
			
				Vector(unsigned int size);
			
				Vector(std::initializer_list<v_val> &&);
			
				~Vector();
			
				v_val get(unsigned int index) const;
			
				v_val & operator[](unsigned int index);
			
				unsigned int size() const;

			
			private:
				v_val * data;
				unsigned int d_size;
			
		};
	}
}

#endif /* Vector_hpp */
