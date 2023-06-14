#include <iostream>

using namespace std;

int main()
{
	int N;
	int k=0;
	int x;
	cout<<"Enter number of numbers\n";
	cin>>N;
	for (int i =0;i<N;i++)
	{
		cin>>x;
		if(x%2==0){
			k++;
			cout<<x<<"\n";
		}	
	}
	cout << "Number of even numbers is equal to "<< k;
}


