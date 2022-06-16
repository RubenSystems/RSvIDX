from ctypes import *

rsvidx = CDLL('bin/rsvidx.so')


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


rsvidx.close.argtypes = [c_void_p]
rsvidx.close.restype = None


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
		rsvidx.close(self._index)



index = Similarity(10, 2, "bin/test")
# index.add("abc", [1,9])
print(index.get([-20,-49]))




















