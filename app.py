import csv


count =0
# 

with open('rows.csv', newline='') as csvfile , open('result.csv', 'w') as file:
    reader = csv.reader(csvfile)


    
    for row in reader:
        # print(row['first_name'], row['last_name'])
        data = [row[1], row[3], row[7], row[8], row[17], row[9]]
        print(data)
        writer = csv.writer(file)
        writer.writerow(data)
        count+=1
        if count >2000:
            break