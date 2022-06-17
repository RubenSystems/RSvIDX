from ctypes import *

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


""" Wrapper for lsh index """
class Similarity:

	_index = None

	def __init__(self, tables: int, dimensions: int, filename: str):
		self._index = rsvidx.lsh(tables, dimensions, bytes(filename, "utf-8"))

	def get(self, array: [float]) -> [str]:
		array_pointer = (c_float*len(array))(*array)

		result = rsvidx.lsh_get(self._index, len(array), array_pointer )
		toReturn = [rsvidx.lsh_result_get_id(result, x).decode() for x in range(rsvidx.lsh_result_get_size(result))]
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
rsvidx.ordered.argtypes = None
rsvidx.ordered.restype = c_void_p

rsvidx.ordered_insert.argtypes = [c_void_p, c_char_p, c_float]
rsvidx.ordered_insert.restype = None

rsvidx.ordered_get_greater.argtypes = [c_void_p, c_float]
rsvidx.ordered_get_greater.restype = c_void_p

rsvidx.ordered_get_less.argtypes = [c_void_p, c_float]
rsvidx.ordered_get_less.restype = c_void_p

rsvidx.ordered_result_get_size.argtypes = [c_void_p]
rsvidx.ordered_result_get_size.restype = c_int

rsvidx.close_ordered.argtypes = [c_void_p]
rsvidx.close_ordered.restype = None

""" Wrapper for ordered index """
class Ordered:
	_index = None
	
	def __init__(self):
		self._index = rsvidx.ordered()
		
	def insert(self, id: str, value: float):
			array_pointer = (c_float*len(data))(*data)
			rsvidx.insert(self._index, bytes(id, "utf-8"), value)
			
	def getGreater(self, value: float) -> str:
		result = rsvidx.ordered_get_greater(self._index, value)
		size = rsvidx.ordered_result_get_size(result)
		return [
			rsvidx.ordered_node_get_id(rsvidx.ordered_result_get_node(result, x)).decode()
			for x in range(size)
		]
		
	def getLess(self, value: float) -> str:
		result = rsvidx.ordered_get_less(self._index, value)
		size = rsvidx.ordered_result_get_size(result)
		return [
			rsvidx.ordered_node_get_id(rsvidx.ordered_result_get_node(result, x)).decode()
			for x in range(size)
		]
		
		
		
		
		
		
		
	def __del__(self):
		rsvidx.close_ordered(self._index)
	


















