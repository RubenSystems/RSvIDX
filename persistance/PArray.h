//
//  PArray.h
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 24/08/2022.
//

#ifndef PArray_h
#define PArray_h


#include "PAlloc.h"
#include "../RSCore/Array.h"




namespace rsvidx {
	namespace persistance {
		
		template <class T>
		class PArray : public core::Array<T, PAlloc<T>> {
			
			typedef core::Array<T, PAlloc<T>> base;
			
			public:
				PArray(const std::string & n_filename) : core::Array<T, PAlloc<T>>() {
					base::set_filename(n_filename);
					base::currentSize = core::Array<T, PAlloc<T>>::allocated;
				}
				
				~PArray() {
					if (base::currentSize > 0)
						base::allocate(base::currentSize);
				}
			
				PArray(const PArray & copy) = delete;
				
				PArray(PArray && move) = delete;
				
				PArray & operator = (const PArray & copy) = delete;
				
				PArray & operator = (PArray && move) {
					base::currentSize = 0;
					base::operator= (std::move(move));
					
					return *this;
				}
				
				

		};
	}
}

#endif /* PArray_h */
