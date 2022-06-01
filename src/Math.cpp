//
//  Math.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//

#include "Math.hpp"
#include <math.h>
#include <system_error>
#include <future>
#include <vector>
#include "../Output.h"



static rs::math::Vector::v_val calculateVectorRow(rs::math::Matrix * a, rs::math::Vector * b, unsigned int row) {
	float sum = 0;
	for (unsigned int column = 0; column < a->size().columns; column++) {
		sum += a->get(row, column) * b->get(column);
	}
	
	return sum;
}

namespace rs::math {
	
	// MARK: -Utility Functions
	int power(int a, int b) {
		return pow(a, b);
	}
	
	
	void dot(Matrix * a, Vector * b, Vector & result) {
		if(a->size().rows != result.size()) {
			throw std::runtime_error("[MATH] - dot product dimensions incorrect \n");
		}
		
		std::vector<std::future<Vector::v_val>> futures;
		futures.resize(a->size().rows);
		
		for ( unsigned int row = 0; row < a->size().rows; row ++) {
			futures[(int)row] = (std::async(std::launch::async, calculateVectorRow, a, b, row));
		}
		
		for(unsigned int i = 0; i < a->size().rows; i ++) {
			Vector::v_val value = futures[(int)i].get();
			result[i] = value;
		}
	}
	
	Vector::v_val cosineSimilarity(Vector * a, Vector * b) {
		double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
		for(unsigned int i = 0; i < a->size(); i++) {
			dot += a->get(i) * b->get(i) ;
			denom_a += a->get(i) * a->get(i);
			denom_b += b->get(i) * b->get(i);
		}
		return dot / (sqrt(denom_a) * sqrt(denom_b)) ;

	}
	
	void generateProjections(Matrix & fill) {
		std::vector<std::future<Random::r_type>> futures;
		int totalSize = fill.size().rows * fill.size().columns;
		futures.resize(totalSize);
		for (int i = 0; i < totalSize; i ++) {
			futures[i] = std::async(std::launch::async, []() {return Random::shared.generate();});
		}
		
		for(unsigned int i = 0; i < totalSize; i++) {
			fill[i] = futures[i].get();
		}
			
	}
	
	//MARK: -RANDOM
	Random Random::shared = Random();
	
	Random::Random() {
		this->distribution = std::uniform_real_distribution<r_type>(-1, 1);
	}
	
	Random::r_type Random::generate() {
		return this->distribution(generator);
	}
	
	// MARK: -MATRIX imp
	
	
	Matrix::Matrix(unsigned int n_rows, unsigned int n_columns) : rows(n_rows), columns(n_columns) {
		data = new m_val[n_rows * n_columns];
	}
	
	Matrix::Matrix(unsigned int n_rows, unsigned int n_columns, m_val * n_data) : Matrix(n_rows, n_columns) {
		memmove(data, n_data, n_rows * n_columns * sizeof(m_val));
	}
	
	
	Matrix::~Matrix(){
		delete [] this->data;
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
	
	// MARK: -VECTOR imp
	Vector::Vector(unsigned int size) : d_size(size){
		data = new v_val[size];
	}
	
	Vector::Vector(unsigned int size, v_val * n_data) : Vector(size) {
		memmove(data, n_data, size * sizeof(v_val));
	}
	
	
	Vector::~Vector(){
		delete [] data;
	}
	
	Vector::v_val Vector::get(unsigned int index) const {
		return this->data[index];
	}
	
	Vector::v_val & Vector::operator[](unsigned int index) {
		return this->data[index];
	}
	
	unsigned int Vector::size() const {
		return this->d_size;
	}
	
	
	
	LSH_INDEXING_TYPE hash(Matrix * planes, Vector * vector) {
		LSH_INDEXING_TYPE hash = 0;
		Vector result (planes->size().rows);
		dot(planes, vector, result);
		
		for (unsigned int i = result.size(); i > 0; i --) {
			hash += result.get(i) > 0 ? (1 << i) : 0;
		}
		return hash;
	}
}

