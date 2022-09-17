//
//  Vector.cpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 02/09/2022.
//

#include "../math/Vector.hpp"
#include <string.h>

namespace rsvidx {
	namespace math {
		Vector::Vector(unsigned int size) : d_size(size){
			data = new v_val[size];
		}

		Vector::Vector(unsigned int size, v_val * n_data) : Vector(size) {
			memmove(data, n_data, size * sizeof(v_val));
		}
		
		Vector::Vector(std::initializer_list<v_val> && list) : Vector((unsigned int)list.size()) {
			memmove(data, list.begin(), d_size * sizeof(v_val));
		}


		Vector::~Vector(){
			if (data != nullptr){
				delete [] data;
			}
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

	}
}
