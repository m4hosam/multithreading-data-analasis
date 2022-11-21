import sys
# from ctypes import *
from ctypes import cdll
import ctypes.util
import time
import threading
import os
import timeit
import functools


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

similars_no = mylib.getNumberOfArraysInSimilars
similars_no.restype = ctypes.c_int

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


# startSenaryo4(int threadsNo)
start_senaryo4 = mylib.startSenaryo4
start_senaryo4.argtypes = [ctypes.c_int]
start_senaryo4.restype = None

# senaryo4(int start, int end, float orgPersentage, int threadNo)
senaryo4 = mylib.senaryo4
senaryo4.argtypes = [ctypes.c_int, ctypes.c_int,
                     ctypes.c_float, ctypes.c_int]
senaryo4.restype = None


sort_products(1000, 60)

# Save Similars to sorted.csv
save_similars()


# print(similars_no())
# start senaryo2
# start_senaryo2()


# run senaryo2
# multithreading will be here from start array to end
# arguments are (start array, end array, persentage)
# senaryo2(0, 18, 70)


# clearing the file to run senaryo 3
# start_senaryo3()

# run senaryo3
# multithreading will be here from start record to end record
# arguments are senaryo3(int start, int end, int complaintIdi, float orgPersentage, int limit)
# limit is the same value for sort_products function
# senaryo3(0, 100, 3237160, 50, 1000)


def multi_senaryo2(thread_num, persentage):
    # creating threads
    threads = []
    arrays = similars_no()
    num = arrays // thread_num
    remainder = arrays % thread_num

    for i in range(0, thread_num):
        start = i*num
        end = (i+1)*num
        # print("start: ", start, "End: ", end)
        if(i == thread_num-1 and remainder != 0):
            end = end + remainder

        # print("start: ", start, "end: ", end)
        t = threading.Thread(target=senaryo2, args=(start, end, persentage,))
        threads.append(t)

    for i in range(0, thread_num):
        threads[i].start()

    for i in range(0, thread_num):
        threads[i].join()


def multi_senaryo3(thread_num, persentage, complaintId, limit):
    # creating threads
    threads = []
    num = limit//thread_num

    for i in range(0, thread_num):
        start = i*num+1
        end = (i+1)*num
        # print("start: ", start, "End: ", end)
        t = threading.Thread(target=senaryo3, args=(
            start, end, complaintId, persentage, limit,))
        threads.append(t)

    for i in range(0, thread_num):
        threads[i].start()

    for i in range(0, thread_num):
        threads[i].join()

# senaryo4(int start, int end, float orgPersentage, int threadNo)


def multi_senaryo4(thread_num, persentage, limit):
    # creating threads
    threads = []
    num = limit//thread_num

    for i in range(0, thread_num):
        start = i*num+1
        end = (i+1)*num
        # print("start: ", start, "End: ", end)
        t = threading.Thread(target=senaryo4, args=(
            start, end, persentage, i,))
        threads.append(t)

    for i in range(0, thread_num):
        threads[i].start()

    for i in range(0, thread_num):
        threads[i].join()


if __name__ == "__main__":
    '''It is very important to use name == __main__ guard code with threads and multiprocessing'''
    #  arguments (limit,persentage)

    # start = time.time()
    # multi_senaryo2(1, 70)
    # end = time.time()

    # print("Multithreading(1):  ", end-start)
    # start = time.time()
    # multi_senaryo2(3, 70)
    # end = time.time()

    # print("Multithreading(3):  ", end-start)
    # start = time.time()
    # multi_senaryo2(5, 70)
    # end = time.time()

    # print("Multithreading(5):  ", end-start)
    # start = time.time()
    # multi_senaryo2(8, 70)
    # end = time.time()

    # print("Multithreading(8):  ", end-start)
    # print("senaryo 3 ")

    # start = time.time()
    # multi_senaryo3(1, 70, 3236983, 10000)
    # end = time.time()

    # print("Multithreading(1):  ", end-start)
    # start = time.time()
    # multi_senaryo3(3, 70, 3236983, 10000)
    # end = time.time()

    # print("Multithreading(3):  ", end-start)
    # start = time.time()
    # multi_senaryo3(5, 70, 3236983, 10000)
    # end = time.time()

    # print("Multithreading(5):  ", end-start)
    # start = time.time()
    # multi_senaryo3(8, 70, 3236983, 10000)
    # end = time.time()

    # print("Multithreading(8):  ", end-start)

    print("senaryo 4 ")
    # multi_senaryo4(thread_num, persentage, limit):
    start = time.time()
    multi_senaryo4(1, 70,  1000)
    end = time.time()

    print("Multithreading(1):  ", end-start)
    start = time.time()
    multi_senaryo4(3, 70,  1000)
    end = time.time()

    print("Multithreading(3):  ", end-start)
    start = time.time()
    multi_senaryo4(5, 70,  1000)
    end = time.time()

    print("Multithreading(5):  ", end-start)
    start = time.time()
    multi_senaryo4(8, 70,  1000)
    end = time.time()

    print("Multithreading(8):  ", end-start)

    # num = 9 % 2
    # print("num: ", num)
