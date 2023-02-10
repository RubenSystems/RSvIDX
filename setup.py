from setuptools import setup, Extension
from distutils.command.build_ext import build_ext as build_ext_orig

import glob

class CTypesExtension(Extension):
	pass

class build_ext(build_ext_orig):
	def build_extension(self, ext):
		self._ctypes = isinstance(ext, CTypesExtension)
		return super().build_extension(ext)

	def get_export_symbols(self, ext):
		if self._ctypes:
			return ext.export_symbols
		return super().get_export_symbols(ext)

	def get_ext_filename(self, ext_name):
		if self._ctypes:
			print(f"HERE {ext_name}")
			return ext_name + ".so"
		return super().get_ext_filename(ext_name)


c_module = CTypesExtension(
	'rsvidx.rsvidxlib',
	sources = [*glob.glob("src/*.c"), *glob.glob("smac-alloc/src/*.c")],
	extra_compile_args=['-O3']
)

setup(
	name='rsvidx',
	version='0.2.2',    
	description='RubenSystems Vector Indexer. Python3 edition.',
	url='https://github.com/RubenSystems/RSvIDX',
	author='RubenSystems. Ruben Ticehurst-James.',
	author_email='ruben@rubensystems.com',
	packages=['rsvidx'],
	install_requires=[],
	ext_modules = [c_module],
	cmdclass={'build_ext': build_ext}
)