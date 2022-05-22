//
//  Permanent.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 22/05/2022.
//

#include "Permanent.hpp"

#include <fstream>

namespace rs::rsvidx {
	Permanent::Permanent() {}

	const Permanent Permanent::shared = Permanent();

	void Permanent:: read(std::string filename, void * data, int size, int offset) const {
		std::fstream file;
	
		file.open("test.rsdata", std::ios::in | std::ios::binary);
		file.seekg(offset);
		file.read(reinterpret_cast<char*>(data), size);
		file.close();
	}

	void Permanent::write(std::string filename, void * data, int size, int offset) const {
		std::fstream file;
		file.open("test.rsdata", std::ios::out | std::ios::binary);
		file.seekg(offset);
		file.write(reinterpret_cast<char*>(data), size);
		file.close();
	}
}
