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
	
	
	rsvidx::DataStore store("storetest/");
	
	float data [] = {12,34};
	rsvidx::Record rec(ID("HELLO"), "hello there", 2, data);
	
	store.set(rec);
	
	rsvidx::Record x;
	store.get(ID("HELLO"), x);
	out(x.data);
	
	
	return 0;
}


