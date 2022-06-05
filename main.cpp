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
#include "headers/InvertedIndex.hpp"

using namespace std::chrono;



int main(int argc, const char * argv[]) {
	
	rs::core::Array<int> array;
	
	array.add(1);
	array.add(2);
	array.add(3);
	array.add(4);
	array.add(5);
	
	array.insert(1, 10);
	
	for(int i = 0; i < array.size(); i ++) {
		out(array[i]);
	}
	
	return 0;
}


