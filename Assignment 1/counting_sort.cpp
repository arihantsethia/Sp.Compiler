#include <iostream>

using namespace std;

void print(int a[],int p,int r){
	for(;p<r;p++)
	cout<<a[p]<<endl;
}

int* countingSort(int a[],int k,int n){
	int *c = new int[k]();
	int *b = new int[n];
	for(int i=0; i<n;i++){
		c[a[i]]++;
	}
	for(int i=1; i<k;i++){
		c[a[i]]+= c[a[i-1]];
	}
	for(int i=n-1; i>-1;i--){
		b[c[a[i]]-1]=a[i];
		c[a[i]]--;
	}
	return b;
}

int main (){
	int k,n, *a;
	cin>>k;
	cin>>n;
	a = new int [n];
	for(int i=0; i<n; i++){
		cin>>a[i];
	}
	a = countingSort(a,k+1,n);
	cout<<"Sorted\n";
	print(a,0,n);
	return 0;
}