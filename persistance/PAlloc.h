//
//  PAlloc.h
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 25/08/2022.
//

#ifndef PAlloc_h
#define PAlloc_h



#include <string>
#include <system_error>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


namespace rsvidx {
	namespace persistance {
		template <typename T>
		class PAlloc {
			public:
				typedef unsigned long index_type;
				
			
				/**
				 Creates an allocator. Initally pointing to unallocated data.
				 */
				PAlloc() : allocated(0), filename("") {
					
				}
			
				void set_filename(const std::string & n_filename) {
					filename = n_filename + ".rspcs";
					file = ::open(filename.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
					struct stat file_info;

					
					if (fstat(file, &file_info) == -1 || file_info.st_size == 0) {
						data = nullptr;
						allocated = 0;
					} else {
						
						
						data = (T *)mmap(NULL, file_info.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, file, 0);
						allocated = file_info.st_size / sizeof(T);
					}
				}
		
			
				PAlloc(const PAlloc & copy) {
					file = copy.file;
					filename = copy.filename;
					allocate(copy.allocatedSize());
					
					for (index_type i = 0; i < copy.allocatedSize(); i ++) {
						operator[](i) = copy[i];
					}
				}
				
				PAlloc(PAlloc && move) {
					file = move.file;
					data = move.data;
					allocated = move.allocatedSize();
					filename = std::move(move.filename);
					move.data = nullptr;
				}
				
				PAlloc & operator = (const PAlloc & copy) {
					file = copy.file;
					filename = copy.filename;
					allocate(copy.allocatedSize());
					for (index_type i = 0; i < copy.allocatedSize(); i ++) {
						operator[](i) = copy[i];
					}
					return *this;
				}
				
				PAlloc & operator = (PAlloc && move) {
					delete data;
					file = move.file;
					data = move.data;
					allocated = move.allocatedSize();
					filename = std::move(move.filename);
					move.data = nullptr;
					
					return *this;
				}
				
				/**
				 Destructor. Will free the amount of memory allocated
				 
				 Notes:
					- Does not hit the destructor of the objects in its allocation. That should be done by calling ::destroy(index: )
				 */
				~PAlloc() {
					::close(file);
					munmap(data, allocated * sizeof(T));
				}
			
			
				T operator[](index_type index) const {
					if (index > allocated) { throw std::runtime_error("[ALLOCATOR] - cannot access element that is out of bounds"); }
					return data[index];
				}
			
				T & operator[](index_type index) {
					if (index > allocated) { throw std::runtime_error("[ALLOCATOR] - cannot access element that is out of bounds"); }
					return data[index];
				}
			
				/**
				 Allocates memory of size blocks.
				 
				 Notes:
					- Preserves previously allocated data.
					- If there was previous data, it will move it over.
				 
				 Warning:
					- If the size of previous data > size, it will truncate the data and not destroy it.
					- You need to make sure that the data is being destroyed
				 */
				void allocate(index_type size) {
					if (filename == "") {
						throw std::runtime_error("[FILE] - filename not set, unable to allocate: " + filename);
					}
					// Check so if alloc is called after allocating from file, it will not realloc pointlessly;
					if (size == allocated) {
						return;
					}
					
					index_type allocating_size = size * sizeof(T);
					if (ftruncate(file, allocating_size) == -1) {
//						perror("error: ");
//						exit(0);
						throw std::runtime_error(std::string("[FILE] - unable to resize file: ") + filename.c_str());
					}

					T* new_data = (T *)mmap(NULL, allocating_size, PROT_WRITE | PROT_READ, MAP_SHARED, file, 0);
					if (data != nullptr && allocated == 0) {
						for (int i = 0; i < allocated; i ++) {
							new_data[i] = std::move(data[i]);
						}
						munmap(data, allocated);
					}
					
					data = new_data;
					allocated = size;
				}
			
				/**
				 Size. Returns the amount of blocks (where a block is sizeof(T)) have been allocated.
				 */
				index_type allocatedSize() const {
					return allocated;
				}
			
			
			
			public:
				T * data;
				int file;
				index_type allocated;
				std::string filename = "";
		};
	}
}


#endif /* PAlloc_h */
