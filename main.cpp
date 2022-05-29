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
		
//	rs::rsvidx::PersistantArray<int> x ("test");
	rs::rsvidx::LSHTable x (3, 2);
	
	x.setFoldername("testfolder/");
	
//	rs::math::Vector::v_val values [] = {1,2,3};
//	rs::math::Vector vec(3, values);
//	x.add(vec, "rubeniscoo");
	
	rs::math::Vector::v_val values [] = {6, 9, 100};
	rs::math::Vector vec(3, values);
//	x.add(vec, ID("rubenisco2"));
	
	rs::core::Array<LSH_ID_TYPE> * result = x.get(vec);
	for(int i = 0; i < result->size(); i++) {
		out(result->operator[](i).data);
	}
	
//	x.add(1, 23);
	
	
	
	return 0;
}
