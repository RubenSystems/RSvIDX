
from ctypes import *
import os

# libfile = glob.glob('build/*/rsvidx/rsvidxlib*.so')[0]
this_dir = os.path.abspath(os.path.dirname(__file__))


"""
	= UNCOMMENT IF LIVE =
"""
rsvidx = CDLL(os.path.join(this_dir, 'rsvidxlib.so'))


"""
	= UNCOMMENT IF TESTING =
"""
#rsvidx = CDLL("rsvidx_build.so")

class id_record(Structure):
    _fields_=[("uid", c_char_p)]

rsvidx.init_lsh_heap.argtypes = [c_char_p, c_char_p, c_int, c_int]
rsvidx.init_lsh_heap.restype = c_void_p

rsvidx.lsh_heap_free.argtypes = [c_void_p]
rsvidx.lsh_heap_free.restype = c_void_p

rsvidx.lsh_add.argtypes = [c_void_p, c_char_p, c_void_p]
rsvidx.lsh_add.restype = None

rsvidx.lsh_custom_hash_add.argtypes = [c_void_p, c_char_p, c_void_p, c_size_t]
rsvidx.lsh_custom_hash_add.restype = None

rsvidx.lsh_get.argtypes = [c_void_p, c_void_p, c_ulong, c_void_p]
rsvidx.lsh_get.restype = c_ulong

rsvidx.lsh_delete_helper.argtypes = [c_void_p, c_char_p]
rsvidx.lsh_delete_helper.restype = None


rsvidx.lsh_get_uid_from_result.argtypes = [c_void_p, c_void_p, c_ulong, c_char_p]
rsvidx.lsh_get_uid_from_result.restype = c_ulong

rsvidx.lsh_get_vector_from_result.argtypes = [c_void_p, c_void_p, c_ulong, c_void_p]
rsvidx.lsh_get_vector_from_result.restype = None

id_size = 32

class RandomAccessIDBuffer:
	def __init__(self, buffer):
		self.buffer = buffer

	def get(self, idx, index: int):
		global id_size
		id_buffer = create_string_buffer(32)
		id_size = rsvidx.lsh_get_uid_from_result(idx._idx, self.buffer, index, id_buffer)
		
		vector_buffer = (c_float * idx._dimensions)()
		rsvidx.lsh_get_vector_from_result(idx._idx, self.buffer, index, vector_buffer)
		
		return id_buffer[:id_size].decode(), [x for x in vector_buffer]



class Similarity:
	def __init__(self, name: str, hash_size: int, dimensions: int):
		self._dimensions = dimensions
		self._idx = rsvidx.init_lsh_heap(bytes(f"{name}.map", "utf-8"), bytes(f"{name}.store", "utf-8"), hash_size, dimensions)
		
	def add(self, vector: [float], rec_id: str):
		rsvidx.lsh_add(
			self._idx,
			bytes(rec_id[:31], "utf-8"),
			(c_float * len(vector))(*vector),
		)
		
	def add_custom_hash(self, vector: [float], rec_id: str, hash: int):
		rsvidx.lsh_custom_hash_add(
			self._idx,
			bytes(rec_id[:31], "utf-8"),
			(c_float * len(vector))(*vector),
			hash
		)
	
	def get(self, vector: [float], limit: int = 100):
		buffer_size = (id_size + (sizeof(c_float) * self._dimensions)) * limit
		buffer = create_string_buffer(buffer_size)
		result_size = rsvidx.lsh_get(
			self._idx,
			(c_float * len(vector))(*vector),
			limit,
			buffer
		)
		
		raidb = RandomAccessIDBuffer(buffer)

		return [raidb.get(self, i)  for i in range(result_size)]
		
	def remove(self, id: str):
		rsvidx.lsh_delete_helper(self._idx, bytes(id, "utf-8"))
		
	def __del__(self) :
		rsvidx.lsh_heap_free(self._idx)
