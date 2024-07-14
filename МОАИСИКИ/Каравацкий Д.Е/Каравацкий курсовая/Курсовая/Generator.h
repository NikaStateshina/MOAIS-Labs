#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;


//n - размерность массива
void qsortKillSeqGen(int n, string dir) {

    string filename = dir + "//" + "Medof3_" + to_string(n) + "_" + "1.txt";
    ifstream file(filename);
    int i = 1;

    while (!file.fail()) {
        file.close();
        i++;
        filename = dir + "//" + "Medof3_" + to_string(n) + "_" + to_string(i) + ".txt";
        file.open(filename); // Открываем новый файл для чтения
    }

    ofstream out(filename);
    out << n << endl;

    //Генерация

    //Четные
    if (n % 2 == 0) {
        int m = n / 2 - 1;
        for (int i = 0; i < m; ++i) {

            if (i % 2 == 0) {
                out << i + 1 << " ";
            }
            else {
                if (m % 2 != 0) {
                    out << m + i + 1 << " ";
                }
                else out << m + i << " ";
            }
        }
        m = n - m;
        for (int i = 0; i < m; i++) {
            out << (i + 1) * 2 << " ";
        }
    }

    //Нечетные
    else {
        int m = n / 2;
        for (int i = 0; i < m; ++i) {
            if (i % 2 == 0) {
                out << i + 1 << " ";
            }
            else {
                if (m % 2 != 0) {
                    out << m + i + 1 << " ";
                }
                else out << m + i << " ";
            }
        }
        m = n - m;
        for (int i = 0; i < m; i++) {
            out << (i + 1) * 2 << " ";
        }
    }
    out.close();
}


void upSortedSequence(int n, string dir) {

    string filename = dir + "//" + "Up_" + to_string(n) + "_" + "1.txt";
    ifstream file(filename);
    int i = 1;

    while (!file.fail()) {
        file.close();
        i++;
        filename = dir + "//" + "Up_" + to_string(n) + "_" + to_string(i) + ".txt";
        file.open(filename); // Открываем новый файл для чтения
    }

    ofstream out(filename);
    out << n << endl;

    for (int i = 0; i < n; i++) {
        out << i << " ";
    }
    out.close();
}



void downSortedSequence(int n, string dir) {

    string filename = dir + "//" + "Down_" + to_string(n) + "_" + "1.txt";
    ifstream file(filename);
    int i = 1;

    while (!file.fail()) {
        file.close();
        i++;
        filename = dir + "//" + "Down_" + to_string(n) + "_" + to_string(i) + ".txt";
        file.open(filename); // Открываем новый файл для чтения
    }

    ofstream out(filename);
    out << n << endl;

    for (int i = n; i > 0; i--) {
        out << i << " ";
    }
    out.close();
}


void randSequence(int n, string dir) {

    std::random_device rd;  // Устройство для генерации случайных чисел
    std::mt19937 gen(rd()); // Инициализация генератора случайных чисел с seed от rd()
    int min_value = 0;
    int max_value = 100000;
    std::uniform_int_distribution<> distrib(min_value, max_value); // Равномерное распределение в заданном диапазоне
    int random_value = 0;

    string filename = dir + "//" + "Rand_" + to_string(n) + "_" + "1.txt";
    ifstream file(filename);
    int i = 1;

    while (!file.fail()) {
        file.close();
        i++;
        filename = dir + "//" + "Rand_" + to_string(n) + "_" + to_string(i) + ".txt";
        file.open(filename); // Открываем новый файл для чтения
    }

    ofstream out(filename);
    out << n << endl;

    for (int i = 0; i < n; i++) {
        out << distrib(gen) << " ";
    }
    out.close();
}