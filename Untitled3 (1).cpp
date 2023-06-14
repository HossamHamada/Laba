#include <iostream>
#include <math.h>
#include <locale.h>
using namespace std;

int main ()
{
	setlocale(LC_ALL, "rus");	
	cout << "Function value calculation\n" << endl;
	
	double x, y , t;
	cout << "Enter function argument --> ";
	cin >> x;
	t = x*x + 10*x - 2;
	if (x < - 7 && t > 0 && t  != 0)
			{
				y = sqrt(t);
				cout << "*x = " << x
					 << "    y = " << y
					 <<endl;				
			}
        else // x >= -7 or t <= 0 or (x >= -7 and t <= 0)
		if (x >= -7 && x < 0 &&  t != 0)
				{
				y = 1 / t;
				cout << "**x = " << x
					 << "    y = " << y
					 <<endl;

				}
		 else // x >= -7 or t <= 0 or (x >= -7 and t <= 0)
			if (x >= 0 && t !=0 && cos(t) )
			{
				y =  tan(t);
				cout << "***x = " << x
					 << "    y = " << y
					 <<endl;
			}
			else 
				cout << "***No solutions" << endl;

system("pause");
return 0;
}
