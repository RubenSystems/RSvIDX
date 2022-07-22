//
//  StandardDiskOperator.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 25/05/2022.
//

#include "../headers/StandardDiskOperator.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>
#include <stdio.h>
#include <system_error>

namespace fs = std::__fs::filesystem;

namespace rsvidx {
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
		fs::create_directories(fullDirectory);

		//		Error handling
		//			throw std::runtime_error("[FILE] - unable to create full directory " + std::string(fullDirectory));
		//		}
	}
	
	void StandardDiskOperator::remove(const char * filename) {
		if( ::remove( filename ) != 0 ) {
			throw std::runtime_error("[DELETE] - error deleting file");
		}
	}
}
