import sys
from ctypes import *
from ctypes import cdll
import ctypes.util
import time
import threading
import os


# def find_cudart(root_path: str = os.path.abspath(os.sep),
#                 cudart_file_name: str = "functions.so") -> str:

#     for root, dirs, files in os.walk(root_path):
#         if cudart_file_name in files:
#             return os.path.join(root, cudart_file_name)


# Find the library and load it
mylib_path = ctypes.util.find_library(
    "C:\\Users\\moham\\Desktop\\Yazlab\\functions.so")
if not mylib_path:
    print("Unable to find the specified library.1")
    sys.exit()

# stdc = cdll.LoadLibrary("libc.so.6")  # or similar to load c library
# stdcpp = cdll.LoadLibrary("libstdc++.so.6")  # or similar to load c++ library
# mylib = cdll.LoadLibrary("C:\\Users\\moham\\Desktop\\Yazlab\\functions.so")
mylib = ctypes.CDLL(mylib_path)

print("Well")


# mylib.test_empty()


sort_products = mylib.NoThreadSort
sort_products.argtypes = [ctypes.c_int, ctypes.c_float]
sort_products.restype = None


save_similars = mylib.saveSimilars
save_similars.restype = None

# test = mylib.test
# test.argtypes = [ctypes.c_int, ctypes.c_int]
# test.restype = ctypes.c_int

# test_passing_array = mylib.test_passing_array
# test_passing_array.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
# test_passing_array.restype = None

# mylib.test_empty()

sort_products(100, 60)
# Save Similars to sorted.csv
save_similars()


# def threaded():
#     test(0, 1000000000)


# if __name__ == '__main__':
#     start_time = time.time()
#     t()
#     t()
#     t()
#     t()
#     t()
#     t()
#     print("Sequential run time: ", (time.time() - start_time))

#     start_time = time.time()
#     t1 = threading.Thread(target=t)
#     t2 = threading.Thread(target=t)
#     t3 = threading.Thread(target=t)
#     t4 = threading.Thread(target=t)
#     t5 = threading.Thread(target=t)
#     t6 = threading.Thread(target=t)
#     t1.start()
#     t2.start()
#     t3.start()
#     t4.start()
#     t5.start()
#     t6.start()
#     t1.join()
#     t2.join()
#     t3.join()
#     t4.join()
#     t5.join()
#     t6.join()
#     print("Parallel run time: ", (time.time() - start_time))
