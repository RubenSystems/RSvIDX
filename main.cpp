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
#include "headers/PersistantTypes.hpp"

using namespace std::chrono;

int main(int argc, const char * argv[]) {

	rs::rsvidx::PersistantMultimap<int> x ("test/", sizeof(LSH_INDEXING_TYPE));
	
	x.add(1, 23);
	
	
	return 0;
}
