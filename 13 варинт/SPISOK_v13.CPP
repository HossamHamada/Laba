#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

struct pointer
{ int d;
  pointer *p;
};

//=====================
void FormOch(pointer **ph, int data)
{
 *ph = new pointer;
 
 (*ph) -> d = data;
 (*ph)->p = NULL;
}

//======================
void DobOch (pointer **pk, int data)
      {   
	  pointer *px=new pointer;
	  px->d=data;
	  px->p=NULL;
	  (*pk)->p=px;
	  *pk=px;
	  //(*pk)->p=NULL;
       }
//======================
void IskOch (pointer **ph, int &data)
{ data = (*ph)->d;
  *ph = (*ph)->p;
}

//======================
int main()
{
//system("cls");
// ======= Формирование очереди ======
 pointer *ph=NULL;
 cout<<"Input 1 element -->" ;
 int data;
 cin >> data ;
 
 FormOch(&ph, data);
 pointer *pk = ph;
  int i = 1;	//счетчик всех элементов
  int k = 1;	//счетчик элементов в "трубе"
  int t = 8; 	// длина "трубы"
//cout<<"====="<<ph->d<<pk->d;
// ======= Добавление в очередь ======
while (data!=0)
 {
	cout<<"Input "<<i+1<<" element -->" ;
	cin >> data;
	if (data == 0) break;
	DobOch(&pk, data);
	k++;
	i++;
	if (k >= t+1)
		{
			IskOch(&ph, data);
			cout<<"-------->> "<< data << endl ;
			//ph = ph->p;
		}
 }
 
 while (ph != NULL)
 {
 	IskOch(&ph, data);
	cout<<"-------->> "<< data << endl ;
 }
 
getch();
 }
