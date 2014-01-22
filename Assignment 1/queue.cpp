#include <iostream>

using namespace std;

class Queue
{
	int length,head,tail,*arr;
public:
	Queue(int x){
		length = x;
		head = 0;
		tail = 0;
		arr = new int[length];
	};
	void push(int key){
		if(tail-head >= length)
			cout<<"Error\n";
		else{
			arr[tail%length]=key;
			tail++;
		}
	}
	int pop(){
		if(head-tail>=0)
			return -1;
		head++;
		return arr[head-1];
	}

	int print(){
		for(int i = head; i<tail;i++)
		cout<<arr[i%length]<<endl;
	}

	/* data */
};

int main(){
	int length,choice,temp;
	cin>>length;
	Queue sk(length);
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