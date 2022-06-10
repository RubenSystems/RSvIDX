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
	

	
	rs::rsvidx::Record rec (ID("jeff"), "{'1': '2'}");
	
	store.set(rec);
	out(store.get(ID("jeff")).data);
	
	
	
	return 0;
}


