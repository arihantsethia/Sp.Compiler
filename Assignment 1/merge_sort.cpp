#include <iostream>
#include <climits>

using namespace std;

void print(int a[],int p,int r){
	for(;p<r;p++)
	cout<<a[p]<<endl;
}

void merge(int a[],int p, int q, int r){
	int i=p,j=q+1,k=0;
	int *b = new int[r-p+1];
	while(k<r-p+1){
		if(i <= q && j<= r){
			if(a[i] < a[j])
				b[k++]=a[i++];
			else
				b[k++]=a[j++];
		} else if (i>q) {
			for(;j<=r;j++,k++)
				b[k]=a[j];
		} else {
			for(;i<=q; i++, k++)
				b[k] = a[i];
		}
	}
	for(i=p,j=0; i<=r; i++,j++)
		a[i] = b[j]; 
}

void mergeSort(int a[], int p, int r){
	if(p<r){
		int q = (r-p)/2 +p;
		mergeSort(a,p,q);
		mergeSort(a,q+1,r);
		merge(a,p,q,r);
		print(a,p,r);
	}
}

int main(){
	int n,*a;
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>a[i];
	mergeSort(a,0,n-1);
	cout<<"Sorted Array \n";
	print(a,0,n);
	return 0;
}
