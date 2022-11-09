import csv

import multiprocessing


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

# filter_data(0, 100000)
# filter_data(0, 100000)
# filter_data(0, 100000)
# filter_data(0, 100000)
# filter_data(0, 100000)


# num = 1000000//40


# for i in range(0, 40):
#     start = i*num+1
#     end = (i+1)*num
#     filter_data(start, end)

# filter_data(0, 33000)
# filter_data(33001, 60000)
# filter_data(60001, 100000)


# creating threads
threads = []
num = 1000000//5


for i in range(0, 5):
    start = i*num+1
    end = (i+1)*num
    print("start: ", start, "End: ", end)
    t = multiprocessing.Process(target=filter_data, args=(start, end))
    threads.append(t)


for i in range(0, 5):
    threads[i].start()

for i in range(0, 5):
    threads[i].join()


print("Done!")
