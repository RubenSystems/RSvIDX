//
//  PMatrix.h
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 07/09/2022.
//

#ifndef PMatrix_h
#define PMatrix_h


#include "../math/Matrix.hpp"
#include "PAlloc.h"

namespace rsvidx {
	namespace persistance {
		class PMatrix : public math::Matrix, protected PAlloc<math::Matrix::m_val> {
			
			typedef PAlloc<math::Matrix::m_val> allocator;
			typedef math::Matrix 				matrix;
			
			public:
				PMatrix(const std::string & filename, int n_columns, int n_rows) : PAlloc<math::Matrix::m_val>(), math::Matrix(n_columns, n_rows, nullptr){
					allocator::set_filename(filename + "projections.rsmatrix");
					allocator::allocate(n_columns * n_rows);
					matrix::data = allocator::data;
				}
			
				PMatrix(const PMatrix & copy): matrix(copy), allocator(copy) {
					
				}

				PMatrix(PMatrix && move): matrix(move), allocator(move) {

				}
				
				PMatrix & operator = (const PMatrix & copy) {
					
					return *this;
				}
				
				PMatrix & operator = (PMatrix && move) {
					matrix::operator=(move);
					allocator::operator=(move);
					
					return *this;
				}

			
				~PMatrix() {
					
				}
		};
	}
}


#endif /* PMatrix_h */
