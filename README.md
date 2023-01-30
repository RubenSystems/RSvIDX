# RSvIDX

## Vector indexing system

### Vector indexing

**RSvIDX can be used for general purpose vector indexing and similarity search. Applications include:**

- Semantic search
- Document deduplication
- Recommendation
- Classification
- Image search
- Reverse image search
- Audio similarity (like Shazam)
- Q&A


### Features
- fast and efficient math library
- optimised persistant operations (you now no longer need to explicitly save the index as this is scheduled automatically)
- better in-memory performance compaired to RSvIDX_v3
- no dependencies (new build size is 98% smaller)
- Usable in C with bindings in Python3
- No intermideate C bindings


### Example:

Try out https://apps.apple.com/gb/app/headlines-today/id1363257410 on the App Store for a semantic search example.


# Installation
(For Python3)

```
pip3 install rsvidx
```


# Usage
(For Python3)

***Create an index***
You can finetune number of buckets to your use case. Less buckets results in higher accuracy but more items to brute force search. Less buckets results in lower accuracy but fewer items to brute force search.
```python3 
import rsvidx
file_name = "test.index"
number_of_buckets = 8
dimensions = 4
index = rsvidx.Similarity(file_name, number_of_buckets, dimensions)
```



***Add item to index***
```python3
add_vector = [1,2,3,4]
add_uid = "1234"
index.add(add_vector, add_uid)
```



***Get items from index***

This will get items that are similar to the get vector
```python3
get_vector = [1,2,3,4]
results = index.get(get_vector)
```



***Remove items from index***
```python3 
remove_uid = "1234"
index.remove(remove_uid)
```



