//
//  Math.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//

#ifndef Math_hpp
#define Math_hpp



#include <stdio.h>

namespace rs::math {
	int power(int, int);
	
	class Matrix {
		typedef float m_val;
		
		public:
			Matrix(unsigned int n_rows, unsigned int n_columns, m_val * n_data) : rows(n_rows), columns(n_columns), data(n_data) {}
		
			~Matrix();
			
			int get(unsigned int row, unsigned int column);
		
		private:
			m_val * data;
			unsigned int rows, columns;
		
			
	};
}

#endif /* Math_hpp */
