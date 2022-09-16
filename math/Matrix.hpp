//
//  Matrix.hpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 02/09/2022.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>

namespace rsvidx {
	namespace math {
		class Matrix {
			public:
				typedef float m_val;
			
				Matrix(unsigned int n_rows, unsigned int n_columns);
				
				Matrix(unsigned int n_rows, unsigned int n_columns, m_val * n_data);
			
				~Matrix();
			
				Matrix(const Matrix & copy);
				
				Matrix(Matrix && move);
				
				Matrix & operator = (const Matrix & copy);
				
				Matrix & operator = (Matrix && move);

			
				m_val & operator[](unsigned int index) ;
				
				m_val & mutate(unsigned int row, unsigned int column);
			
				m_val get(unsigned int row, unsigned int column) const;
						
				struct Size {
					unsigned int rows, columns;
				};
			
				Size size() const;
			
			protected:
				m_val * data;
				unsigned int rows, columns;
				bool requires_dealloc = false;
		};
	}
}



#endif /* Matrix_hpp */
