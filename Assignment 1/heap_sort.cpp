#include <iostream>

using namespace std;

int heapSize = 0;

void swap(int a[],int i, int j){
	int temp= a[i];
	a[i] = a[j];
	a[j] =temp;
}

void print(int a[],int n){
	for(int i=0;i<n;i++)
	cout<<a[i]<<endl;
}

void maxHeapify(int a[], int i){
	int l = 2*i+1;
	int r = 2*(i+1);
	int largest;
	if( l< heapSize && a[i] < a[l])
		largest = l;
	else 
		largest = i;
	if( r< heapSize && a[largest]<a[r])
		largest = r;
	if(largest != i){
		swap(a,largest,i);
		maxHeapify(a,largest);
	}

}

void buildMaxHeap(int a[],int n){
	heapSize = n;
	for(int i = (n-1)/2 ;i>=0;i--){
		maxHeapify(a,i);
	}
}

void heapSort(int a[],int n){
	buildMaxHeap(a,n);
	for(int i = n-1; i > 0 ; i--){
		swap(a,i,0);
		heapSize-- ;
		maxHeapify(a,0);
	}
}


int main(){
	int n,*a;
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>a[i];
	heapSort(a,n);
	cout<<"Sorted Array \n";
	print(a,n);
	return 0;
}