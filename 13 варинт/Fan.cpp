#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <locale>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//��� ������ ��� ���������� � �����������
struct Characteristic {
    char blades[25];
    int power;
    int frequency;
};


//��� ������ ��� �����������
struct Fan {
    char model[25];
    char country[25];
    int year;
    char material[25];
    Characteristic characteristic;
};

//��� ������ ��� ����� �����
typedef char TName[25];
//��� ������ ��� �������� ����������
typedef FILE TFile;
//���������� ��� �����������
Fan fan;
//���������� ��� ����� �����
TName NameFile;
//�������� ����������
TFile *f;
//���� ������ ����� ��� ������
int flag = 0;

//** ����� ���� ************************************************************
void menu(void) {
    system("cls");
    cout << "******** � � � � ********\n\n"
         << "[1]-��������/�������� ��������������� �����\n"
         << "[2]-���������� � ���� �������\n"
         << "[3]-�������� �� ����� �������\n"
         << "[4]-�������� ����� �����\n"
         << "[5]-���������� ������ � �������� �������\n"
         << "[6]-���������� �������. ����� ����������� �� ��������.\n"
         << "[ ESC ]-�����\n";
}

//** ���� ����������� *****************************************************
void InputFan(Fan &fan) {
    cin.clear(); //�������� ����� � ����� ��������� ���������������� � 0
    while (!isspace(cin.get())) //���������� �� ����������� ��������� �����
        continue;
    cout << "���������� �����������:\n";
    cout << "������������ ������ ->";
    cin.getline(fan.model, 25);

    cout << "��� �������->";
    cin >> fan.year;

    cin.clear();
    while (!isspace(cin.get())) //���������� �� ����������� ��������� �����
        continue;
    cout << "������ �������������->";
    cin.getline(fan.country, 25);

    cout << "���������� ��������� �����������->";
    cin >> fan.material;

    cout << "\n ����������� ��������������:\n";
    cout << "\t ������� ������� � ������->";
    cin >> fan.characteristic.frequency;
    cout << "\t ����������� �������� � ������->";
    cin >> fan.characteristic.power;
    cin.clear();
    while (!isspace(cin.get()))
        continue;
    cout << "\t ���������� �������� �����������->";
    gets(fan.characteristic.blades);
    cout << "����� �����";

}

//** ����� ����������� �� ����� ************************************************
void OutputFan(Fan &fan) {
    cout << "������������ ������ �����������: " << fan.model << "\n"
         << "������������ ������ �����������: " << fan.country << "\n"
         << "�������� �������� �����������: " << fan.material << "\n"
         << "��� ������� �����������: " << fan.year << " �.\n"
         << "����������� �������������� �����������:\n"
         << "\t���������� ��������: " << fan.characteristic.blades << "\n"
         << "\t������� �������:" << fan.characteristic.frequency << " ��\n"
         << "\t����������� ��������: " << fan.characteristic.power << " ��\n";
}

//** ��������/�������� ����� ���� ������ ********************************

void CreateOpenFile(TName &nameFile, int &flag) {
    char ch;
    flag = 0;
    cout << "������� ��� ����� ��� ������-->";
    //scanf("%s",&NameFile);
    gets(nameFile);
    f = fopen(nameFile, "r");
    if (f == NULL)
        do {
            system("cls");
            cout << "����� � ������ "
                 << nameFile
                 << " ���.\n\n"
                 << "������� ���� � ������ "
                 << nameFile;
            cout << "������� [ Y ] / [ N ]\n";
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                f = fopen(nameFile, "w");
                cout << "���� � ������ " << nameFile << " ������.\n"
                     << "\n\n��� ����������� ������� ����� �������\n";
                getch();
                flag = 1;
            }
            if (ch == 'N' || ch == 'n') {
                cout << "���� �� ������.\n"
                     << "\n\n��� ����������� ������� ����� �������\n";
                getch();
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
    else {
        flag = 1;
        cout << "���� ������� ������\n"
             << "\n��� ����������� ������� ����� �������\n";
        getch();
    }
    fclose(f);
}

//** ���������� ������ (������������) � ���� (� ���� ������) **********
void RecordFan(TName NameFile, Fan &fan, int flag) {
    if (flag) {
        f = fopen(NameFile, "a");
        InputFan(fan);
        fwrite(&fan, sizeof(fan), 1, f);
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}

//** ����� ����� (���� ������) �� ����� *****************
void FileOutput() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  ����� ����� �� �����  ********\n"
             << "****************************************\n";
        while (fread(&fan, sizeof(Fan), 1, f)) {
            //printf("%d",ftell(f));
            cout << "����� ������ = " << i + 1 << "\n\n";
            OutputFan(fan);
            cout << "****************************************" << "\n";
            i++;
            if (i % 3 == 0)  //����� �� ��������� ������� (������������)
            {
                getch();
                system("cls");
                cout << "********  ����� ����� �� �����  ********\n"
                     << "****************************************\n";
            }
        }
        getch();
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }

}

//** ������ ����� *****************************
long filesize(TFile *f) {
    long curpos, length;
    curpos = ftell(f);        //���������� ������� ���������
    fseek(f, 0L, SEEK_END);    //���������� �� ����� �����
    length = ftell(f);        //���������� ��������� � ����� �����
    fseek(f, curpos, SEEK_SET);    //���������� �� ������ ���������
    return length;
}


//** ���������� ������ � �������� ������� ******
void UpdateFan(TName NameFile, Fan &fan, int flag) {
    long i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  ���������� ������ � �������� �������  ********\n\n"
             << "********************************************************\n\n"
             << "������� ����� ������ ��� ���������� "
             << "�� "
             << (filesize(f) / sizeof(fan))
             << " --> ";
        cin >> i;
        //long q;
        fpos_t q;
        //������������ �� ������ � ������� i
        fseek(f, (i - 1) * sizeof(fan), SEEK_CUR);
        //���������� ������� ���������
        fgetpos(f, &q);

        fread(&fan, sizeof(fan), 1, f);
        OutputFan(fan);
        cout << "****************************************\n";

        char ch;
        cout << "�������� ������?\n������� [ Y ] / [ N ]\n";
        do {
            //clrscr();
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                //������ ����� ��������
                InputFan(fan);
                //��������� �� ������ �����
                fsetpos(f, &q);
                //���������� ����� ��������
                fwrite(&fan, sizeof(fan), 1, f);
                cout << "������ ���������.\n";
            }
            if (ch == 'N' || ch == 'n') {
                cout << "������ �� ����������.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\n��� ����������� ������� ����� �������\n";
        getch();
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}

//** �������� ����������� �� ���� **********************************
void DeleteFan(TName NameFile, Fan &fan, int flag) {
    long i = 0, k = 0;
    TFile *g;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  �������� ������ � �������� �������  ********\n\n"
             << "********************************************************\n\n"
             << "������� ����� ������ ��� �������� "
             << "�� "
             << (filesize(f) / sizeof(fan))
             << " --> ";
        cin >> i;

        //������������ �� ������ � ������� i
        fseek(f, (i - 1) * sizeof(fan), SEEK_CUR);
        fread(&fan, sizeof(fan), 1, f);
        OutputFan(fan);
        cout << "****************************************\n";

        char ch;
        cout << "������� ������?\n"
             << "������� [ Y ] / [ N ]\n";
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
                cout << "������ ���������.\n";
                fclose(g);
                fclose(f);
                remove(NameFile);    //������� ������ ����
                rename("Temp", NameFile);//��������������� ��������� ����
            }
            if (ch == 'N' || ch == 'n') {
                cout << "������ �� ����������.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\n��� ����������� ������� ����� �������\n";
        getch();
        //fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}

//******************** ��� ������� *****************
void SearchModelByPower() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r");
        int power;
        cout << "������� �������� ����������� ��� ������ --> ";
        cin >> power;

        cout << "********  ����� ����������� � ���� ������  *************\n"
             << "********************************************************\n";
        while (fread(&fan, sizeof(fan), 1, f)) {


            if (fan.characteristic.power == power) {
                cout << "����� ������ = " << i + 1 << "\n\n";
                OutputFan(fan);
                cout << "********************************************************\n";
                i++;
                if (i % 3 == 0)  //����� �� ��������� ������� (������������)
                {
                    getch();
                    system("cls");
                    cout << "********  ����� ����������� � ���� ������  *************\n"
                         << "********************************************************\n";
                }
            }
        }

        getch();
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}



//������ ���������

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
                CreateOpenFile(NameFile, flag); //�������� � �������� ����� ���� ������
                break;
            case '2':
                system("cls");
                RecordFan(NameFile, fan, flag); //������ ������ � ����
                //getch();
                break;
            case '3':
                system("cls"); // �������� ����������� �� ���� ������
                cout << "�������� ����������� �� ���� ������\n";
                DeleteFan(NameFile, fan, flag);
                getch();
                break;
            case '4':
                system("cls");    // ����� ����� �� �����
                FileOutput();
                break;
            case '5':
                system("cls");        //���������� ������ � �������� �������
                //printf("���������� ������ � �������� �������\n");
                UpdateFan(NameFile, fan, flag);
                //getch();
                break;
            case '6':
                system("cls");
                cout << "���������� ������� � ������������ � ���������:\n"
                     << "����� �����������  � ���� ������\n";
                SearchModelByPower();
                getch();
                break;
            case '8':
                exit(1);
        }
    } while (ch != 27);
    return 0;
}
