#include <iostream>

using namespace std;

void swap(int a[],int i, int j){
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void insertionSort(int a[],int n){
	for(int i=1;i<n;i++){
		int x = a[i];
		int j = i-1;
		while(a[j]> x && j>=0){
			a[j+1]=a[j];
			j--;
		}
		a[j+1] = x;
	}
}

void print(int a[],int n){
	for(int i=0;i<n;i++)
	cout<<a[i]<<endl;
}

int main(){
	int n,*a;
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>a[i];
	insertionSort(a,n);
	cout<<"Sorted Array \n";
	print(a,n);
	return 0;
}