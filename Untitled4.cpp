#include <iostream>
#include <math.h>
using namespace std;

long double fact(int N)
{
    if(N < 0) 
    return 0; 
    if (N == 0) 
    return 1; 
    else 
    return N * fact(N - 1); 
}

int main(int argc, char** argv) {
	int n, x, k = 0;
	float total = 0;
	cout<<"Enter n, x: ";
	cin>>n>>x;
	
	while (k <= n){
	total += ((pow(-1, k) * (pow(x, (4*k)+5)))/
     (((4*k)+1)*((4*k)+5))* fact(k+1));
	k++;
	}
	
	cout<<"Result: "<<total;
	
	return 0;
}


