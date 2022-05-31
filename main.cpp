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
#include "headers/LSHTable.hpp"

using namespace std::chrono;



int main(int argc, const char * argv[]) {
	
	rs::rsvidx::LSHTable table(3) ;
	table.setFoldername("table1/");
	
	float vvals [] = {1,2,3};
	rs::math::Vector vec(3, vvals);
//	table.add(vec, ID("a is b"));
	rs::core::Array<ID> * result = table.get(vec);
	for(int i = 0; i < result->size(); i ++) {
		out(result->operator[](i).data);
	}
	
	
	return 0;
}


