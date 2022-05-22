//
//  Dispatcher.hpp
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 22/05/2022.
//

#ifndef Dispatcher_hpp
#define Dispatcher_hpp

#include <stdio.h>

#include <thread>
#include <queue>
#include <functional>


/*
 this class does not work. do not use it. if you use it, your code will not run. 
 */
namespace rs::rsvidx {
	class Dispatcher {
		
		public:
			Dispatcher();
			
			enum Queue{
				highpriority = 0,
				io = 1
			};
		
		private:
			const static int queueCount = 2;
			std::thread * threads;
			std::queue<std::function<void()>> * queues;
		
			bool active;
			
		
	};
}

#endif /* Dispatcher_hpp */
