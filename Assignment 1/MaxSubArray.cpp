#include <iostream>

using namespace std;

int max(int a,int b){
	if(a>=b)
		return a;
	else
		return b;
}

int maxArray(int a[],int n){
	int max_local = 0, max_global =0;
	for(int i=0;i<n;i++){
		max_local = max(a[i],max_local+a[i]);
		max_global = max(max_global,max_local);
	}
	return max_global;
}


int main(){
	int n;
	cin>>n;
	int *a = new int[n];
	for(int i=0; i<n; i++)
		cin>>a[i];
	int sum = maxArray(a,n); 
	cout<<sum<<endl;
	return 0;
}