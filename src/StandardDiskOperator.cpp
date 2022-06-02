//
//  StandardDiskOperator.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 25/05/2022.
//

#include "StandardDiskOperator.hpp"
#include <fstream>
#include <sstream>
#include "../Output.h"
#include <sys/stat.h>

namespace rs::rsvidx {
	void StandardDiskOperator::open(const char * filename, OpenType type){
		file = new std::fstream;
		createDirectory(filename);
		((std::fstream*)file)->open(filename, (type == READ ? std::ios::in : std::ios::out) | std::ios::binary);
		
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
	
	bool StandardDiskOperator::exists(const char * filename) {
		struct stat buffer;
		return (stat (filename, &buffer) == 0);
	}
	
	std::string strippingFilenames(const std::string forFullPath) {
		std::string fullDirectory = "";
		std::string word;
		std::istringstream str(forFullPath);
		while(std::getline(str, word, '/')) {
			if (word.find('.') == std::string::npos ) {
				fullDirectory += word + "/";
			}
		}
		
		if(fullDirectory[0] == '/') {
			fullDirectory = std::string(fullDirectory.begin() + 1, fullDirectory.end());
		}
		return fullDirectory;
	}


	bool fileExists(const std::string & filepath) {
		struct stat buffer;
		return (stat (filepath.c_str(), &buffer) == 0);
	}
	
	void StandardDiskOperator::createDirectory(const char * forString) {
			std::string fullDirectory = strippingFilenames(forString);
			if(fileExists(fullDirectory)) {
				return;
			}
			
			std::string command = "mkdir -p " + fullDirectory;
			char charArr[command.length() + 1];
			strcpy(charArr, command.c_str());
			
			std::system(charArr);
		}
}
