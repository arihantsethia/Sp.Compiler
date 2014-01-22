#include <iostream>
#include <list>

using namespace std;

enum Color {WHITE,BLACK,GREY};

class node{
public:
	int index;
	node(int n){
		index = n;
	}
};

class vertex{
public:
	int data,id,parent,dist,finish;
	Color color;
	list<node> adj;
	vertex(){
		parent = -1;
	}
	vertex(int _data, int _id){
		data = _data;
		id = _id;
		parent = -1;
	}

};

class Graph{
	int count, t;
	vertex *v;

	void addToList(int directed, int x, int y){
		node j(y);
		v[x].adj.push_front(j);
		if(!directed){
			j.index = x;
			v[y].adj.push_front(j);
		}
	}

	void dfs_visit(int n){		
		list<node>::iterator iter;
		v[n].dist = ++t;
		v[n].color = GREY;
		for(iter = v[n].adj.begin(); iter != v[n].adj.end(); iter++){
			if(v[iter->index].color == WHITE){
				v[iter->index].parent = n;
				dfs_visit(iter->index);
			}
		}
		v[n].color = BLACK;
		v[n].finish = ++t;
		cout<<n+1<<"\t: "<<v[n].finish<<"\n";
	}

public:
	Graph(int n){
		v = new vertex[n];
		count = n;
		int data;
		for(int i=0; i<n; i++){
			cout<<"Enter the data in "<<i+1<<" Vertex : ";
			cin>>v[i].data;
			v[i].id = i;
		}
	}

	void generateGraph(int directed){
		int choice,x,y;
		cout<<"Enter 0 for Finish!.....Press any key to continue: ";
		cin>>choice;
		while(choice){
			cout<<"Enter X Y : ";
			cin>>x>>y;
			addToList(directed, x-1, y-1);
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

	void dfs(){
		for(int i=0; i<count; i++){
			v[i].color = WHITE;
			v[i].parent = -1;
		}
		t = 0;
		for(int i=0; i8< count; i++){
			if(v[i].color==WHITE){
				dfs_visit(i);
			}
		}
	}
};

int main(){
	int **a,length,choice;
	cin>>length;
	Graph g(length);
	cout<<"Enter 0 for undirected graph and 1 for directed graph : ";
	cin>>choice;
	g.generateGraph(choice);
	cout<<"Printed Graph\n";
	g.printGraph();
	cout<<"\nDFS TRAVERSAL\n";
	g.dfs();
	return 0;
}