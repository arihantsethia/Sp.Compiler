#include <iostream>
#include <list>
#include <climits>

using namespace std;

class node{
public:
	int index,wt;
	node(int n,int x){
		index = n;
		wt = x;
	}
};

class vertex{
public:
	int id,d,parent;;
	list<node> adj;
	vertex(){
		parent = -1;
	}
	vertex(int _id){
		id = _id;
		parent = -1;
	}

};

class Graph{
	int count, t;
	vertex *v;

	void addToList(int x, int y, int wt){
		node j(y,wt);
		v[x].adj.push_front(j);
	}

public:
	Graph(int n){
		v = new vertex[n];
		count = n;
		for(int i=0; i<n; i++){
			v[i].id = i;
		}
	}

	void generateGraph(){
		int choice,x,y,wt;
		cout<<"Enter 0 for Finish!.....Press any key to continue: ";
		cin>>choice;
		while(choice){
			cout<<"Enter X Y : ";
			cin>>x>>y;
			cout<<"Enter Weight : ";
			cin>>wt;
			addToList( x-1, y-1, wt);
			cout<<"Enter 0 for Finish!.....Press any key to continue: ";
			cin>>choice;
		}
	}

	void printGraph(){
		list<node>::iterator iter;
		for (int i = 0; i < count; i++) {
			cout<<i+1<<" : "; 
			for(iter = v[i].adj.begin(); iter != v[i].adj.end(); iter++){
				cout<<(iter->index)+1<<"\t";
			}
			cout<<endl;
		}
	}

	void printVertex(){
		for (int i = 0; i < count; i++) {
				cout<<v[i].id<<"\t"<<v[i].d<<"\n";
		}
	}

	bool bellman(int k){
		for(int i = 0; i < count; i++ ){
			v[i].d = INT_MAX;
			v[i].parent = -1;
		}
		v[k].d = 0;
		list<node>::iterator it;
		for(int j= 0; j< count; j++){
			for(int i =0 ;i < count; i++){
				for(it = v[i].adj.begin(); it != v[i].adj.end(); it++){
					if(v[it->index].d > v[i].d + it->wt ){
						v[it->index].d = v[i].d + it->wt;
						v[it->index].parent = i;
						//cout<<it->index<<"\t"<<i<<endl;
					}
				}
			}
		}
		for(int i =0 ; i<count; i++) {
			for(it = v[i].adj.begin(); it != v[i].adj.end(); it++){
				if(v[it->index].d > v[i].d + it->wt )
					return false;
			}
		}
		return true;
	}
};

int main(){
	int **a,length,choice;
	cin>>length;
	Graph g(length);
	g.generateGraph();
	cout<<"Printed Graph\n";
	g.printGraph();
	cout<<"\nEnter ID : \n";
	cin>>choice;
	if(g.bellman(choice-1))
		g.printVertex();
	else 
		cout<<"No Shortest Distance \n";
	return 0;
}