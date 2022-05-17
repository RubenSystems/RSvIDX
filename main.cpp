//
//  main.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//

#include "Output.h"

#include "headers/Array.hpp"

int main(int argc, const char * argv[]) {
	// insert code here...
	
	rs::core::Array<int> arr;
	
	
	
	
	for(int i = 0; i < 10; i ++) {
		arr.add(i);
		out(arr[i]);
		
	}
	
	
	return 0;
}
