//
//  hash_table.h
//  RSvIDX_V4
//
//  Created by Ruben Ticehurst-James on 07/01/2023.
//

#ifndef hash_table_h
#define hash_table_h

#include <stdio.h>
#include <stdlib.h>

#define HT_INITIAL_SIZE 8
#define HT_PROBE_SHIFT 5

/*
 Check this out:
 https://github.com/python/cpython/blob/main/Objects/dictobject.c#L143
 */

enum bucket_flag {
	BUCKET_OCCUPIED = 2,
	BUCKET_BRIDGE = 1,
	BUCKET_EMPTY = 0
};

enum bucket_operation_response {
	BUCKET_EXISTS,
	BUCKET_DOES_NOT_EXIST
};

// TODO: - Don't specalise size_t size_t
struct hash_bucket {
	enum bucket_flag 	status;
	size_t 				key;
	size_t 				value;
};

typedef struct hash_bucket * 	(* _hash_table_alloc)(size_t);
typedef void 					(* _hash_table_free)(struct hash_bucket *);

struct hash_table {
	struct hash_bucket * 	buckets;
	size_t 					used;
	size_t 					allocated;
	_hash_table_alloc 		_allocator;
	_hash_table_free		_dealloc;
};

struct hash_table init_hash_table(_hash_table_alloc allocator, _hash_table_free deallocator);

struct hash_table in_memory_hash_table(void);

void hash_table_add(struct hash_table * table, size_t key, size_t value) ;

enum bucket_operation_response hash_table_get(struct hash_table * table, size_t key, size_t * value);

enum bucket_operation_response hash_table_delete(struct hash_table * table, size_t key);

#endif /* hash_table_h */
