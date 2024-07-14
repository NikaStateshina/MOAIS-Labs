from tkinter import *
from math import *
import time

import matplotlib, numpy, sys
import matplotlib.pyplot as plt
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from tkinter import filedialog
from PyQt5 import QtCore, QtGui, QtWidgets


#считать время


#возвращать первое встреченное
#параметр для эксперимента - размер хэша и слова на вход

#генератор получает на вход количество символов и опционально алфавит из которого создавать
#генератор должен заполнять строку словами хэш которого совпадает с хэшем запроса


#оптимизировать для миллиарда слов     

#   PyPy - не ставятся библиотеки    
# taichi - со строками не работает 
# numba - та реализация которая заработала выигрыша в скорости не дала, ещё и повисает при первом вызове функции


#генерировать текст в файл +

#добавить перебор хэша +

#на графике Время, количество найденных слов +

#пофиксить создание графиков+

#добавить сохранение и загрузку тестов +

#добавлять пробел в начало собственного алфавита



#comp = 0

class TextGen:
    A_CODE = ord("a")
    #L_GROUPS = 13
    CYRILLIC =" абвгдежзийклмнопрстуфхцчшщъыьэюя"#стратегически важный пробел в начале

    def randomword(self,alph,alen,wlen):
        ind = numpy.random.randint(0,alen, wlen)
        return ''.join(alph[ind].tolist())
    
    def generate(self,se,alph,len1,len2):
        if alph:
            letters_np=numpy.array(list(" "+alph))
            alen=len(alph)
        else:
            letters_np =numpy.array(list(self.CYRILLIC))
            alen=33
            wlen=numpy.random.randint(len1,len2)
        if wlen !=0:
            return ' '.join([self.randomword(letters_np,alen,wlen),se])

    def generate_text(self,alph,len1,len2,tlen):
        space_pos=[0]*tlen
        pos=0
        if alph:
            letters_np=numpy.array(list(" "+alph))
            alen=len(alph)
        else:
            letters_np =numpy.array(list(self.CYRILLIC))
            alen=33
        wlens = numpy.random.randint(len1,len2+2, tlen)
        for i in range(tlen):
            pos+=wlens[i]
            space_pos[i]=pos
        text=numpy.random.randint(1,alen, pos+1)
        for i in space_pos:
            text[i]=0
        return ''.join(letters_np[text].tolist())

#//////////////////////////////////////////////////////////////////////
class SignHashSearch:
    A_CODE = ord("a")
    def build_dictionary(self,num_l_groups):
        dictionary = [0] * (2<<num_l_groups-1)
        for i in range(2<<num_l_groups-1):
            dictionary[i] = set()
        return dictionary


    def hash_func(self,w,L_GROUPS):
        hsha=0
        for j in w:
            hsha = hsha|(1<<(ord(j)-self.A_CODE)%L_GROUPS)
        return hsha


    def fill_dict(self,dictionary,word_list,L_GROUPS):
        for i in word_list:
            hsh=self.hash_func(i,L_GROUPS)
            dictionary[hsh].add(i)


    def iter(self,req,st):
        for i in st:
            return req == i


    def find(self,dictionary,k,req,L_GROUPS):
        res=[]
        ohsh=self.hash_func(req,L_GROUPS)
        hsh=ohsh
        bhsh=ohsh
        res.extend(dictionary[ohsh])
        self.iter(req,dictionary[ohsh])
        if k == 1:
            for i in range(0,L_GROUPS):
                hsh= ohsh ^ (1 << i)
                res.extend(dictionary[hsh])
                self.iter(req,dictionary[ohsh])
        if k == 2:
            for i in range(0,L_GROUPS):
                hsh= ohsh ^ (1 << i)
                bhsh=hsh
                res.extend(dictionary[hsh])
                self.iter(req,dictionary[ohsh])
                for j in range(0,i):
                    hsh= bhsh ^ (1 << j)
                    res.extend(dictionary[hsh])
                    self.iter(req,dictionary[ohsh])
                for j in range(i+1,L_GROUPS):
                    hsh= bhsh ^ (1 << j)
                    res.extend(dictionary[hsh])
                    self.iter(req,dictionary[ohsh])
        return list(set(res))



#//////////////////////////////////////////////////////////////////////



class Experiment:

    SHS=SignHashSearch()

    def experiment(self,se,req,k):
        rl1=[]
        rl2=[]
        rl3=[]
        w_list = se.split()
        for i in range(1,17):

            startd = time.time()
            dic=self.SHS.build_dictionary(16)
            self.SHS.fill_dict(dic,w_list,i)
            endd = time.time()
            starts = time.time()
            result=self.SHS.find(dic,k,req,i)
            ends = time.time()
            rl1.append((endd-startd)*1000)
            rl2.append(len(result))
            rl3.append((ends-starts)*1000)
        self.build_graph(rl1,rl2,rl3)


    def build_graph(self,ds1,ds2,ds3):
        x = list(range(1,17))
        x_axis = numpy.arange(len(x))
        fig = plt.figure()
        plt.subplot(311)
        t_plot = plt.bar(x_axis,ds1,0.8,color='b')
        plt.xticks(x_axis, x) 
        plt.xlabel('Размер хеша')
        plt.ylabel('Время построения словаря')
        plt.bar_label(t_plot, label_type='edge',fontsize=8)

        plt.subplot(312)
        t_plot2 = plt.bar(x_axis,ds3,0.8,color='g')
        plt.xticks(x_axis, x) 
        plt.xlabel('Размер хеша')
        plt.ylabel('Время поиска')
        plt.bar_label(t_plot2, label_type='edge',fontsize=8)

        plt.subplot(313)
        w_plot = plt.bar(x_axis,ds2,0.8,color='r')   
        plt.xticks(x_axis, x) 
        plt.xlabel('Размер хеша')
        plt.ylabel('Количество слов')
        plt.bar_label(w_plot, label_type='edge',fontsize=8)

        plt.show()
#//////////////////////////////////////////////////////////////////////



#//////////////////////////////////////////////////////////////////////
class Ui_MainWindow(object):

    str_experiment=""

    def load_experiment(self):
        filepath = QtWidgets.QFileDialog.getOpenFileName(MainWindow,"Open file","","Text files (*.txt)")
        if filepath[0]!='':
             with open(filepath[0], "r") as file:
                self.str_experiment = file.readline()
            
    def save_experiment(self):
        filepath = QtWidgets.QFileDialog.getOpenFileName(MainWindow,"Open file","","Text files (*.txt)")
        if filepath[0]!='':
            with open(filepath[0], "w") as file:
                file.write(self.str_experiment)

    def word_gen_action(self):           
        Tg=TextGen()
        self.str_experiment = Tg.generate(self.str_experiment,self.lineEdit.text(),self.symc1.value(),self.symc2.value())
    def text_gen_action(self):           
        Tg=TextGen()
        self.str_experiment = Tg.generate_text(self.req_line.text(),self.symc1.value(),self.symc2.value(),self.worc.value())

    def experiment_action(self):  
        Ex=Experiment()
        Ex.experiment(self.str_experiment,self.req_line.text(),self.dif_slider.value())

    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(794, 542)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.centralwidget)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.gen_box = QtWidgets.QGroupBox(self.centralwidget)
        self.gen_box.setAlignment(QtCore.Qt.AlignCenter)
        self.gen_box.setObjectName("gen_box")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(self.gen_box)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.symc_frame = QtWidgets.QFrame(self.gen_box)
        self.symc_frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.symc_frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.symc_frame.setLineWidth(5)
        self.symc_frame.setObjectName("symc_frame")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.symc_frame)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.symc_lbl = QtWidgets.QLabel(self.symc_frame)
        self.symc_lbl.setObjectName("symc_lbl")
        self.verticalLayout_2.addWidget(self.symc_lbl)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.symc_lbl_1 = QtWidgets.QLabel(self.symc_frame)
        self.symc_lbl_1.setObjectName("symc_lbl_1")
        self.horizontalLayout.addWidget(self.symc_lbl_1)
        self.symc1 = QtWidgets.QSpinBox(self.symc_frame)
        self.symc1.setMinimum(1)
        self.symc1.setMaximum(32)
        self.symc1.setObjectName("symc1")
        self.horizontalLayout.addWidget(self.symc1)
        self.symc_lbl_2 = QtWidgets.QLabel(self.symc_frame)
        self.symc_lbl_2.setObjectName("symc_lbl_2")
        self.horizontalLayout.addWidget(self.symc_lbl_2)
        self.symc2 = QtWidgets.QSpinBox(self.symc_frame)
        self.symc2.setMinimum(1)
        self.symc2.setMaximum(32)
        self.symc2.setObjectName("symc2")
        self.horizontalLayout.addWidget(self.symc2)
        self.verticalLayout_2.addLayout(self.horizontalLayout)
        self.verticalLayout_5.addWidget(self.symc_frame)
        self.alph_frame = QtWidgets.QFrame(self.gen_box)
        self.alph_frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.alph_frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.alph_frame.setObjectName("alph_frame")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.alph_frame)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_3.addItem(spacerItem)
        self.splitter_3 = QtWidgets.QSplitter(self.alph_frame)
        self.splitter_3.setOrientation(QtCore.Qt.Vertical)
        self.splitter_3.setObjectName("splitter_3")
        self.label = QtWidgets.QLabel(self.splitter_3)
        self.label.setObjectName("label")
        self.lineEdit = QtWidgets.QLineEdit(self.splitter_3)
        self.lineEdit.setObjectName("lineEdit")
        self.verticalLayout_3.addWidget(self.splitter_3)
        self.verticalLayout_5.addWidget(self.alph_frame)
        spacerItem1 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_5.addItem(spacerItem1)
        self.frame = QtWidgets.QFrame(self.gen_box)
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setLineWidth(5)
        self.frame.setObjectName("frame")
        self.verticalLayout_6 = QtWidgets.QVBoxLayout(self.frame)
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        self.worc_lbl = QtWidgets.QLabel(self.frame)
        self.worc_lbl.setObjectName("worc_lbl")
        self.verticalLayout_6.addWidget(self.worc_lbl)
        self.worc = QtWidgets.QSpinBox(self.frame)
        self.worc.setMinimum(1)
        self.worc.setMaximum(1000000000)
        self.worc.setObjectName("worc")
        self.verticalLayout_6.addWidget(self.worc)
        self.verticalLayout_5.addWidget(self.frame)
        self.gen_btn_frame = QtWidgets.QFrame(self.gen_box)
        self.gen_btn_frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.gen_btn_frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.gen_btn_frame.setLineWidth(5)
        self.gen_btn_frame.setObjectName("gen_btn_frame")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.gen_btn_frame)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.gen_w_btn = QtWidgets.QPushButton(self.gen_btn_frame)
        self.gen_w_btn.setObjectName("gen_w_btn")
        self.verticalLayout_4.addWidget(self.gen_w_btn)
        self.gen_t_btn = QtWidgets.QPushButton(self.gen_btn_frame)
        self.gen_t_btn.setObjectName("gen_t_btn")
        self.verticalLayout_4.addWidget(self.gen_t_btn)
        self.gen_s_btn = QtWidgets.QPushButton(self.gen_btn_frame)
        self.gen_s_btn.setObjectName("gen_s_btn")
        self.verticalLayout_4.addWidget(self.gen_s_btn)
        self.gen_l_btn = QtWidgets.QPushButton(self.gen_btn_frame)
        self.gen_l_btn.setObjectName("gen_l_btn")
        self.verticalLayout_4.addWidget(self.gen_l_btn)
        self.verticalLayout_5.addWidget(self.gen_btn_frame)
        self.horizontalLayout_3.addWidget(self.gen_box)
        self.search_box = QtWidgets.QGroupBox(self.centralwidget)
        self.search_box.setAlignment(QtCore.Qt.AlignCenter)
        self.search_box.setObjectName("search_box")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.search_box)
        self.verticalLayout.setObjectName("verticalLayout")
        self.dif_frame = QtWidgets.QFrame(self.search_box)
        self.dif_frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.dif_frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.dif_frame.setLineWidth(5)
        self.dif_frame.setObjectName("dif_frame")
        self.verticalLayout_7 = QtWidgets.QVBoxLayout(self.dif_frame)
        self.verticalLayout_7.setObjectName("verticalLayout_7")
        self.splitter = QtWidgets.QSplitter(self.dif_frame)
        self.splitter.setOrientation(QtCore.Qt.Vertical)
        self.splitter.setObjectName("splitter")
        self.dif_lbl = QtWidgets.QLabel(self.splitter)
        self.dif_lbl.setObjectName("dif_lbl")
        self.dif_slider = QtWidgets.QSlider(self.splitter)
        self.dif_slider.setMaximum(2)
        self.dif_slider.setOrientation(QtCore.Qt.Horizontal)
        self.dif_slider.setTickPosition(QtWidgets.QSlider.TicksBelow)
        self.dif_slider.setTickInterval(1)
        self.dif_slider.setObjectName("dif_slider")
        self.verticalLayout_7.addWidget(self.splitter)
        self.verticalLayout.addWidget(self.dif_frame)
        spacerItem2 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem2)
        self.req_frame = QtWidgets.QFrame(self.search_box)
        self.req_frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.req_frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.req_frame.setLineWidth(5)
        self.req_frame.setObjectName("req_frame")
        self.verticalLayout_8 = QtWidgets.QVBoxLayout(self.req_frame)
        self.verticalLayout_8.setObjectName("verticalLayout_8")
        self.splitter_2 = QtWidgets.QSplitter(self.req_frame)
        self.splitter_2.setOrientation(QtCore.Qt.Vertical)
        self.splitter_2.setObjectName("splitter_2")
        self.req_lbl = QtWidgets.QLabel(self.splitter_2)
        self.req_lbl.setObjectName("req_lbl")
        self.req_line = QtWidgets.QLineEdit(self.splitter_2)
        self.req_line.setText("")
        self.req_line.setObjectName("req_line")
        self.verticalLayout_8.addWidget(self.splitter_2)
        self.verticalLayout.addWidget(self.req_frame)
        spacerItem3 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem3)
        self.search_btn = QtWidgets.QPushButton(self.search_box)
        self.search_btn.setObjectName("search_btn")
        self.verticalLayout.addWidget(self.search_btn)
        self.horizontalLayout_3.addWidget(self.search_box)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        
        self.gen_w_btn.clicked.connect(self.word_gen_action)
        self.gen_t_btn.clicked.connect(self.text_gen_action)
        self.gen_s_btn.clicked.connect(self.save_experiment)
        self.gen_l_btn.clicked.connect(self.load_experiment)
        self.search_btn.clicked.connect(self.experiment_action)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "SignHashExperiment"))
        self.gen_box.setTitle(_translate("MainWindow", "Параметры генератора текста"))
        self.symc_lbl.setText(_translate("MainWindow", "Количество символов"))
        self.symc_lbl_1.setText(_translate("MainWindow", "От"))
        self.symc_lbl_2.setText(_translate("MainWindow", "До"))
        self.label.setText(_translate("MainWindow", "Алфавит"))
        self.worc_lbl.setText(_translate("MainWindow", "Количество слов"))
        self.gen_w_btn.setText(_translate("MainWindow", "Сгенерировать слово"))
        self.gen_t_btn.setText(_translate("MainWindow", "Сгенерировать текст"))
        self.gen_s_btn.setText(_translate("MainWindow", "Сохранить эксперимент"))
        self.gen_l_btn.setText(_translate("MainWindow", "Загрузить эксперимент"))
        self.search_box.setTitle(_translate("MainWindow", "Параметры нечёткого поиска"))
        self.dif_lbl.setText(_translate("MainWindow", "Количество расхождений хэша"))
        self.req_lbl.setText(_translate("MainWindow", "Поисковый запрос"))
        self.search_btn.setText(_translate("MainWindow", "Начать поиск"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())