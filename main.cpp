//
//  main.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//


#include <fstream>
#include <chrono>

#include "Output.h"

#include "config.h"
#include "headers/LSHIndex.hpp"

using namespace std::chrono;



int main(int argc, const char * argv[]) {
	
	float vvals [] = {1,2,3};
	rs::math::Vector vec(3, vvals);
	
	rs::rsvidx::LSHIndex index(10, 3, "index") ;

	
	index.add(vec, ID("hello rr"));
	rs::core::Array<LSH_ID_TYPE> result = index.get(vec);
	
	for (int i = 0; i < result.size(); i ++) {
		out(result[i].data);
	}
	
	
	return 0;
}


