import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QMainWindow
import pandas as pd
from interfaceUI import Ui_MainWindow
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QApplication, QWidget, QMessageBox

def init_data():
    data = pd.read_csv('newdata.csv')
    # data = data.drop(['Date received','Sub-product','Sub-issue','Consumer complaint narrative', 'Company public response', 'Tags', 'Consumer consent provided?', 'Submitted via','Date sent to company', 'Company response to consumer','Timely response?', 'Consumer disputed?'], axis=1)
    # data['Issue'] = data['Issue'].str.replace(r'[^\w\s]+', '')
    # data['Product'] = data['Product'].str.replace(r'[^\w\s]+', '')
    # data = data.dropna()
    return data

class MainWindow:
    def __init__(self):
        self.main_win = QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self.main_win)
        self.data = init_data()
        self.init_dataTable(self.data)
        self.ui.filtering_combo.setEnabled(False)
        self.ui.filteringSame_radio.setEnabled(False)
        self.ui.filtering_textEdit.setEnabled(False)
        self.ui.filteringKey_radio.setEnabled(False)
        self.ui.filteringColumn_checkbox.clicked.connect(self.toggleFilteringCheckbox)
        self.ui.All_checkbox.clicked.connect(self.toggleColumnCheckboxes)

    def init_dataTable(self, data):
        columnNum = len(data.axes[1])
        rowNum = len(data.axes[0])
        tableRows = []

        self.ui.dataset_table.setRowCount(21)
        self.ui.dataset_table.setColumnCount(6)
        

        self.ui.dataset_table.setItem(0, 0, QtWidgets.QTableWidgetItem('Product'))
        self.ui.dataset_table.setItem(0, 1, QtWidgets.QTableWidgetItem('Issue'))
        self.ui.dataset_table.setItem(0, 2, QtWidgets.QTableWidgetItem('Company'))
        self.ui.dataset_table.setItem(0, 3, QtWidgets.QTableWidgetItem('State'))
        self.ui.dataset_table.setItem(0, 4, QtWidgets.QTableWidgetItem('ZIP code'))
        self.ui.dataset_table.setItem(0, 5, QtWidgets.QTableWidgetItem('Complaint ID'))

        counter = 0
        for index, row in data.iterrows():
            list = [row['Product'], row['Issue'], row['Company'], row['State'], row['ZIP code'], row['Complaint ID']]
            # print(list)
            counter += 1
            tableRows.append(list)
            if counter == 20:
                break

        for row in range(1, 20):
            for column in range(0, columnNum-2):
                self.ui.dataset_table.setItem(row, column, QtWidgets.QTableWidgetItem(str(tableRows[row][column])))


    def show(self):
        self.main_win.show()
    
    def toggleFilteringCheckbox(self):
        state = self.ui.filtering_combo.isEnabled()
        if state:
            self.ui.filtering_combo.setEnabled(False)
            self.ui.filteringSame_radio.setEnabled(False)
            self.ui.filtering_textEdit.setEnabled(False)
            self.ui.filteringKey_radio.setEnabled(False)
        else: 
            self.ui.filtering_combo.setEnabled(True)
            self.ui.filteringSame_radio.setEnabled(True)
            self.ui.filtering_textEdit.setEnabled(True)
            self.ui.filteringKey_radio.setEnabled(True)
    
    def toggleColumnCheckboxes(self):
        state = self.ui.All_checkbox.isChecked()
        if state:
            self.ui.Product_checkbox.setChecked(True)
            self.ui.Issue_checkbox.setChecked(True)
            self.ui.ID_checkbox.setChecked(True)
            self.ui.ZIP_checkbox.setChecked(True)
            self.ui.Company_checkbox.setChecked(True)
            self.ui.State_checkbox.setChecked(True)
        else:
            self.ui.Product_checkbox.setChecked(False)
            self.ui.Issue_checkbox.setChecked(False)
            self.ui.ID_checkbox.setChecked(False)
            self.ui.ZIP_checkbox.setChecked(False)
            self.ui.Company_checkbox.setChecked(False)
            self.ui.State_checkbox.setChecked(False)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_win = MainWindow()
    main_win.show()
    sys.exit(app.exec_())



# data.to_csv("newdata.csv")





















# print(zips)

# for i in range(10):
#     cursor.execute(f'''
#      INSERT INTO complaints 
#      VALUES({date[i]}, {products[i]},{issues[i]},{companies[i]},{states[i]},{complaint_ids[i]},{zips[i]})   
#     ''')
# cursor.commit()

# with open('rows.csv', newline = '') as csvfile:
#     spamreader = csv.reader(csvfile, delimiter=',')
#     for row in spamreader:
#         print(','.join(row))


# start = time.perf_counter()

# def do_something(seconds):
#     print(f'sleeping {seconds} sec(s)')
#     time.sleep(seconds)
#     return f'Done sleeping...{seconds}'

# with concurrent.futures.ThreadPoolExecutor() as executor:
#     secs = [5,4,3,2,1]
#     results = executor.map(do_something, secs)

#     for result in results:
#         print(result)
    # results = [executor.submit(do_something, sec) for sec in secs]
    
    # for f in concurrent.futures.as_completed(results):
    #     print(f.result())


# threads = []

# for _ in range(10):
#     t = threading.Thread(target = do_something, args = [1.5])
#     t.start()
#     threads.append(t)

# for thread in threads:
#     thread.join()
# t1 = threading.Thread(target = do_something)
# t2 = threading.Thread(target = do_something)

# t1.start()
# t2.start()

# t1.join()
# t2.join()

# finish = time.perf_counter()

# print(f'\nfinsished in {round(finish - start, 2)}\n')
