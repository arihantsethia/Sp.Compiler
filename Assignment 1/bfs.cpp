#include <iostream>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

enum Color {Black,White,Grey};


class node{
public:
	int index;
	node *next;
	node(){
		next= NULL;
	}
	node(int x){
		index = x;
		next = NULL;
	}

};

class vertex{
public:
	int d,key;
	node *p;
	Color color;
	vertex(){
		color = White;
		d = INT_MAX;
		p = NULL;
	}
};

class queue{
	vertex *a;
	int head,tail,length;
	queue(int n){
		a = new vertex[n];
		head = 0;
		tail = 0;
		length = n;
	} 
	void push(vertex s){
		if( tail-head>=length){
			cout<<"Error\n";
			return;
		}
		a[tail%length]=s;
		tail++;
	}
	vertex pop(){
		vertex temp;
		if(head - tail>=0)
			return temp;
		temp = a[head%length];
		head++;
	}

	bool empty(){
		if(head-tail == 0)
			return true;
		return false;
	} 

};




class graph{
private:	
	int count ; 
	node *nodes;
	vertex *v;
	
	void addnewnode(int from,int to){
		node *temp = new node(to);
		temp->next = nodes[from].next;
		nodes[from].next = temp;
	}

public:
	graph(int x){
		count =x;
		nodes = new node[count];
		generateGraph(x);
	}
	
	void generateGraph(int n){
		v = new vertex[n];
		int choice,from,to;
		cout<<"Generate the Graph | Press any number to continue | 0 for exit"<<endl;
		cin>>choice;
		while(choice){
			if(choice){
				cout<<"Enter from & to: ";
				cin>>from>>to;
				addnewnode(from-1,to-1);
			}
			cout<<"Press any number to continue | 0 for exit"<<endl;
			cin>>choice;
		}

	}
	
	void print(){
		for(int i=0; i<count; i++){
			node *temp = nodes[i].next;
			while(temp!=NULL){
				cout<<(temp->index)+1<<"\t";
				temp = temp->next;
			}
			cout<<endl;
		}
	}

	void BFS(vertex s){
		queue q(count);
		for(int i=0;i<count;i++){
				v[i].color = White;
				v[i].d = 0;
				v[i].p = NULL;
		}
		s.color = Grey;
		s.d = 0;
		q.push(s);

		while(!q.empty()){
			vertex u = q.pop();
			node *n = nodes[u];
			while(n!=NULL){
				if(v[n->data].color == White){
					v[n->data].color == Grey;
					v[n->data].d = u.d+ 1;
					v[n->data].p = u; 

				}					
			}
			u.color = Black;
		}
	}
};

int main(){
	int length,choice,from,to;
	cout<<"Enter number of nodes :";
	cin>>length;
	graph g(length);
	cout<<"Enter 1 for printing graph| 0 for exit"<<endl;
	cin>>choice;
	while(choice){
		if(choice==1){
			cout<<"Graph at present is :"<<endl;
			g.print();
		}
		cout<<"1 for printing graph| 0 for exit"<<endl;
		cin>>choice;
	}
	return 0;
}