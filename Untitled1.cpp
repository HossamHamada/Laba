#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char** argv)
 {
	float a,b, total;
	
	int c,d;
	
	
	cout<<"Enter a, b, c, d: ";
	cin>>a>>b>>c>>d;
	if (c-(tan(a/2))!=0){
	total = (4*c+d-1) / (c-(tan(a/2)));
	cout<<"Result: "<< total;}
	else {
		cout<<"Net resultata";
	}
	return 0;
}

