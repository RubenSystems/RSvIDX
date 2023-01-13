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
	int64_t				value;
};

struct hash_table {
	void * 	raw_data;
	size_t 					allocated;
	int 					_pfd;
};

struct hash_bucket * buckets(struct hash_table * table);

struct hash_table init_phash_table(const char * filename);

void hash_table_add(struct hash_table * table, size_t key, size_t value) ;

enum bucket_operation_response hash_table_get(struct hash_table * table, size_t key, size_t * value);

enum bucket_operation_response hash_table_delete(struct hash_table * table, size_t key);

void hash_table_free(struct hash_table * table) ;

#endif /* hash_table_h */
