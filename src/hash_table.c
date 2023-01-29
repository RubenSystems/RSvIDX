//
//  hash_table.c
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 07/01/2023.
//


#include "include/hash_table.h"
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include "../smac-alloc/src/include/palloc.h"

struct hash_bucket * buckets(struct hash_table * table) {
	return (struct hash_bucket *)(table->raw_data + sizeof(size_t));
}

static size_t used(struct hash_table * table) {
	return *(size_t *)table->raw_data;
}

static struct hash_bucket * _alloc(struct hash_table * table, size_t size){
	_resize_file(table->_pfd, size);
	void * new_ptr = _palloc(table->_pfd, size, NULL, 0);
	memset(new_ptr, 0, size);
	return new_ptr;
}

static void _dealloc(void * buckets, size_t size) {
	// TODO: - MEMORY LEAK!
	munmap(buckets, size);
}



static void _add_no_resize(struct hash_table * table, size_t key, size_t value) {
	size_t mask = table->allocated - 1;
	size_t index = key & mask;
	size_t probe = key;
	
	while (true) {
		if (buckets(table)[index].status == BUCKET_BRIDGE ||
			buckets(table)[index].status == BUCKET_EMPTY) {
			
			struct hash_bucket _new_bucket = {
				.status = BUCKET_OCCUPIED,
				.key = key,
				.value = value
			};
			
			buckets(table)[index] = _new_bucket;
			return;
		} else if(buckets(table)[index].key == key) {
			buckets(table)[index].value = value;
		}
		
		probe >>= HT_PROBE_SHIFT;
		index = mask & (index * 5 + probe + 1);
	}
}

static void _resize_table(struct hash_table * table, size_t new_size) {
	size_t old_allocated_size = table->allocated;
	struct hash_bucket * old_buckets = buckets(table);
	size_t old_used = *(size_t *)table->raw_data;
	void * old_data_ptr = table->raw_data;
	
	table->raw_data = _alloc(table, (sizeof(struct hash_bucket) * new_size) + sizeof(size_t));
	table->allocated = new_size;
	*(size_t *)table->raw_data = old_used;
	
	
	size_t moved = 0;
	for (size_t i = 0; i < old_allocated_size; i ++) {
		if (old_buckets[i].status == BUCKET_OCCUPIED) {
			_add_no_resize(table, old_buckets[i].key, old_buckets[i].value);
			
			if (++moved >= used(table)) {
				break;
			}
		}
	}
	_dealloc(old_data_ptr, sizeof(size_t) + (sizeof(struct hash_bucket) * old_allocated_size));
}

struct hash_table init_phash_table(const char * filename) {
	int fd = _open_file(filename);
	
	size_t alloc_size = _file_size(fd);
	
	
	struct hash_table _init_val = {
		._pfd = fd,
	};
	
	if (alloc_size > 0) {
		_init_val.raw_data = _palloc(fd, alloc_size, NULL, 0);
		_init_val.allocated = (alloc_size - sizeof(size_t)) / sizeof(struct hash_bucket);
	} else {
		_init_val.raw_data = _palloc(fd, (HT_INITIAL_SIZE * sizeof(struct hash_bucket)) + sizeof(size_t), NULL, 0);
		_init_val.allocated = HT_INITIAL_SIZE;
		*((size_t *)_init_val.raw_data) = 0;
	}
	
	
	
	return _init_val;
}

void hash_table_add(struct hash_table * table, size_t key, size_t value) {
	if ((*(size_t*)table->raw_data)++ >= (size_t)((2/3.0) * table->allocated)) {
		
		_resize_table(table, table->allocated * 2);
	}
	
	_add_no_resize(table, key, value);

}

enum bucket_operation_response hash_table_get(struct hash_table * table, size_t key, size_t * value) {
	size_t mask = table->allocated - 1;
	size_t index = key & mask;
	size_t probe = key;
	
	while (true) {
		if (buckets(table)[index].key == key &&
			buckets(table)[index].status == BUCKET_OCCUPIED) {
			
			*value = buckets(table)[index].value;
			return BUCKET_EXISTS;
		} else if (buckets(table)[index].status == BUCKET_EMPTY) {
			return BUCKET_DOES_NOT_EXIST;
		}
		
		probe >>= HT_PROBE_SHIFT;
		index = mask & (index * 5 + probe + 1);
	}
}


enum bucket_operation_response hash_table_delete(struct hash_table * table, size_t key) {
	size_t mask = table->allocated - 1;
	size_t index = key & mask;
	size_t probe = key;
	
//	if (table->used - 1 <= (1/3) * table->allocated) {
//		_resize_table(table, table->allocated * 2);
//	}
	
	while (true) {
		if (buckets(table)[index].key == key &&
			buckets(table)[index].status == BUCKET_OCCUPIED) {
			buckets(table)[index].status = BUCKET_BRIDGE;
			return BUCKET_EXISTS;
		} else if (buckets(table)[index].status == BUCKET_EMPTY) {
			return BUCKET_DOES_NOT_EXIST;
		}
		
		probe >>= HT_PROBE_SHIFT;
		index = mask & (index * 5 + probe + 1);
	}
}


void hash_table_free(struct hash_table * table) {
	_dealloc(table->raw_data, (sizeof(struct hash_bucket) * table->allocated) + sizeof(size_t));
}
