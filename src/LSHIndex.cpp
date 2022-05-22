//
//  LSHIndex.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 19/05/2022.
//

#include "LSHIndex.hpp"
#include "../headers/Math.hpp"

using namespace rs::rsvidx;


LSHIndex::LSHIndex(int numberOfTables, int hashSize, std::string filename):
	numberOfTables(numberOfTables), hashSize(hashSize) {
		
	tables = new rs::core::HashArray<id_type>[numberOfTables];
	
}
