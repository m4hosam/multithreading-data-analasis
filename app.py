import sys
# from ctypes import *
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


mylib = ctypes.CDLL(mylib_path)

print("Well")


sort_products = mylib.NoThreadSort
sort_products.argtypes = [ctypes.c_int, ctypes.c_float]
sort_products.restype = None


save_similars = mylib.saveSimilars
save_similars.restype = None

start_senaryo2 = mylib.startSenaryo2
start_senaryo2.restype = None


# senaryo2(int start, int end, float orgPersentage)
senaryo2 = mylib.senaryo2
senaryo2.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_float]
senaryo2.restype = None

start_senaryo3 = mylib.startSenaryo3
start_senaryo3.restype = None

# senaryo3(int start, int end, int complaintIdi, float orgPersentage, int limit)
senaryo3 = mylib.senaryo3
senaryo3.argtypes = [ctypes.c_int, ctypes.c_int,
                     ctypes.c_int, ctypes.c_float, ctypes.c_int]
senaryo3.restype = None


#  arguments (limit,persentage)
sort_products(1000, 60)

# Save Similars to sorted.csv
save_similars()

# start senaryo2
start_senaryo2()

# run senaryo2
# multithreading will be here from start array to end
# arguments are (start array, end array, persentage)
senaryo2(0, 18, 70)


# clearing the file to run senaryo 3
start_senaryo3()

# run senaryo3
# multithreading will be here from start record to end record
# arguments are senaryo3(int start, int end, int complaintIdi, float orgPersentage, int limit)
# limit is the same value for sort_products function
senaryo3(0, 100, 3237160, 50, 1000)


# stdc = cdll.LoadLibrary("libc.so.6")  # or similar to load c library
# stdcpp = cdll.LoadLibrary("libstdc++.so.6")  # or similar to load c++ library
# mylib = cdll.LoadLibrary("C:\\Users\\moham\\Desktop\\Yazlab\\functions.so")

# test = mylib.test
# test.argtypes = [ctypes.c_int, ctypes.c_int]
# test.restype = ctypes.c_int

# test_passing_array = mylib.test_passing_array
# test_passing_array.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
# test_passing_array.restype = None

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
