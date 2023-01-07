//
//  hash_table.c
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 07/01/2023.
//

#include "hash_table.h"
#include <stdbool.h>

struct hash_table init_hash_table(_hash_table_alloc allocator, _hash_table_free deallocator) {
	struct hash_table _init_val = {
		.buckets = allocator(HT_INITIAL_SIZE * sizeof(struct hash_bucket)),
		.used = 0,
		.allocated = HT_INITIAL_SIZE,
		.allocator = allocator,
		.dealloc = deallocator
	};
	return _init_val;
}


static struct hash_bucket * in_memory_ht_allocator(size_t size){
	return malloc(sizeof(struct hash_bucket) * size);
}

static void in_memory_ht_deallocator(struct hash_bucket * buckets) {
	free(buckets);
}

struct hash_table in_memory_hash_table() {
	return init_hash_table(in_memory_ht_allocator, in_memory_ht_deallocator);
}

void hash_table_add(struct hash_table * table, size_t key, size_t value) {
	size_t mask = table->allocated - 1;
	size_t index = key & mask;
	size_t probe = key;
	
	while (true) {
		if (table->buckets[index].status == BUCKET_BRIDGE ||
			table->buckets[index].status == BUCKET_EMPTY) {
			
			struct hash_bucket _new_bucket = {
				.status = BUCKET_OCCUPIED,
				.key = key,
				.value = value
			};
			
			table->buckets[index] = _new_bucket;
			return;
		} else if(table->buckets[index].key == key) {
			table->buckets[index].value = value;
		}
		
		probe >>= HT_PROBE_SHIFT;
		index = mask & (index * 5 + probe + 1);
	}
}

enum bucket_operation_response hash_table_get(struct hash_table * table, size_t key, struct hash_bucket * bucket) {
	size_t mask = table->allocated - 1;
	size_t index = key & mask;
	size_t probe = key;
	
	while (true) {
		if (table->buckets[index].key == key &&
			table->buckets[index].status == BUCKET_OCCUPIED) {
			
			*bucket = table->buckets[index];
			return BUCKET_EXISTS;
		} else if (table->buckets[index].status == BUCKET_EMPTY) {
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
	
	while (true) {
		if (table->buckets[index].key == key &&
			table->buckets[index].status == BUCKET_OCCUPIED) {
			table->buckets[index].status = BUCKET_BRIDGE;
			return BUCKET_EXISTS;
		} else if (table->buckets[index].status == BUCKET_EMPTY) {
			return BUCKET_DOES_NOT_EXIST;
		}
		
		probe >>= HT_PROBE_SHIFT;
		index = mask & (index * 5 + probe + 1);
	}
}
