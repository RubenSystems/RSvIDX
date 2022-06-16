# RSvIDX
The next generation vector indexing tool. Developed as a sucessor to the older RSmIDX. 

___RSvIDX takes everything great about RSmIDX and makes it better:___

- faster and more efficient math library
- optimised disk operations
- better memory performance
- no dependencies (new build size is 98% smaller)

RSvIDX also comes with general purpose indexes: 
* Ordered 
* Inverse 

and an on-disk document datastore which can store documents in any string format. 

### Vector indexing
RSvIDX can be used for general purpose vector indexing and similarity search. Applications include:
* Semantic search 
* Document deduplication 
* Recommendation 
* Classification 
* Image search 
* Reverse image search 
* Audio similarity (like Shazam)
* Q&A 

### Distributable
RSvIDX is a distributable system. Since the indexes are independent of one another, different indexes can be stored on different machines. 

### Fast and efficient
RSvIDX has it’s own math library for ultra efficient and low energy computations. Since it is written in c++ with c bindings, it runs on several devices, from mobile phones to servers. 

### Bindings 
RSvIDX has C bindings, Python bindings (in a C style) and Python bindings (in a Python style).

### Example:
Try out https://apps.apple.com/gb/app/headlines-today/id1363257410 on the App Store for a semantic search example. 

