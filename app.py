import csv
import functools
import multiprocessing
import timeit


f = open('result.csv', "w+")
f.close()


def filter_data(start, end):
    count = 0
    # num = 1200000/thread
    with open('rows.csv', newline='', encoding='Latin1') as csvfile, open('result.csv', 'a', encoding='Latin1') as file:
        reader = csv.reader(csvfile)
        # looping inside the whole csv file
        for row in reader:
            count += 1
            # print("count: ", count)
            # setting a range point from start till end
            if(count > start):
                # removing the null values
                if row and row[1] and row[3] and row[7] and row[8] and row[17] and row[9]:

                    data = [count, row[1], row[3],
                            row[7], row[8], row[17], row[9]]

                    # print(data)
                    writer = csv.writer(file)
                    writer.writerow(data)
            if count > end:
                break


# filter_data(0, 1000000)

def multible_functions(thread_num):
    num = 1000000//thread_num
    for i in range(0, thread_num):
        start = i*num+1
        end = (i+1)*num
        filter_data(start, end)


def multi_threading(thread_num):
    # creating threads
    threads = []
    num = 1000000//thread_num

    for i in range(0, thread_num):
        start = i*num+1
        end = (i+1)*num
        # print("start: ", start, "End: ", end)
        t = multiprocessing.Process(target=filter_data, args=(start, end,))
        threads.append(t)

    for i in range(0, thread_num):
        threads[i].start()

    for i in range(0, thread_num):
        threads[i].join()


if __name__ == "__main__":
    '''It is very important to use name == __main__ guard code with threads and multiprocessing'''
    import timeit
    # print("Time to Run 1x: ", timeit.timeit(
    #     functools.partial(filter_data, 0, 1000000), number=1))
    print("Multiple: ", timeit.timeit(
        functools.partial(multible_functions, 10), number=1))
    print("Multiprocessing:  ", timeit.timeit(
        functools.partial(multi_threading, 10), number=1))
