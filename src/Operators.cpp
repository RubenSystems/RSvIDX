//
//  Operators.cpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 02/09/2022.
//

#include "../math/Operators.hpp"

#include <system_error>
#include <future>
#include <vector>
#include <math.h>

#include "../math/Random.hpp"

static rsvidx::math::Vector::v_val calculate_vector_row(rsvidx::math::Matrix * a, rsvidx::math::Vector * b, unsigned int row) {
	float sum = 0;
	for (unsigned int column = 0; column < a->size().columns; column++) {
		sum += a->get(row, column) * b->get(column);
	}
	
	return sum;
}


namespace rsvidx {
	namespace math {
		
		void dot(Matrix * a, Vector * b, Vector & result) {
			if(a->size().rows != result.size()) {
				throw std::runtime_error("[MATH] - dot product dimensions incorrect \n");
			}
			
			std::vector<std::future<Vector::v_val>> futures;
			futures.resize(a->size().rows);
			
			for ( unsigned int row = 0; row < a->size().rows; row ++) {
				futures[(int)row] = (std::async(std::launch::async, calculate_vector_row, a, b, row));
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
	}
}
