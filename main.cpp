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
#include "headers/OrderedIndex.hpp"

using namespace std::chrono;



int main(int argc, const char * argv[]) {
	
	rs::rsvidx::OrderedIndex x;
	
	x.insert({ID("hi1"), 10});
	x.insert({ID("hi2"), 20});
	x.insert({ID("hi3 "), 30});
	
	
	x.save("test");
//
//
	auto result = x.getGreaterThan(19);
	for (int i = 0; i < result.size(); i ++) {
		out(result[i].id.data);
	}
	
	
	
	return 0;
}


