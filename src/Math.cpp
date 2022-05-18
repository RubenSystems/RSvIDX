//
//  Math.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//

#include "Math.hpp"
#include <math.h>


namespace rs::math {
	int power(int a, int b) {
		return pow(a, b);
	}
	
	Matrix::~Matrix(){ delete [] this->data; }
	
	int Matrix::get(unsigned int row, unsigned int column) {
		return this->data[column + (row * this->columns)];
	}
}
