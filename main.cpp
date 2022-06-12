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
#include "headers/DataStore.hpp"

#include "Binding.cpp"

using namespace std::chrono;



int main(int argc, const char * argv[]) {
	
	
	rsvidx::LSHIndex * x = lsh(10, 2, "test");
	
	float v_vals [] = {1,2};
	lsh_add(x, "1", 2, v_vals);
	
	
	
	return 0;
}


