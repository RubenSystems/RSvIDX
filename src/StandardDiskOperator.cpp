//
//  StandardDiskOperator.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 25/05/2022.
//

#include "StandardDiskOperator.hpp"
#include <fstream>
#include "../Output.h"

namespace rs::rsvidx {
	void StandardDiskOperator::open(const char * filename, OpenType type){
		file = new std::fstream;
		((std::fstream*)file)->open(filename, (type == READ ? std::ios::in : std::ios::out) | std::ios::binary);
		out(filename);
	}
	
	void StandardDiskOperator::write(void * data, int size) {
		((std::fstream*)file)->write(reinterpret_cast<char *>(data), size);

	}
	
	void StandardDiskOperator::read(void * data, int size) {
		((std::fstream*)file)->read(reinterpret_cast<char *>(data), size);

	}
	
	void StandardDiskOperator::seek(int distance) {
		((std::fstream*)file)->seekg(distance);
	}
	
	void StandardDiskOperator::close() {
		((std::fstream*)file)->close();
	}
}
