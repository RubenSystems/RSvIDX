//
//  Random.cpp
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 02/09/2022.
//

#include "Random.hpp"

namespace rsvidx {
	namespace math {
		Random Random::shared = Random();

		Random::Random() {
			this->distribution = std::uniform_real_distribution<r_type>(-1, 1);
		}

		Random::r_type Random::generate() {
			return this->distribution(generator);
		}
	}
}
