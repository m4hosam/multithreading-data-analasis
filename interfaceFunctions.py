import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QMainWindow
import pandas as pd
from interfaceUI import Ui_MainWindow
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QApplication, QWidget, QMessageBox
import app
import time


def init_data():
    data = pd.read_csv("out.csv", encoding="ISO-8859-1")
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

        self.filteringRadioVal = 0
        self.filterBy = 0
        self.threadNum = 0
        self.similarityColumn = 0
        self.similarityPercentage = 0
        self.checkedColumns = []

        self.init_dataTable(self.data)
        self.ui.filtering_combo.setEnabled(False)
        self.ui.filteringSame_radio.setEnabled(False)
        self.ui.filtering_textEdit.setEnabled(False)
        self.ui.filteringKey_radio.setEnabled(False)
        self.ui.filteringColumn_checkbox.clicked.connect(
            self.toggleFilteringCheckbox)
        self.ui.ara_button.clicked.connect(self.getInput)
        self.ui.All_checkbox.clicked.connect(self.toggleColumnCheckboxes)

        self.ui.Product_checkbox.clicked.connect(self.toggleAll)
        self.ui.Issue_checkbox.clicked.connect(self.toggleAll)
        self.ui.ID_checkbox.clicked.connect(self.toggleAll)
        self.ui.ZIP_checkbox.clicked.connect(self.toggleAll)
        self.ui.Company_checkbox.clicked.connect(self.toggleAll)
        self.ui.State_checkbox.clicked.connect(self.toggleAll)

    def init_dataTable(self, data):
        columnNum = len(data.axes[1])
        rowNum = len(data.axes[0])
        tableRows = []

        self.ui.dataset_table.setRowCount(100)
        self.ui.dataset_table.setColumnCount(6)

        self.ui.dataset_table.setItem(
            0, 0, QtWidgets.QTableWidgetItem('Product'))
        self.ui.dataset_table.setItem(
            0, 1, QtWidgets.QTableWidgetItem('Issue'))
        self.ui.dataset_table.setItem(
            0, 2, QtWidgets.QTableWidgetItem('Company'))
        self.ui.dataset_table.setItem(
            0, 3, QtWidgets.QTableWidgetItem('State'))
        self.ui.dataset_table.setItem(
            0, 4, QtWidgets.QTableWidgetItem('ZIP code'))
        self.ui.dataset_table.setItem(
            0, 5, QtWidgets.QTableWidgetItem('Complaint ID'))

        counter = 0
        for index, row in data.iterrows():
            list = [row['Product'], row['Issue'], row['Company'],
                    row['State'], row['ZIP code'], row['Complaint ID']]
            # print(list)
            counter += 1
            tableRows.append(list)
            if counter == 100:
                break

        for row in range(1, 100):
            for column in range(0, columnNum-1):
                self.ui.dataset_table.setItem(
                    row, column, QtWidgets.QTableWidgetItem(str(tableRows[row][column])))

    def init_resultsTable(self, data):
        columnNum = len(data.axes[1])
        rowNum = len(data.axes[0])
        tableRows = []

        self.ui.result_table.setRowCount(100)
        self.ui.result_table.setColumnCount(6)

        self.ui.result_table.setItem(
            0, 0, QtWidgets.QTableWidgetItem('Product'))
        self.ui.result_table.setItem(0, 1, QtWidgets.QTableWidgetItem('Issue'))
        self.ui.result_table.setItem(
            0, 2, QtWidgets.QTableWidgetItem('Company'))
        self.ui.result_table.setItem(0, 3, QtWidgets.QTableWidgetItem('State'))
        self.ui.result_table.setItem(
            0, 4, QtWidgets.QTableWidgetItem('ZIP code'))
        self.ui.result_table.setItem(
            0, 5, QtWidgets.QTableWidgetItem('Complaint ID'))

        counter = 0
        for index, row in data.iterrows():
            list = [row['Product'], row['Issue'], row['Company'],
                    row['State'], row['ZIP code'], row['Complaint ID']]
            # print(list)
            counter += 1
            tableRows.append(list)
            if counter == 100:
                break

        for row in range(0, 100):
            for column in range(0, columnNum-1):
                self.ui.result_table.setItem(
                    row, column, QtWidgets.QTableWidgetItem(str(tableRows[row][column])))

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

    def toggleAll(self):
        if not self.ui.ID_checkbox.isChecked():
            self.ui.All_checkbox.setChecked(False)
        if not self.ui.Company_checkbox.isChecked():
            self.ui.All_checkbox.setChecked(False)
        if not self.ui.State_checkbox.isChecked():
            self.ui.All_checkbox.setChecked(False)
        if not self.ui.ZIP_checkbox.isChecked():
            self.ui.All_checkbox.setChecked(False)
        if not self.ui.Issue_checkbox.isChecked():
            self.ui.All_checkbox.setChecked(False)

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

    def getInput(self):
        threadNum = self.ui.threadNum_textEdit.toPlainText()
        similarityColumn = self.ui.similarity_combo.currentText()
        similarityPercentage = self.ui.similarity_textEdit.toPlainText()
        if threadNum.isnumeric() == False:
            return
        elif similarityPercentage.isnumeric() == False:
            return

        threadNum = int(threadNum)
        filteringRadioVal = 0
        filterBy = 0

        if self.ui.filteringColumn_checkbox.isChecked():
            filterBy = self.ui.filtering_combo.currentText()
            if self.ui.filteringSame_radio.isChecked():
                filteringRadioVal = "same"
            else:
                filteringRadioVal = self.ui.filtering_textEdit.toPlainText()
        else:
            filteringRadioVal = 0
            filterBy = 0

        checkedColumns = ['Product', 'Issue', 'Company',
                          'State', 'ZIP code', 'Complaint ID']
        if not self.ui.All_checkbox.isChecked():
            if not self.ui.Product_checkbox.isChecked():
                checkedColumns.remove('Product')
            if not self.ui.Issue_checkbox.isChecked():
                checkedColumns.remove('Issue')
            if not self.ui.Company_checkbox.isChecked():
                checkedColumns.remove('Company')
            if not self.ui.State_checkbox.isChecked():
                checkedColumns.remove('State')
            if not self.ui.ZIP_checkbox.isChecked():
                checkedColumns.remove('ZIP code')
            if not self.ui.ID_checkbox.isChecked():
                checkedColumns.remove('Complaint ID')

        self.filteringRadioVal = filteringRadioVal
        self.filterBy = filterBy
        self.threadNum = threadNum
        self.similarityColumn = similarityColumn
        self.similarityPercentage = similarityPercentage
        self.checkedColumns = checkedColumns

        print("filtering radio val: " + str(self.filteringRadioVal))
        print("filterBy : " + str(self.filterBy))
        print("thread Num: " + str(self.threadNum))
        print("similarity column:" + str(self.similarityColumn))
        print("similarity Percentage: " + str(self.similarityPercentage))
        print("checked Columns: " + str(self.checkedColumns))

        self.runCfunctions()

    def init_threadTable(self, time):

        self.ui.thread_table.setRowCount(1)
        self.ui.thread_table.setColumnCount(2)

        self.ui.thread_table.setItem(
            0, 0, QtWidgets.QTableWidgetItem('total run time'))
        self.ui.thread_table.setItem(
            0, 1, QtWidgets.QTableWidgetItem(str(time)))

    def runCfunctions(self):

        if self.filteringRadioVal == 0:
            print("111")
            start = time.time()
            self.results = pd.read_csv("sorted.csv", encoding="ISO-8859-1")
            self.init_resultsTable(self.results)
            end = time.time()
            self.init_threadTable(end-start)
            # run function

        elif self.filteringRadioVal == "same":
            app.multi_senaryo2(self.threadNum, self.similarityPercentage)

            results = pd.read_csv("result.csv", encoding="ISO-8859-1")
            # run senaryo 2

        else:
            app.multi_senaryo3(
                self.threadNum, self.filteringRadioVal, self.similarityPercentage)
            results = pd.read_csv("result.csv", encoding="ISO-8859-1")

        # run senaryo 3 with self.filterBy self.filteringRadioVal self.filterby


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
