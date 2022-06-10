//
//  DataStore.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 05/06/2022.
//

#include "DataStore.hpp"
#include "../headers/StandardDiskOperator.hpp"
#include <fstream>
#include "../Output.h"

namespace rs::rsvidx {
	DataStore::DataStore(const std::string & foldername) :
		foldername(foldername) {}
	
	void DataStore::set(const Record & record) {
		StandardDiskOperator file = StandardDiskOperator();
		out((foldername + record.id.data + ".rsrecord"));
		file.open((foldername + record.id.data + ".rsrecord").c_str(), DiskOperator::OpenType::WRITE);
		int currentPosition = 0;


		file.seek(currentPosition);
		file.write((ID*)&(record.id), sizeof(char) * ID::idsize);
		currentPosition += sizeof(char) * ID::idsize;

		file.seek(currentPosition);
		file.write((struct Size *)&(record.size), sizeof(record.size));
		currentPosition += sizeof(record.size);

		file.seek(currentPosition);

		file.write(record.data, record.size.data * sizeof(char));
		currentPosition += record.size.data * sizeof(char);
		
//		file.seek(currentPosition);
//		file.write(record.vector.getbuffer(), record.vector.size() * sizeof(rs::math::Vector::v_val));

		file.close();
	}
	
	Record DataStore::get(const ID & id) {
		StandardDiskOperator file = StandardDiskOperator();
		out((foldername + id.data + ".rsrecord"));
		file.open((foldername + id.data + ".rsrecord").c_str(), DiskOperator::OpenType::READ);
		
		Record record;
		
		int currentPosition = 0;

		file.seek(currentPosition);
		file.read((ID*)&(record.id), sizeof(char) * ID::idsize);
		currentPosition += sizeof(char) * ID::idsize;

		file.seek(currentPosition);
		file.read((struct Size *)&(record.size), sizeof(record.size));
		currentPosition += sizeof(record.size);



		file.seek(currentPosition);
		record.data = new char [record.size.data + 1];
		
		file.read(record.data, sizeof(char) * record.size.data);
		record.data[ sizeof(char) * record.size.data] = 0;
		
//		file.seek(currentPosition);
//		file.read(record.data, record.size.data * sizeof(char));
//		currentPosition += record.size.data * sizeof(char);
		
//		rs::math::Vector(record.size.vector);
//		
//		file.seek(currentPosition);
//		file.read(record.vector.getbuffer(), record.vector.size() * sizeof(rs::math::Vector::v_val));

		file.close();
		
		
		return record;
		
	}
}
