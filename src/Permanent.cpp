//
//  Permanent.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 22/05/2022.
//

#include "Permanent.hpp"



namespace rs::rsvidx {
	Permanent::Permanent() {}

	const Permanent Permanent::shared = Permanent();

	void Permanent::filescope(std::function<void (std::fstream &)> action) const {
		std::fstream file;
		action(file);
		file.close();
	}
	
	void Permanent::read(std::fstream & file, void * data, int size, int offset) const {
	
		//file.open(filename, std::ios::in | std::ios::binary);
		file.seekg(offset);
		file.read(reinterpret_cast<char*>(data), size);
	}

	void Permanent::write(std::fstream & file, void * data, int size, int offset) const {
		
		//file.open(filename, writetype == append ?  std::ios::app | std::ios::binary : std::ios::binary);
		file.seekg(offset);
		file.write(reinterpret_cast<char*>(data), size);
	}
}
