#include <iostream>
using namespace std;

int *a;
void merge(int p, int q,int r){
	int n1 = q-p+1;
	int n2 = r-q;
	int *l1 = new int[n1+1];
	int *l2 = new int[n2+1];
	for(int i=0;i<n1;i++)
		l1[i] = a[p+i];
	for(int i=0;i<n2;i++)
		l2[i] = a[q+i+1];
	l1[n1] = 1000000;
	l2[n2] = 1000000;
	int i=0;
	int j=0;
	for (int k=p; k<=r; k++){
		if(l1[i]<=l2[j]){
			a[k] = l1[i];
			i++;
		}
		else{
			a[k]=l2[j];
			j++;
		}
	}
}

void mergeSort(int p, int r){
	if (p<r){
		int q = (p+r)/2;
		mergeSort(p,q);
		mergeSort(q+1,r);
		merge(p,q,r);
	}
}

int main (){
	int length;
	cin>>length;
	a = new int [length];
	for(int i=0; i<length; i++){
		cin>>a[i];
	}
	mergeSort(0,length-1);
	cout<<"Sorted\n";
	for(int i=0; i<length; i++){
		cout<<a[i]<<endl;
	}
	return 0;
}
