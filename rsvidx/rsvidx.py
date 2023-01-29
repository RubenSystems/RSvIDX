
from ctypes import CDLL, c_int, c_uint, c_float, c_void_p, c_ulong, c_char_p, c_char, create_string_buffer, Structure
import os

# libfile = glob.glob('build/*/rsvidx/rsvidxlib*.so')[0]
this_dir = os.path.abspath(os.path.dirname(__file__))
rsvidx = CDLL(os.path.join(this_dir, 'rsvidxlib.so'))

class id_record(Structure):
    _fields_=[("uid", c_char_p)]

rsvidx.init_lsh_heap.argtypes = [c_char_p, c_char_p, c_int, c_int]
rsvidx.init_lsh_heap.restype = c_void_p

rsvidx.lsh_heap_free.argtypes = [c_void_p]
rsvidx.lsh_heap_free.restype = c_void_p

rsvidx.lsh_add.argtypes = [c_void_p, c_char_p, c_void_p, c_ulong]
rsvidx.lsh_add.restype = None

rsvidx.lsh_get.argtypes = [c_void_p, c_void_p, c_ulong, c_ulong, c_void_p]
rsvidx.lsh_get.restype = c_ulong

rsvidx.lsh_delete_helper.argtypes = [c_void_p, c_char_p]
rsvidx.lsh_delete_helper.restype = None

id_size = 32

class RandomAccessIDBuffer:
	def __init__(self, buffer):
		self.buffer = buffer

	def __getitem__(self, index):
		_idx = index * id_size
		buffer_data = self.buffer.raw[_idx:_idx + id_size]
		terminate = 32
		for index, value in enumerate(buffer_data):
			if value == 0:
				terminate = index
				break
				
		return buffer_data[:terminate].decode()



class Similarity:
	def __init__(self, name: str, hash_size: int, dimensions: int):
		self._idx = rsvidx.init_lsh_heap(bytes(f"{name}.map", "utf-8"), bytes(f"{name}.store", "utf-8"), hash_size, dimensions)
		
	def add(self, vector: [float], rec_id: str):
		rsvidx.lsh_add(
			self._idx,
			bytes(rec_id, "utf-8"),
			(c_float * len(vector))(*vector),
			len(vector),
		)
	
	def get(self, vector: [float], limit: int = 100):
		buffer = create_string_buffer(id_size * limit)
		result_size = rsvidx.lsh_get(
			self._idx,
			(c_float * len(vector))(*vector),
			len(vector),
			limit,
			buffer
		)
		
		raidb = RandomAccessIDBuffer(buffer)

		return [raidb[i] for i in range(result_size)]
		
	def remove(self, id: str):
		rsvidx.lsh_delete_helper(self._idx, bytes(id, "utf-8"))
	
	def quick_remove(self, id: str, vector):
		rsvidx.lsh_delete_helper(self._idx, bytes(id, "utf-8"), (c_float * len(vector))(*vector), len(vector))
		
	def __del__(self) :
		rsvidx.lsh_heap_free(self._idx)
