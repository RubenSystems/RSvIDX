//
//  Output.h
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 17/05/2022.
//

#ifndef Output_h
#define Output_h


#define _DEBUG true

#if _DEBUG
	#include <iostream>
	#define out(value) (std::cout << value << std::endl)
#else
	#define out(value)
#endif


#endif /* Output_h */
