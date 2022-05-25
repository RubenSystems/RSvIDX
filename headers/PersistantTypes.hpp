//
//  PersistantTypes.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 23/05/2022.
//

#ifndef PersistantTypes_hpp
#define PersistantTypes_hpp

#include <stdio.h>
#include <fstream>
#include "../core/Array.h"

namespace rs::rsvidx {
	template <class T>
	class PersistantArray : public core::Array<T> {
		public:
			PersistantArray(std::string filename, int initialSize = 2, bool resizable = true) :
				filename(filename + ".rsarray"), loaded(false), core::Array<T>(initialSize, resizable) { }
		
			void save(){
				StateMap state = {this->currentPosition, this->maximumSize, this->resizable};
				
				std::fstream file;
				file.open(filename, std::ios::out | std::ios::binary);
				file.seekg(0);
				file.write(reinterpret_cast<char*>(&state), sizeof(StateMap));
				file.seekg(sizeof(StateMap));
				file.write(reinterpret_cast<char*>(this->data), this->currentPosition * sizeof(T));
				file.close();
				
			}
		
			void load() {
				loaded = true;
				StateMap state;
				
				std::fstream file;
				file.open(filename, std::ios::in | std::ios::binary);
				file.seekg(0);
				file.read(reinterpret_cast<char*>(&state), sizeof(StateMap));
				this->resize(state.maximumSize);
				this->currentPosition = state.currentPosition;
				this->maximumSize = state.maximumSize;
				this->resizable = state.resizable;
				
				file.seekg(sizeof(StateMap));
				file.read(reinterpret_cast<char*>(this->data), state.currentPosition * sizeof(T));
				file.close();
				
			}
		
			
		private:
			std::string filename;
		
			bool loaded;
		
			struct StateMap {
				int currentPosition;
				int maximumSize;
				bool resizable;
			};
	};
}

#endif /* PersistantTypes_hpp */
