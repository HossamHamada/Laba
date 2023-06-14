#include <iostream>

using namespace std;

int main(){
	int N, x, k=0, i=0;
	cout<<"Enter number of numbers\n";
	cin>>N;
	if(N<=0) {
		cout<< "ERROR";
		return -1;
	}
	while (i<N){
		cin>>x;
		if(x==0){
			cout<<"ERROR numbers should not be 0";
			return -1;
		}
		
		if(x%2==0){
			k++;
			cout<<x<<"\n";
		}
		i++;
	}
	cout << "Number of even numbers is equal to "<< k;
}
