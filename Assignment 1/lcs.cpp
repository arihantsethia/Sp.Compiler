#include <iostream>

using namespace std;

int main(){
	int n,*a,*l;
	cin>>n;
	a = new int[n];
	l = new int[n];
	for(int i=0; i <n;i++){
		cin>>a[i];
	}
	
	for(int i=0; i <n;i++){
		int max =0;
		for(int j=0;j<i;j++){
			if(a[i]>a[j]){
				if(max<l[j])
					max = l[j];
			}
		}
		l[i] = max + 1;
	}
	for(int i=0; i <n;i++){
		cout<<l[i]<<endl;
	}
	
	return 0;
}