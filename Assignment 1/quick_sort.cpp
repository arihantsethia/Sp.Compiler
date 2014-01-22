#include <iostream>

using namespace std;


void swap(int a[],int i, int j){
	int temp= a[i];
	a[i] = a[j];
	a[j] =temp;
}

void print(int a[],int p,int r){
	for(;p<r;p++)
	cout<<a[p]<<endl;
}

int partition(int *a,int low,int high)
{
    int p=low,r=high,x=a[r],i=p-1;
    for(int j=p;j<=r-1;j++)
    {
        if (a[j]<=x)
        {
            i=i+1;
            swap(a,i,j);
        }
    }
    swap(a,i+1,r);
    return i+1;
}


int quickSort(int a[], int p, int r){
	if(p<r){
		int q = partition(a,p,r);
		quickSort(a,p,q);
		quickSort(a,q+1,r);
	}
}

int main (){
	int length, *a;
	cin>>length;
	a = new int [length];
	for(int i=0; i<length; i++){
		cin>>a[i];
	}
	quickSort(a,0,length);
	cout<<"Sorted\n";
	print(a,0,length);
	return 0;
}