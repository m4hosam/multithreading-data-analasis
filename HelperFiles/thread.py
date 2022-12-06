import time
import threading
import multiprocessing


def fn():
    '''since all 3 functions were identical you can just use one ...'''
    x = 0
    while x < 6000000:
        x += 1


def TEST_THREADS():
    new_thread1 = threading.Thread(target=fn, args=())
    new_thread2 = threading.Thread(target=fn, args=())
    new_thread3 = threading.Thread(target=fn, args=())
    new_thread4 = threading.Thread(target=fn, args=())
    new_thread5 = threading.Thread(target=fn, args=())
    new_thread6 = threading.Thread(target=fn, args=())
    new_thread7 = threading.Thread(target=fn, args=())
    new_thread8 = threading.Thread(target=fn, args=())
    new_thread9 = threading.Thread(target=fn, args=())
    new_thread1.start()
    new_thread2.start()
    new_thread3.start()
    new_thread4.start()
    new_thread5.start()
    new_thread6.start()
    new_thread7.start()
    new_thread8.start()
    new_thread9.start()
    new_thread1.join()
    new_thread2.join()
    new_thread3.join()
    new_thread4.join()
    new_thread5.join()
    new_thread6.join()
    new_thread7.join()
    new_thread8.join()
    new_thread9.join()


def TEST_NORMAL():
    fn()
    fn()
    fn()
    fn()
    fn()
    fn()
    fn()
    fn()
    fn()


def TEST_MULTIPROCESSING():
    new_thread1 = multiprocessing.Process(target=fn, args=())
    new_thread2 = multiprocessing.Process(target=fn, args=())
    new_thread3 = multiprocessing.Process(target=fn, args=())
    new_thread4 = multiprocessing.Process(target=fn, args=())
    new_thread5 = multiprocessing.Process(target=fn, args=())
    new_thread6 = multiprocessing.Process(target=fn, args=())
    new_thread7 = multiprocessing.Process(target=fn, args=())
    new_thread8 = multiprocessing.Process(target=fn, args=())
    new_thread9 = multiprocessing.Process(target=fn, args=())
    new_thread1.start()
    new_thread2.start()
    new_thread3.start()
    new_thread4.start()
    new_thread5.start()
    new_thread6.start()
    new_thread7.start()
    new_thread8.start()
    new_thread9.start()
    new_thread1.join()
    new_thread2.join()
    new_thread3.join()
    new_thread4.join()
    new_thread5.join()
    new_thread6.join()
    new_thread7.join()
    new_thread8.join()
    new_thread9.join()


if __name__ == "__main__":
    '''It is very important to use name == __main__ guard code with threads and multiprocessing'''
    import timeit
    print("Time to Run 1x: ", timeit.timeit(fn, number=1))
    print("NORMAL: ", timeit.timeit(TEST_NORMAL, number=1))
    print("Threaded:  ", timeit.timeit(TEST_THREADS, number=1))
    print("Multiprocessing:  ", timeit.timeit(TEST_MULTIPROCESSING, number=1))
