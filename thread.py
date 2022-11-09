import time
import threading
import multiprocessing


def fn():
    '''since all 3 functions were identical you can just use one ...'''
    x = 0
    while x < 100000000:
        x += 1


def TEST_THREADS():
    new_thread1 = threading.Thread(target=fn, args=())
    new_thread2 = threading.Thread(target=fn, args=())
    new_thread3 = threading.Thread(target=fn, args=())
    new_thread1.start()
    new_thread2.start()
    new_thread3.start()
    new_thread1.join()
    new_thread2.join()
    new_thread3.join()


def TEST_NORMAL():
    fn()
    fn()
    fn()


def TEST_MULTIPROCESSING():
    new_thread1 = multiprocessing.Process(target=fn, args=())
    new_thread2 = multiprocessing.Process(target=fn, args=())
    new_thread3 = multiprocessing.Process(target=fn, args=())
    new_thread1.start()
    new_thread2.start()
    new_thread3.start()
    new_thread1.join()
    new_thread2.join()
    new_thread3.join()


if __name__ == "__main__":
    '''It is very important to use name == __main__ guard code with threads and multiprocessing'''
    import timeit
    print("Time to Run 1x: ", timeit.timeit(fn, number=1))
    print("NORMAL: ", timeit.timeit(TEST_NORMAL, number=1))
    print("Threaded:  ", timeit.timeit(TEST_THREADS, number=1))
    print("Multiprocessing:  ", timeit.timeit(TEST_MULTIPROCESSING, number=1))
