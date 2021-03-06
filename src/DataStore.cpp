//
//  DataStore.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 05/06/2022.
//

#include "../headers/DataStore.hpp"

#include "../headers/StandardDiskOperator.hpp"

namespace rsvidx {
	DataStore::DataStore(const std::string & foldername) :
		foldername(foldername) {}
	
	void DataStore::set(Record & record) {
		StandardDiskOperator file = StandardDiskOperator();
		file.open((foldername + record.id.data + ".rsrecord").c_str(), DiskOperator::OpenType::WRITE);
		int currentPosition = 0;


		file.seek(currentPosition);
		file.write((ID*)&(record.id), sizeof(char) * ID::idsize);
		currentPosition += sizeof(char) * ID::idsize;

		file.seek(currentPosition);
		file.write((struct Size *)&(record.size), sizeof(record.size));
		currentPosition += sizeof(record.size);

		file.seek(currentPosition);
		file.write((void *)&record.data[0], record.size.data * sizeof(char));
		currentPosition += record.size.data * sizeof(char);
		
		file.seek(currentPosition);
		file.write(record.vector, record.size.vector * sizeof(math::Vector::v_val));

		file.close();
	}
	
	void DataStore::get(const ID & id, Record & record) {
		StandardDiskOperator file = StandardDiskOperator();
		file.open((foldername + id.data + ".rsrecord").c_str(), DiskOperator::OpenType::READ);
				
		int currentPosition = 0;

		file.seek(currentPosition);
		file.read((ID*)&(record.id), sizeof(char) * ID::idsize);
		currentPosition += sizeof(char) * ID::idsize;

		file.seek(currentPosition);
		file.read((struct Size *)&(record.size), sizeof(record.size));
		currentPosition += sizeof(record.size);


		file.seek(currentPosition);
		record.data.resize(record.size.data);
		file.read((void *)&record.data[0], sizeof(char) * record.size.data);
		currentPosition += sizeof(char) * record.size.data;
		
		

		file.seek(currentPosition);
		record.allocateVector(record.size.vector);
		file.read(record.vector, record.size.vector * sizeof(math::Vector::v_val));
		
		
		file.close();
	}
	
	void DataStore::remove(const ID & id) {
		StandardDiskOperator file = StandardDiskOperator();
		file.remove((foldername + id.data + ".rsrecord").c_str());
	}
}
