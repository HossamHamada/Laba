#include <iostream>
#include <math.h>
using namespace std;


int main(int argc, char** argv)
 {
	int a, b;
	long int X;
	cout<<"Enter a, b: ";
	cin>>a>>b;
	
	if (a < b && a / b - 42 != 0){
		X = (a/b)-42;
	}else if ( a == b){
		X = -11;
	} else if (a > b && a!=0 ){
		X = ((pow(a, 3)-8)/(a));
	}
	
	cout<<"Result: "<< X;
	
	return 0;
}
