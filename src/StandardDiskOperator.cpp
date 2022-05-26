//
//  StandardDiskOperator.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 25/05/2022.
//

#include "StandardDiskOperator.hpp"
#include <fstream>

namespace rs::rsvidx {
	void StandardDiskOperator::open(const char * filename, OpenType type){
		this->file = new std::fstream;
		((std::fstream *)file)->open(filename, (type == READ ? std::ios::in : std::ios::out) | std::ios::binary);
	}
	
	void StandardDiskOperator::write(void * data, int size) {
		if (((std::fstream *)file)->is_open() && !((std::fstream *)file)->write(reinterpret_cast<char *>(data), size)) {
			throw std::runtime_error("[WRITE] - write error");
		}
	}
	
	void StandardDiskOperator::read(void * data, int size) {
		if (((std::fstream *)file)->is_open() && !((std::fstream *)file)->read(reinterpret_cast<char *>(data), size)) {
			throw std::runtime_error("[READ] - read error");
		}
	}
	
	void StandardDiskOperator::seek(int distance) {
		if (((std::fstream *)file)->is_open()) {
			((std::fstream *)file)->seekg(distance);
		}
	}
	
	void StandardDiskOperator::close() {
		if(((std::fstream *)file)->is_open()) {
			((std::fstream *)file)->close();
		}
	}
}
