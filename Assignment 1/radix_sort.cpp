#include <iostream>

using namespace std;

void insertionSort(int a[],int n, int factor){
	for(int i=1; i<n; i++){
		int x = a[i];
		int j = i-1;
		while(a[j]>x && j>=0){
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = x;
	}
}

void radixSort(int a[], int d){
	for(int i=1; i<d; i++){
		for(int i)
	}
}

int main (){
	int k,n, *a;
	cin>>k;
	cin>>n;
	a = new int [n];
	for(int i=0; i<n; i++){
		cin>>a[i];
	}
	radixSort(a,k+1,n);
	cout<<"Sorted\n";
	print(a,0,n);
	return 0;
}