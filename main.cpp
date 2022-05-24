//
//  main.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//


#include <fstream>
#include <chrono>

#include "Output.h"

#include "headers/PersistantTypes.hpp"

using namespace std::chrono;

int main(int argc, const char * argv[]) {
//	std::string filename = "hello.rsdata";
//	{
//		int * k = new int[100];
//		long something = 1234567898765432;
//		for (int i = 0; i < 100; i ++){ k[i] = i;}
//
////		std::fstream file;
////		file.open(filename, std::ios::app | std::ios::binary);
////		file.seekg(0);
////		file.write(reinterpret_cast<char*>(&something), sizeof(long));
////		file.seekg(sizeof(long));
////		file.write(reinterpret_cast<char*>(k), 100*sizeof(int));
////		file.close();
//		delete [] k;
//	}{
//
//		int * k = new int[100];
//		long something;
////		std::fstream file;
////		file.open(filename, std::ios::in | std::ios::binary);
////		file.seekg(0);
////		file.read(reinterpret_cast<char*>(&something), sizeof(long));
////		file.seekg(sizeof(long));
////		file.read(reinterpret_cast<char*>(k), 100 * sizeof(int));
////		file.close();
////		rs::rsvidx::Permanent::shared.read(, &something, sizeof(long), 0);
////		rs::rsvidx::Permanent::shared.read(, k, sizeof(int) * 100, sizeof(long));
//
//		out(something);
//		out("");
//		for (int i = 0; i < 100; i ++) {
//			out(k[i]);
//		}
//	}
	

	{
		rs::rsvidx::PersistantArray<int> x ("array");

		for (int i = 0; i < 100; i ++) {
			x.add(i);
		}
		for (int i = 0; i < x.size(); i ++) {
			out(i<<" "<<x[i]);
		}
		
		x.save();
	}

	{
		rs::rsvidx::PersistantArray<int> x ("array");
		x.load();
		for (int i = 0; i < x.size(); i ++) {
			out(i<<" "<<x[i]);
		}

	}
	
	return 0;
}
