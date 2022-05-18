//
//  main.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//

#include "Output.h"

#include "core/Array.hpp"

#include "headers/Math.hpp"

int main(int argc, const char * argv[]) {
	
	
	float * data = new float [5 * 5];
	
	for (int i = 0; i < 5 * 5; i ++) {
		data[i] = i;
	}
	
	rs::math::Matrix mat(5, 5, data);

	out(mat.get(0, 2));
	
	return 0;
}
