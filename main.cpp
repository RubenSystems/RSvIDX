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

using namespace std::chrono;



int main(int argc, const char * argv[]) {
	
	
	rs::rsvidx::DataStore store("data/");
	
	float v_val [] = {1,2,3};
	
	rs::math::Vector vec(3, v_val);
	
	rs::rsvidx::Record rec (ID("hi"), "i am cool", 9, vec);
	
	store.set(rec);
	
	
	
	return 0;
}


