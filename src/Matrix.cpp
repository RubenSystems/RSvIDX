//
//  Matrix.cpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 02/09/2022.
//

#include "../math/Matrix.hpp"
#include <string.h>

namespace rsvidx {
	namespace math {
		Matrix::Matrix(unsigned int n_rows, unsigned int n_columns) : rows(n_rows), columns(n_columns), requires_dealloc(true) {
			data = new m_val[n_rows * n_columns];
		}

		Matrix::Matrix(unsigned int n_rows, unsigned int n_columns, m_val * n_data) : rows(n_rows), columns(n_columns), requires_dealloc(false) {
			data = n_data;
		}


		Matrix::~Matrix(){
			if (requires_dealloc)
				delete [] this->data;
		}
		
		Matrix::Matrix(const Matrix & copy): Matrix(copy.rows, copy.columns) {
			for (int i = 0; i < copy.rows * copy.columns; i ++) {
				data[i] = copy.data[i];
			}
		}
		
		Matrix::Matrix(Matrix && move): rows(move.rows), columns(move.columns), requires_dealloc(move.requires_dealloc) {
			data = move.data;
			move.data = nullptr;
		}
		
		Matrix & Matrix::operator = (const Matrix & copy) {
			rows = copy.rows;
			columns = copy.columns;
			requires_dealloc = copy.requires_dealloc;
			data = new m_val[columns * rows];
			for (int i = 0; i < copy.rows * copy.columns; i ++) {
				data[i] = copy.data[i];
			}
			
			return *this;
		}
		
		Matrix & Matrix::operator = (Matrix && move) {
			delete data;
			rows = move.rows;
			columns = move.columns;
			requires_dealloc = move.requires_dealloc;
			data = move.data;
			move.data = nullptr;
			
			return *this;
		}

		Matrix::m_val Matrix::get(unsigned int row, unsigned int column) const {
			return this->data[column + (row * this->columns)];
		}
		

		Matrix::m_val & Matrix::operator[](unsigned int index) {
			return this->data[index];
		}

		Matrix::m_val & Matrix::mutate(unsigned int row, unsigned int column) {
			return this->operator[](column + (row * this->columns));
		}

		Matrix::Size Matrix::size() const {
			return {rows, columns};
		}

	}
}
