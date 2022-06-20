//
//  Math.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//

#ifndef Math_hpp
#define Math_hpp



#include <stdio.h>
#include <random>

#include "../config.h"

namespace math {
	int power(int, int);
	
	class Random {
		public:
			typedef float r_type;
		
			static Random shared;
			
			Random ();
		
			r_type generate() ;
		
		protected:
			std::default_random_engine generator;
			std::uniform_real_distribution<r_type> distribution;
	};
	
	class Matrix {
		public:
			typedef float m_val;
		
			Matrix(unsigned int n_rows, unsigned int n_columns);
			
			Matrix(unsigned int n_rows, unsigned int n_columns, m_val * n_data);
		
			~Matrix();
		
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
		
			
	};
	
	class Vector {
		// class representing villian in dispicable me 1
		// actually just a vector (the math kind) which is a non-resizable array but stores the size value which is useful if you need to iterat. should be used to store vecotrs (as this is a vector indexer) and results of calculations.
		
		public:
			typedef float v_val;
		
			//Define an empty vector
			Vector();
		
			Vector(unsigned int size, v_val * data);
		
			Vector(unsigned int size);
		
			~Vector();
		
			v_val get(unsigned int index) const;
		
			v_val & operator[](unsigned int index);
		
			unsigned int size() const;

		
		private:
			v_val * data;
			unsigned int d_size;
		
	};
	
	//This function is faster then numpys 
	void dot(Matrix *, Vector *, Vector &);
	
	Vector::v_val cosineSimilarity(Vector *, Vector * );
	
	void generateProjections(Matrix &);
	
	LSH_INDEXING_TYPE hash(Matrix *, Vector *);
	
	
	
}

#endif /* Math_hpp */
