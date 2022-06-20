from ctypes import *
import json

rsvidx = CDLL('bin/rsvidx.so')

""" Function arg/ret for lsh index """
rsvidx.lsh_result_get_size.argtypes = [c_void_p]
rsvidx.lsh_result_get_size.restype = c_int

rsvidx.lsh_result_delete.argtypes = [c_void_p]
rsvidx.lsh_result_delete.restype = None

rsvidx.lsh_result_get_id.argtypes = [c_void_p, c_int]
rsvidx.lsh_result_get_id.restype = c_char_p

rsvidx.lsh_get.argtypes = [c_void_p, c_uint, POINTER(c_float)]
rsvidx.lsh_get.restype = POINTER(c_char_p)

rsvidx.lsh.argtypes = [c_int, c_int, c_char_p]
rsvidx.lsh.restype = c_void_p

rsvidx.lsh_add.argtypes = [c_void_p, c_char_p, c_uint, POINTER(c_float)]
rsvidx.lsh_add.restype = None

rsvidx.lsh_remove.argtypes = [c_void_p, c_char_p, c_uint, POINTER(c_float)]
rsvidx.lsh_remove.restype = None

rsvidx.lsh_get.argtypes = [c_void_p, c_uint, POINTER(c_float)]
rsvidx.lsh_get.restype = c_void_p


rsvidx.close_lsh.argtypes = [c_void_p]
rsvidx.close_lsh.restype = None


"""

Human:
Wrapper for lsh index

GPT-3:
This is a class that allows you to perform similarity searches on a dataset.

The constructor takes in the number of tables, dimensions, and filename.

The get function takes in an array and returns a list of strings.

The add function adds a uid and array.

The remove function removes a uid and array.

"""
class Similarity:

	_index = None

	def __init__(self, tables: int, dimensions: int, filename: str):
		self._index = rsvidx.lsh(tables, dimensions, bytes(filename, "utf-8"))

	def get(self, array: [float]) -> [str]:
		array_pointer = (c_float*len(array))(*array)

		result = rsvidx.lsh_get(self._index, len(array), array_pointer )
		toReturn = [
			rsvidx.lsh_result_get_id(result, x).decode()
			for x in range(rsvidx.lsh_result_get_size(result))
		]
		rsvidx.lsh_result_delete(result)
		return toReturn

	def add(self, uid: str, array: [float]) :
		array_pointer = (c_float*len(array))(*array)
		rsvidx.lsh_add(self._index, bytes(uid, "utf-8"), len(array), array_pointer)

	def remove(self, uid: str, array: [float]): 
		array_pointer = (c_float*len(array))(*array)
		rsvidx.lsh_remove(self._index, bytes(uid, "utf-8"), len(array), array_pointer)


	def __del__(self):
		rsvidx.close_lsh(self._index)


""" Function arg/ret for ordered index """
rsvidx.ordered.argtypes = [c_char_p]
rsvidx.ordered.restype = c_void_p

rsvidx.ordered_insert.argtypes = [c_void_p, c_char_p, c_float]
rsvidx.ordered_insert.restype = None

rsvidx.ordered_get_greater.argtypes = [c_void_p, c_float]
rsvidx.ordered_get_greater.restype = c_void_p

rsvidx.ordered_get_less.argtypes = [c_void_p, c_float]
rsvidx.ordered_get_less.restype = c_void_p

rsvidx.ordered_result_get_size.argtypes = [c_void_p]
rsvidx.ordered_result_get_size.restype = c_int

rsvidx.ordered_result_get_id.argtypes = [c_void_p, c_int]
rsvidx.ordered_result_get_id.restype = c_char_p

rsvidx.close_ordered.argtypes = [c_void_p, c_char_p]
rsvidx.close_ordered.restype = None

rsvidx.ordered_result_delete.argtypes = [c_void_p]
rsvidx.ordered_result_delete.restype = None

"""

Human:
Wrapper for ordered index

GPT-3:
This class is an ordered index, which is used to store data so that it can be retrieved efficiently.

 The insert function inserts a new value into the index
 
 The getGreater function retrieves all values that are greater than a given value
 
 The getLess function retrieves all values that are less than a given value.

"""
class Ordered:
	_filename = None
	_index = None
	
	def __init__(self, filename):
		self._filename = bytes(filename, "utf-8")
		self._index = rsvidx.ordered(self._filename)
		
	def insert(self, id: str, value: float):
			rsvidx.ordered_insert(self._index, bytes(id, "utf-8"), value)
			
	def getGreater(self, value: float) -> str:
		result = rsvidx.ordered_get_greater(self._index, value)
		size = rsvidx.ordered_result_get_size(result)
		toReturn = [
			rsvidx.ordered_result_get_id(result, x).decode()
			for x in range(size)
		]
		
		rsvidx.ordered_result_delete(result)
		return toReturn
		
	def getLess(self, value: float) -> str:
		result = rsvidx.ordered_get_less(self._index, value)
		
		size = rsvidx.ordered_result_get_size(result)
		
		toReturn = [
			rsvidx.ordered_result_get_id(result, x).decode()
			for x in range(size)
		]
		print("here")
		rsvidx.ordered_result_delete(result)
		return toReturn
		
	def __del__(self):
		rsvidx.close_ordered(self._index, self._filename)
	





""" Function arg/ret for inverted index """
rsvidx.inverted.argtypes = [c_int, c_char_p]
rsvidx.inverted.restype = c_void_p

rsvidx.inverted_add.argtypes = [c_void_p, c_char_p, c_char_p]
rsvidx.inverted_add.restype = None

rsvidx.inverted_get.argtypes = [c_void_p, c_char_p]
rsvidx.inverted_get.restype = c_void_p

rsvidx.inverted_result_get_size.argtypes = [c_void_p]
rsvidx.inverted_result_get_size.restype = c_int

rsvidx.inverted_result_get_id.argtypes = [c_void_p, c_int]
rsvidx.inverted_result_get_id.restype = c_char_p

rsvidx.inverted_result_delete.argtypes = [c_void_p]
rsvidx.inverted_result_delete.restype = None

rsvidx.close_inverted.argtypes = [c_void_p]
rsvidx.close_inverted.restype = None

"""

Human:
Wrapper for Inverted index

GPT-3:
This class is an inverted index, used for indexing document collections for fast document retrieval. It has three functions: __init__(), add(), and get().

__init__() creates a new inverted index with a given number of buckets and foldername.

add() adds a given document ID and data to the index.

get() looks up a given data in the index and returns a list of document IDs associated with that data.

"""
class Inverted:
	_index = None
	
	def __init__(self, buckets: int, foldername: str):
		self._index = rsvidx.inverted(buckets, bytes(foldername, "utf-8"))
		
	def add(self, id: str, data: str):
		rsvidx.inverted_add(self._index, bytes(data, "utf-8"), bytes(id, "utf-8"))
		
	def get(self, data: str) -> [str]:
		result = rsvidx.inverted_get(self._index, bytes(data, "utf-8"))
		
		size = rsvidx.inverted_result_get_size(result)
		
		toReturn = [
			rsvidx.inverted_result_get_id(result, x).decode()
			for x in range(size)
		]
		
		rsvidx.inverted_result_delete(result)
		return toReturn
		
	def __del__(self):
		rsvidx.close_inverted(self._index)
		


""" Function arg/ret for datastore """
rsvidx.datastore.argtypes = [c_char_p]
rsvidx.datastore.restype = c_void_p

rsvidx.datastore_add.argtypes = [c_void_p, c_char_p, c_char_p, c_void_p, c_int]
rsvidx.datastore_add.restype = c_void_p

rsvidx.datastore_result_delete.argtypes = [c_void_p]
rsvidx.datastore_result_delete.restype = None

rsvidx.datastore_get.argtypes = [c_void_p, c_char_p]
rsvidx.datastore_get.restype = c_void_p

rsvidx.datastore_result_get_data.argtypes = [c_void_p]
rsvidx.datastore_result_get_data.restype = c_char_p
		
rsvidx.datastore_result_get_vec_size.argtypes = [c_void_p]
rsvidx.datastore_result_get_vec_size.restype = c_int

rsvidx.datastore_result_get_vec.argtypes = [c_void_p, c_int]
rsvidx.datastore_result_get_vec.restype = c_float
		
rsvidx.datastore_result_delete.argtypes = [c_void_p]
rsvidx.datastore_result_delete.restype = None
		
rsvidx.close_datastore.argtypes = [c_void_p]
rsvidx.close_datastore.restype = None


"""

Human:
Wrapper for datastore. 

GPT-3:
This is the DataStore class. It is used to store data in a file.

The class has three methods.

The first method is used to add data to the datastore.
The second method is used to get data from the datastore.
The third method is used to delete the datastore.
"""

class DataStore:

	_index = None

	def __init__(self, filename: str):
		self._index = rsvidx.datastore(bytes(filename, "utf-8"))
		
	def add(self, id: str, data: dict, vector: [float]):
		vector_p = (c_float * len(vector))(*vector)
	
		rsvidx.datastore_add(
			self._index,
			bytes(id, "utf-8"),
			bytes(json.dumps(data), "utf-8"),
			vector_p,
			len(vector)
		)
			
		
		
	def get(self, id: str) -> (dict, [float]):
		record = rsvidx.datastore_get(self._index, bytes(id, "utf-8"))
		data = json.loads(rsvidx.datastore_result_get_data(record).decode())
		vectorSize = rsvidx.datastore_result_get_vec_size(record)
		vector = [
			rsvidx.datastore_result_get_vec(record, x)
			for x in range(vectorSize)
		]
		
		rsvidx.datastore_result_delete(record)
		
		return data, vector
		
		
	def __del__(self):
		rsvidx.close_datastore(self._index)

