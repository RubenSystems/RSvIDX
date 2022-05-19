//
//  main.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//


#include <fstream>
#include "Output.h"

#include "core/HashArray.h"

#include "headers/Math.hpp"

int main(int argc, const char * argv[]) {

	rs::core::HashArray<int> x(2);

	x.add(0, 55);

	out(x[0][0]);

	
	
//	rs::core::Array<int> x (10);
	
//	for(int i = 0; i <= 100; i++){
//		x.add(i);
//	}
	
//	std::fstream file;
//	uint64_t myuint = 0xFFFF;
//	file.open("test.rsdata", std::ios::out | std::ios::binary);
//	file.write(reinterpret_cast<char*>(&myuint), sizeof(myuint)); // ideally, you should memcpy it to a char buffer.
//	file.close();
//
//	std::fstream fil;
//	uint64_t newuint;
//
//	fil.open("test.rsdata", std::ios::in | std::ios::binary);
//	fil.read(reinterpret_cast<char*>(&newuint), sizeof(uint64_t));
//	fil.close();
//
//	out(newuint);
	
	return 0;
}
