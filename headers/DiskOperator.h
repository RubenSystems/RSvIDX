//
//  DiskOperator.h
//  RSvIDX
//
//  Created by Ruben Ticehurst-James on 25/05/2022.
//

#ifndef DiskOperator_h
#define DiskOperator_h

namespace rs::rsvidx {
	class DiskOperator {
		
		public:
			enum OpenType {
				READ,
				WRITE
			};
		
			virtual void open(const char *, OpenType) = 0;
			
			virtual void write(void *, int) = 0;
			
			virtual void read(void *, int) = 0;
			
			virtual void seek(int) = 0;
			
			virtual void close() = 0;
			
			virtual bool exists(const char *) = 0;
		
	};

}

#endif /* DiskOperator_h */
