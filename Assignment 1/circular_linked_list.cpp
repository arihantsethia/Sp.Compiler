#include <iostream>

using namespace std;

class node{
public:
	node *next;
	int key;
	node(int x){
		next = NULL;
		key = x;
	}
};

class LinkedList{
	node *head;
public:
	LinkedList(){
		head = NULL;
	}
	void addNode(int x){
		if(head == NULL)
			head = new node(x);
		else {
			node *temp = head;
			while(temp->next != NULL)
				temp = temp->next;
			node *newnode = new node(x);
			newnode->next = head;
			temp->next = newnode;
		}
	}

	void removeNode(int x){
		if(head == NULL)
			cout<<"error\n";
		else {
			node *temp = head;
			if(temp->key == x ){
				head = temp->next;
				delete temp;
				return;
			}
			node *prev = temp;
			while(temp->next != head){
				if(temp->key == x){
					prev->next = temp->next;
					delete temp;
					return;
				}
				prev = temp;
				temp=temp->next;
			}
			restoreCircular();
			cout<<"Not Found\n";
		}
	}

	void findMiddle(){
		node *fast = head;
		node *slow = fast;
		while(fast!=NULL && fast->next!= NULL){
			slow=slow->next;
			fast=fast->next->next;
		}
		if(slow!=NULL)	
			cout<<"The Middle Element is "<<slow->key<<endl;
		else
			cout<<"Empty\n";
	}
	void print(){
		node *temp = head;
		while(temp!=NULL){
			cout<<temp->key<<"\t";
			temp=temp->next;
		}	
		cout<<endl;
	}

	void restoreCircular(){
		node *temp = head;
		while(temp->next!=NULL){
			temp = temp->next;
		}
		temp->next=head;
	}

};

int main(){
	int choice,temp;
	LinkedList sk;
	cout<<"Enter 1 for inserting into List | 2 for printing list | 3 for deleting the element | 4 for finding the middle element| 0 for exit"<<endl;
	cin>>choice;
	while(choice){
		if(choice==1){
			cout<<"Enter Element : ";
			cin>>temp;
			sk.addNode(temp);
		}
		else if(choice==2){
			cout<<"Linked at present is :"<<endl;
			sk.print();
		}
		else if(choice==3){
			cout<<"Enter Element : ";
			cin>>temp;
			sk.removeNode(temp);
		}	else if(choice==4){
			sk.findMiddle();
		}				
		cout<<"Enter 1 for inserting into List | 2 for printing list | 3 for deleting the element | 4 for finding the middle element| 0 for exit"<<endl;
		cin>>choice;
	}
	return 0;
}