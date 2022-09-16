//
//  Operators.hpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 02/09/2022.
//

#ifndef Operators_hpp
#define Operators_hpp

#include <stdio.h>

#include "Vector.hpp"
#include "Matrix.hpp"

namespace rsvidx {
	namespace math {
		void dot(Matrix *, Vector *, Vector &);
		
		Vector::v_val cosineSimilarity(Vector *, Vector * );
		
		void generateProjections(Matrix &);
		
		template <typename T>
		T hash(Matrix * planes, Vector * vector) {
			T hash = 0;
			Vector result (planes->size().rows);
			dot(planes, vector, result);
			
			for (unsigned int i = result.size(); i > 0; i --) {
				hash += result.get(i) > 0 ? (1 << i) : 0;
			}
			return hash;
		}
	}
}

#endif /* Operators_hpp */
