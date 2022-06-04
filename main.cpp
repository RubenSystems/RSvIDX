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
	
	rs::rsvidx::InvertedIndex x (10);
	x.setFoldername("test/");
	
	char valx[5] = "RUBE";
	valx[4] = '\0';
	
//	x.add(InvertedIndexNode(ID("1223"), valx));
	x.add(InvertedIndexNode(ID("1222"), valx));
	
	
	const char * val = x.get(ID("1222"));
	out(val);

	
	return 0;
}


