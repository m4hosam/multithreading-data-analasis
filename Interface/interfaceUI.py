# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'interface.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1283, 864)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.dataset_table = QtWidgets.QTableWidget(self.centralwidget)
        self.dataset_table.setGeometry(QtCore.QRect(0, 0, 431, 811))
        self.dataset_table.setObjectName("dataset_table")
        self.dataset_table.setColumnCount(0)
        self.dataset_table.setRowCount(0)
        self.result_table = QtWidgets.QTableWidget(self.centralwidget)
        self.result_table.setGeometry(QtCore.QRect(870, 0, 411, 811))
        self.result_table.setObjectName("result_table")
        self.result_table.setColumnCount(0)
        self.result_table.setRowCount(0)
        self.filtering_group = QtWidgets.QGroupBox(self.centralwidget)
        self.filtering_group.setGeometry(QtCore.QRect(440, 50, 411, 111))
        self.filtering_group.setObjectName("filtering_group")
        self.filteringColumn_checkbox = QtWidgets.QCheckBox(self.filtering_group)
        self.filteringColumn_checkbox.setGeometry(QtCore.QRect(10, 20, 121, 20))
        self.filteringColumn_checkbox.setObjectName("filteringColumn_checkbox")
        self.filteringSame_radio = QtWidgets.QRadioButton(self.filtering_group)
        self.filteringSame_radio.setGeometry(QtCore.QRect(30, 50, 95, 20))
        self.filteringSame_radio.setObjectName("filteringSame_radio")
        self.filteringKey_radio = QtWidgets.QRadioButton(self.filtering_group)
        self.filteringKey_radio.setGeometry(QtCore.QRect(30, 80, 95, 20))
        self.filteringKey_radio.setText("")
        self.filteringKey_radio.setObjectName("filteringKey_radio")
        self.filtering_textEdit = QtWidgets.QTextEdit(self.filtering_group)
        self.filtering_textEdit.setGeometry(QtCore.QRect(50, 80, 191, 21))
        self.filtering_textEdit.setObjectName("filtering_textEdit")
        self.filtering_combo = QtWidgets.QComboBox(self.filtering_group)
        self.filtering_combo.setGeometry(QtCore.QRect(130, 20, 121, 22))
        self.filtering_combo.setObjectName("filtering_combo")
        self.filtering_combo.addItem("")
        self.filtering_combo.addItem("")
        self.filtering_combo.addItem("")
        self.filtering_combo.addItem("")
        self.filtering_combo.addItem("")
        self.filtering_combo.addItem("")
        self.similarity_label = QtWidgets.QGroupBox(self.centralwidget)
        self.similarity_label.setGeometry(QtCore.QRect(440, 170, 411, 51))
        self.similarity_label.setObjectName("similarity_label")
        self.similarity_combo = QtWidgets.QComboBox(self.similarity_label)
        self.similarity_combo.setGeometry(QtCore.QRect(10, 20, 121, 22))
        self.similarity_combo.setObjectName("similarity_combo")
        self.similarity_combo.addItem("")
        self.similarity_combo.addItem("")
        self.similarity_combo.addItem("")
        self.similarity_combo.addItem("")
        self.similarity_combo.addItem("")
        self.similarity_textEdit = QtWidgets.QTextEdit(self.similarity_label)
        self.similarity_textEdit.setGeometry(QtCore.QRect(180, 20, 101, 21))
        self.similarity_textEdit.setObjectName("similarity_textEdit")
        self.similarityPercentage_label = QtWidgets.QLabel(self.similarity_label)
        self.similarityPercentage_label.setGeometry(QtCore.QRect(160, 20, 31, 16))
        self.similarityPercentage_label.setObjectName("similarityPercentage_label")
        self.columns_group = QtWidgets.QGroupBox(self.centralwidget)
        self.columns_group.setGeometry(QtCore.QRect(439, 229, 411, 251))
        self.columns_group.setObjectName("columns_group")
        self.Product_checkbox = QtWidgets.QCheckBox(self.columns_group)
        self.Product_checkbox.setGeometry(QtCore.QRect(40, 30, 81, 20))
        self.Product_checkbox.setObjectName("Product_checkbox")
        self.Issue_checkbox = QtWidgets.QCheckBox(self.columns_group)
        self.Issue_checkbox.setGeometry(QtCore.QRect(40, 60, 81, 20))
        self.Issue_checkbox.setObjectName("Issue_checkbox")
        self.Company_checkbox = QtWidgets.QCheckBox(self.columns_group)
        self.Company_checkbox.setGeometry(QtCore.QRect(40, 90, 81, 20))
        self.Company_checkbox.setObjectName("Company_checkbox")
        self.State_checkbox = QtWidgets.QCheckBox(self.columns_group)
        self.State_checkbox.setGeometry(QtCore.QRect(40, 120, 81, 20))
        self.State_checkbox.setObjectName("State_checkbox")
        self.ID_checkbox = QtWidgets.QCheckBox(self.columns_group)
        self.ID_checkbox.setGeometry(QtCore.QRect(40, 150, 81, 20))
        self.ID_checkbox.setObjectName("ID_checkbox")
        self.ZIP_checkbox = QtWidgets.QCheckBox(self.columns_group)
        self.ZIP_checkbox.setGeometry(QtCore.QRect(40, 180, 81, 20))
        self.ZIP_checkbox.setObjectName("ZIP_checkbox")
        self.All_checkbox = QtWidgets.QCheckBox(self.columns_group)
        self.All_checkbox.setGeometry(QtCore.QRect(40, 210, 81, 20))
        self.All_checkbox.setObjectName("All_checkbox")
        self.threadSays_label = QtWidgets.QLabel(self.centralwidget)
        self.threadSays_label.setGeometry(QtCore.QRect(450, 10, 91, 31))
        self.threadSays_label.setObjectName("threadSays_label")
        self.threadNum_textEdit = QtWidgets.QTextEdit(self.centralwidget)
        self.threadNum_textEdit.setGeometry(QtCore.QRect(550, 20, 121, 21))
        self.threadNum_textEdit.setObjectName("threadNum_textEdit")
        self.ara_button = QtWidgets.QPushButton(self.centralwidget)
        self.ara_button.setGeometry(QtCore.QRect(560, 480, 151, 61))
        self.ara_button.setObjectName("ara_button")
        self.thread_table = QtWidgets.QTableWidget(self.centralwidget)
        self.thread_table.setGeometry(QtCore.QRect(440, 550, 421, 261))
        self.thread_table.setObjectName("thread_table")
        self.thread_table.setColumnCount(0)
        self.thread_table.setRowCount(0)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1283, 26))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.filtering_group.setTitle(_translate("MainWindow", "GroupBox"))
        self.filteringColumn_checkbox.setText(_translate("MainWindow", "s??tun se??iniz"))
        self.filteringSame_radio.setText(_translate("MainWindow", "ayn?? olanlar"))
        self.filtering_combo.setItemText(0, _translate("MainWindow", "Product"))
        self.filtering_combo.setItemText(1, _translate("MainWindow", "Issue"))
        self.filtering_combo.setItemText(2, _translate("MainWindow", "Company"))
        self.filtering_combo.setItemText(3, _translate("MainWindow", "State"))
        self.filtering_combo.setItemText(4, _translate("MainWindow", "ID"))
        self.filtering_combo.setItemText(5, _translate("MainWindow", "ZIP code"))
        self.similarity_label.setTitle(_translate("MainWindow", "s??tun benzerli??i"))
        self.similarity_combo.setItemText(0, _translate("MainWindow", "Product"))
        self.similarity_combo.setItemText(1, _translate("MainWindow", "Issue"))
        self.similarity_combo.setItemText(2, _translate("MainWindow", "Company"))
        self.similarity_combo.setItemText(3, _translate("MainWindow", "State"))
        self.similarity_combo.setItemText(4, _translate("MainWindow", "ZIP code"))
        self.similarityPercentage_label.setText(_translate("MainWindow", "%"))
        self.columns_group.setTitle(_translate("MainWindow", "GroupBox"))
        self.Product_checkbox.setText(_translate("MainWindow", "Product"))
        self.Issue_checkbox.setText(_translate("MainWindow", "Issue"))
        self.Company_checkbox.setText(_translate("MainWindow", "Company"))
        self.State_checkbox.setText(_translate("MainWindow", "State"))
        self.ID_checkbox.setText(_translate("MainWindow", "ID"))
        self.ZIP_checkbox.setText(_translate("MainWindow", "ZIP"))
        self.All_checkbox.setText(_translate("MainWindow", "All"))
        self.threadSays_label.setText(_translate("MainWindow", "thread say??s??"))
        self.ara_button.setText(_translate("MainWindow", "Ara"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
