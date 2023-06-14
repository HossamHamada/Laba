 #include <iostream>
 #include <string.h>
 #include <conio.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
const int n = 10;
void CreateMas1(float a[n][n], int);             
void VivodMas1(const float a[n][n], int);    
float sum(float a[n][n], int);     
float product(float a[n][n], int);  

int main()
{
system("cls");
int n1;
float a[n][n];

  printf("vvedite chislo strok i stolbcov ot 1 do 10\n");
  scanf("%d",&n1);

  //cout << a <<"=adres massiva a\n"; //????? ??????? ? ??????????

  CreateMas1(a, n1);
//  VivodMas1(a, n1);
  float summ=sum(a, n1);
  float production=product(a, n1);
  printf("Sum of matrix elements = %.02f\n",summ);
  printf("Product of matrix elements  = %.02f\n",production);

  getch();
  return 0;
}
//---F U N C T I O N-------------------------------------------//
void CreateMas1(float a[n][n], int n)
{
int i,j;
srand(time(0));
     for (i=0; i<n; i++)
	{
	for (j=0; j<n; j++)
	   {
	     a[i][j]=(float)(rand()%200 - 100);
	     printf("%2.02f\t",a[i][j]);
	    }
	   printf("\n");
	}

}
void VivodMas1(const float a[n][n], int n)
{
printf("M A S S I V E\n");
int i,j;
     for (i=0; i<n; i++)
      {
	for (j=0; j<n; j++)
	   {
	     printf("%2.02f\t",a[i][j]);
	   }
	printf("\n");
      }
}

float sum(float a[n][n], int n)
{
  float result=0;
int i,j;
     for (i=0; i<n; i++)
      {
	for (j=0;j<n; j++)
	   {
	   	if(a[i][j]<0){
	     result+=a[i][j];
		}
	   }
      }
      return result;
}

float product(float a[n][n], int n)
{
 float result=1.0;
int i,j;
     for (i=0; i<n; i++)
      {
	for (j=0; j<n; j++)
	   {
	   	if(a[i][j]>0){
	     result*=a[i][j];
		 }
	   }
      }
      return result;
}

