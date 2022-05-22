//
//  main.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//


#include <fstream>
#include <chrono>

#include "Output.h"

#include "Permanent.hpp"

using namespace std::chrono;

int main(int argc, const char * argv[]) {
	
	int * values = new int [100];
	memset(values, 0, sizeof(int) * 100);
//	for(int i = 0; i < 100; i ++) {
//		values[i] = i;
//	}
//	rs::rsvidx::Permanent::shared.write("values.rsdata", values, 100 * sizeof(int), 0);
	
	rs::rsvidx::Permanent::shared.read("values.rsdata", values, 10 * sizeof(int), 10 * sizeof(int));
	for(int i = 0; i < 100; i ++){
		out(values[i]);
	}
	
	return 0;
}
