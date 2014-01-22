#include <iostream>

using namespace std;

class Stack
{
	int length,top,*arr;
public:
	Stack(int x){
		length = x;
		top = 0;
		arr = new int[length];
	};
	void push(int key){
		if(top >= length)
			cout<<"Overflow\n";
		else{
			arr[top]=key;
			top++;
		}
	}
	int pop(){
		if(top<=0)
			return -1;
		top--;
		return arr[top];
	}

	int print(){
		for(int i = top-1; i>=0;i--)
		cout<<arr[i]<<endl;
	}

	/* data */
};

int main(){
	int length,choice,temp;
	cin>>length;
	Stack sk(length);
	cout<<"Enter 1 for inserting into stack | 2 for printing stack | 3 for poping the element | 0 for exit"<<endl;
	cin>>choice;
	while(choice){
		if(choice==1){
			cout<<"Enter Element : ";
			cin>>temp;
			sk.push(temp);
		}
		else if(choice==2){
			cout<<"Stack at present is :"<<endl;
			sk.print();
		}
		else if(choice==3){
			cout<<"Popped Element : " <<sk.pop()<<endl;
		}			
		cout<<"Enter 1 for inserting into stack | 2 for printing stack | 3 for poping the element | 0 for exit"<<endl;
		cin>>choice;
	}
	return 0;

}