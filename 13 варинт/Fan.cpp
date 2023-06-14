#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <locale>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//тип данных для информации о вентиляторе
struct Characteristic {
    char blades[25];
    int power;
    int frequency;
};


//тип данных для вентилятора
struct Fan {
    char model[25];
    char country[25];
    int year;
    char material[25];
    Characteristic characteristic;
};

//тип данных для имени файла
typedef char TName[25];
//тип данных для файловой переменной
typedef FILE TFile;
//переменная для вентилятора
Fan fan;
//переменная для имени файла
TName NameFile;
//файловая переменная
TFile *f;
//флаг выбора файла для работы
int flag = 0;

//** вывод меню ************************************************************
void menu(void) {
    system("cls");
    cout << "******** М Е Н Ю ********\n\n"
         << "[1]-Создание/открытие типизированного файла\n"
         << "[2]-Добавление в файл записей\n"
         << "[3]-Удаление из файла записей\n"
         << "[4]-Просмотр всего файла\n"
         << "[5]-Обновление записи с заданным номером\n"
         << "[6]-Выполнение задания. Поиск вентилятора по мошности.\n"
         << "[ ESC ]-Выход\n";
}

//** ввод Вентилятора *****************************************************
void InputFan(Fan &fan) {
    cin.clear(); //очистить поток и затем выставить позиционирование в 0
    while (!isspace(cin.get())) //Избавиться от результатов неверного ввода
        continue;
    cout << "Добавление вентилятора:\n";
    cout << "Наименование модели ->";
    cin.getline(fan.model, 25);

    cout << "Год выпуска->";
    cin >> fan.year;

    cin.clear();
    while (!isspace(cin.get())) //Избавиться от результатов неверного ввода
        continue;
    cout << "Страна производитель->";
    cin.getline(fan.country, 25);

    cout << "Технология материала вентилятора->";
    cin >> fan.material;

    cout << "\n Технические характеристики:\n";
    cout << "\t Рабочая частота в герцах->";
    cin >> fan.characteristic.frequency;
    cout << "\t Номинальная мощность в ваттах->";
    cin >> fan.characteristic.power;
    cin.clear();
    while (!isspace(cin.get()))
        continue;
    cout << "\t Количество лопастей вентилятора->";
    gets(fan.characteristic.blades);
    cout << "Конец ввода";

}

//** вывод Вентилятора на экран ************************************************
void OutputFan(Fan &fan) {
    cout << "Наименование модели вентилятора: " << fan.model << "\n"
         << "Наименование страны вентилятора: " << fan.country << "\n"
         << "Материал лопастей вентилятора: " << fan.material << "\n"
         << "Год выпуска вентилятора: " << fan.year << " г.\n"
         << "Технические характеристики вентилятора:\n"
         << "\tКоличество лопастей: " << fan.characteristic.blades << "\n"
         << "\tРабочая частота:" << fan.characteristic.frequency << " Гц\n"
         << "\tНоминальная мощность: " << fan.characteristic.power << " Вт\n";
}

//** создание/открытие файла базы данных ********************************

void CreateOpenFile(TName &nameFile, int &flag) {
    char ch;
    flag = 0;
    cout << "Введите имя файла для работы-->";
    //scanf("%s",&NameFile);
    gets(nameFile);
    f = fopen(nameFile, "r");
    if (f == NULL)
        do {
            system("cls");
            cout << "ФАЙЛА с именем "
                 << nameFile
                 << " НЕТ.\n\n"
                 << "Создать файл с именем "
                 << nameFile;
            cout << "Нажмите [ Y ] / [ N ]\n";
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                f = fopen(nameFile, "w");
                cout << "Файл с именем " << nameFile << " создан.\n"
                     << "\n\nДля продолжения нажмите любую клавашу\n";
                getch();
                flag = 1;
            }
            if (ch == 'N' || ch == 'n') {
                cout << "Файл не создан.\n"
                     << "\n\nДля продолжения нажмите любую клавашу\n";
                getch();
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
    else {
        flag = 1;
        cout << "Файл успешно открыт\n"
             << "\nДля продолжения нажмите любую клавашу\n";
        getch();
    }
    fclose(f);
}

//** добавление записи (Вентиляторов) в файл (в базу данных) **********
void RecordFan(TName NameFile, Fan &fan, int flag) {
    if (flag) {
        f = fopen(NameFile, "a");
        InputFan(fan);
        fwrite(&fan, sizeof(fan), 1, f);
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}

//** вывод файла (базы данных) на экран *****************
void FileOutput() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  Вывод файла на экран  ********\n"
             << "****************************************\n";
        while (fread(&fan, sizeof(Fan), 1, f)) {
            //printf("%d",ftell(f));
            cout << "Номер записи = " << i + 1 << "\n\n";
            OutputFan(fan);
            cout << "****************************************" << "\n";
            i++;
            if (i % 3 == 0)  //вывод по несколько записей (Вентиляторов)
            {
                getch();
                system("cls");
                cout << "********  Вывод файла на экран  ********\n"
                     << "****************************************\n";
            }
        }
        getch();
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }

}

//** размер файла *****************************
long filesize(TFile *f) {
    long curpos, length;
    curpos = ftell(f);        //запоминаем текущее положение
    fseek(f, 0L, SEEK_END);    //перемещаем на конец файла
    length = ftell(f);        //запоминаем положение в конце файла
    fseek(f, curpos, SEEK_SET);    //перемещаем на старое положение
    return length;
}


//** обновление записи с заданным номером ******
void UpdateFan(TName NameFile, Fan &fan, int flag) {
    long i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  Обновление записи с заданным номером  ********\n\n"
             << "********************************************************\n\n"
             << "Введите номер записи для обновления "
             << "из "
             << (filesize(f) / sizeof(fan))
             << " --> ";
        cin >> i;
        //long q;
        fpos_t q;
        //перемещаемся на запись с номером i
        fseek(f, (i - 1) * sizeof(fan), SEEK_CUR);
        //запоминаем текущее положение
        fgetpos(f, &q);

        fread(&fan, sizeof(fan), 1, f);
        OutputFan(fan);
        cout << "****************************************\n";

        char ch;
        cout << "Обновить данные?\nНажмите [ Y ] / [ N ]\n";
        do {
            //clrscr();
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                //вводим новые значения
                InputFan(fan);
                //переходим на старое место
                fsetpos(f, &q);
                //записываем новые значения
                fwrite(&fan, sizeof(fan), 1, f);
                cout << "Данные обновлены.\n";
            }
            if (ch == 'N' || ch == 'n') {
                cout << "Данные не обновленны.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\nДля продолжения нажмите любую клавашу\n";
        getch();
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}

//** удаление вентилятора из базы **********************************
void DeleteFan(TName NameFile, Fan &fan, int flag) {
    long i = 0, k = 0;
    TFile *g;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  Удаление записи с заданным номером  ********\n\n"
             << "********************************************************\n\n"
             << "Введите номер записи для удаления "
             << "из "
             << (filesize(f) / sizeof(fan))
             << " --> ";
        cin >> i;

        //перемещаемся на запись с номером i
        fseek(f, (i - 1) * sizeof(fan), SEEK_CUR);
        fread(&fan, sizeof(fan), 1, f);
        OutputFan(fan);
        cout << "****************************************\n";

        char ch;
        cout << "Удалить данные?\n"
             << "Нажмите [ Y ] / [ N ]\n";
        do {
            //clrscr();
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                fseek(f, 0L, SEEK_SET);
                cout << "****" << ftell(f);
                g = fopen("Temp", "w");
                while (fread(&fan, sizeof(fan), 1, f)) {
                    if (k != (i - 1)) fwrite(&fan, sizeof(fan), 1, g);
                    k++;
                }
                cout << "Данные обновлены.\n";
                fclose(g);
                fclose(f);
                remove(NameFile);    //удаляем старый файл
                rename("Temp", NameFile);//переименовываем временный файл
            }
            if (ch == 'N' || ch == 'n') {
                cout << "Данные не обновленны.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\nДля продолжения нажмите любую клавашу\n";
        getch();
        //fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}

//******************** моя функция *****************
void SearchModelByPower() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r");
        int power;
        cout << "Введите мощность вентилятора для поиска --> ";
        cin >> power;

        cout << "********  Поиск вентилятора в базе данных  *************\n"
             << "********************************************************\n";
        while (fread(&fan, sizeof(fan), 1, f)) {


            if (fan.characteristic.power == power) {
                cout << "Номер записи = " << i + 1 << "\n\n";
                OutputFan(fan);
                cout << "********************************************************\n";
                i++;
                if (i % 3 == 0)  //вывод по несколько записей (вентиляторов)
                {
                    getch();
                    system("cls");
                    cout << "********  Поиск вентилятора в базе данных  *************\n"
                         << "********************************************************\n";
                }
            }
        }

        getch();
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}



//Начало программы

int main() {
    setlocale(0, "");
    char ch;
    system("cls");
    do {
        menu();
        ch = getch();
        switch (ch) {
            case '1':
                system("cls");
                CreateOpenFile(NameFile, flag); //создание и открытие файла базы данных
                break;
            case '2':
                system("cls");
                RecordFan(NameFile, fan, flag); //запись данных в файл
                //getch();
                break;
            case '3':
                system("cls"); // Удаление вентилятора из базы данных
                cout << "Удаление вентилятора из базы данных\n";
                DeleteFan(NameFile, fan, flag);
                getch();
                break;
            case '4':
                system("cls");    // вывод файла на экран
                FileOutput();
                break;
            case '5':
                system("cls");        //Обновление записи с заданным номером
                //printf("Обновление записи с заданным номером\n");
                UpdateFan(NameFile, fan, flag);
                //getch();
                break;
            case '6':
                system("cls");
                cout << "Выполнение задания в соответствии с вариантом:\n"
                     << "Поиск необходимой  в базе данных\n";
                SearchModelByPower();
                getch();
                break;
            case '8':
                exit(1);
        }
    } while (ch != 27);
    return 0;
}
