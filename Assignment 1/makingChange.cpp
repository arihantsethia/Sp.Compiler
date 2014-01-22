#include <iostream>

using namespace std;

int main(){
	int n,amt,*c,*change;
	cin>>n;
	c = new int[n];
	for (int i = 0; i < n; i++)
		cin>>c[i];
	cin>>amt;
	change = new int[amt+1];
	change[0]=0;
	for(int i=1; i<=amt;i++){
		int min = 5000;
		for(int j=0; j <n;j++){
			if(i >= c[j]){
				if(min>change[i-c[j]])
					min=change[i-c[j]];
			}
		}
		change[i] = min+1;
	}
	cout<<change[amt]<<endl;
	return 0;
}