from ctypes import CDLL, c_int, c_uint, c_float, c_void_p, c_ulong, c_char_p

rsvidx = CDLL('bin/rsvidx_build.so')
		
		
		

""" Function arg/ret for ordered index """
rsvidx.init_similarity.argtypes = [c_char_p, c_int, c_int]
rsvidx.init_similarity.restype = c_void_p

rsvidx.generate_similarity.argtypes = [c_void_p]
rsvidx.generate_similarity.restype = None

rsvidx.add_similarity.argtypes = [c_void_p, c_void_p, c_uint, c_char_p]
rsvidx.add_similarity.restype = None

rsvidx.get_similarity.argtypes = [c_void_p, c_void_p, c_uint]
rsvidx.get_similarity.restype = c_void_p

rsvidx.id_at_index.argtypes = [c_void_p, c_ulong]
rsvidx.id_at_index.restype = c_char_p

rsvidx.array_size.argtypes = [c_void_p]
rsvidx.array_size.restype = c_ulong

rsvidx.free_array.argtypes = [c_void_p]
rsvidx.free_array.restype = None

rsvidx.free_index.argtypes = [c_void_p]
rsvidx.free_index.restype = None

class Similarity:
	
	def __init__(self, path: str, dimensions: int, number_of_tables: int):
		self._idx = rsvidx.init_similarity(bytes(path, "utf-8"), dimensions, number_of_tables)
	
	def generate(self):
		rsvidx.generate_similarity(self._idx)
		
	def add(self, vector: [float], rec_id: str):
		rsvidx.add_similarity(
			self._idx,
			(c_float * len(vector))(*vector),
			len(vector),
			bytes(rec_id, "utf-8")
		)
	
	def get(self, vector: [float]):
		result_array = rsvidx.get_similarity(
			self._idx,
			(c_float * len(vector))(*vector),
			len(vector)
		)
		
		
		ret_data = [
			rsvidx.id_at_index(result_array, i).decode()
			for i in range(rsvidx.array_size(result_array))
		]
		
		rsvidx.free_array(result_array)
		return ret_data
		
	def remove(self, id: str):
		rsvidx.remove_similarity(self._idx, bytes(id, "utf-8")) 
		
	def __del__(self) :
		rsvidx.free_index(self._idx)
		
