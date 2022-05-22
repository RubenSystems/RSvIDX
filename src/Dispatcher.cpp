//
//  Dispatcher.cpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 22/05/2022.
//

#include "Dispatcher.hpp"

namespace rs::rsvidx {
	Dispatcher::Dispatcher() : active(true) {
		threads = new std::thread [queueCount];
		queues = new std::queue<std::function<void()>> [queueCount];
		for(int i = 0; i < queueCount; i ++) {
			threads[i] = std::thread([](){});
		}
	}
}
