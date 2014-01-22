#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

class vertex{
public:
	int data,id,parent,priority;
	vertex(){
		parent = -1;
	}
	vertex(int _data, int _id){
		data = _data;
		id = _id;
		parent = -1;
	}

	bool operator >(vertex& v1){
		return priority > v1.priority;
	}

	bool operator <(vertex& v1){
		return priority < v1.priority;
	}
};

class priority_queue{
	vector<vertex> queue;
public:
	void swap(int i, int j){
		vertex temp = queue[i];
		queue[i] = queue[j];
		queue[j] =  temp;
	}

	void insert(vertex x){
		queue.push_back(x);
		int i = queue.size()-1;
		while(i>0 && queue[i] < queue[(i-1)/2]) {
			swap(i,(i-1)/2);
			i = (i-1)/2;
		}
	}

	void changePriority(int x,int newPriority){
		for(int i = 0; i < queue.size(); i++){
			if(queue[i].id == x){
				if(queue[i].priority > newPriority){
					queue[i].priority = newPriority;
					while(i>0 && queue[i] < queue[(i-1)/2]) {
						swap(i,(i-1)/2);
						i = (i-1)/2;
					}
				}
				break;
			}
		}
	}

	vertex pop(){
		vertex temp = queue[0];	
		swap(queue.size()-1, 0);
		queue.pop_back();
		minHeapify(0);
		return temp;
	}

	bool contains( int x){
		vector<vertex>::iterator it;
		for(it = queue.begin(); it!=queue.end(); it++){
			if(it->id == x){
				return true;
			}
		}
		return false;
	}

	void print(){
		vector<vertex>::iterator it;
		for(it = queue.begin(); it!=queue.end(); it++){
				cout<<it->id<<"\t"<<it->priority<<endl;
		}
	}

	bool empty(){
		return queue.empty();
	}

	void minHeapify( int i){
		int l = 2*i+1;
		int r = 2*(i+1);
		int smallest;
		if(l<queue.size() && queue[l]< queue[i])
			smallest = l;
		else
			smallest = i;
		if(r < queue.size() && queue[r]<queue[smallest])
			smallest = r;
		if(smallest != i ){
			swap(smallest,i);
			minHeapify(smallest);
		}
	}
};

class Graph{
	int count,t,**adj;
	vertex *v;
	priority_queue q;

public:
	Graph(int n){
		v = new vertex[n];
		adj = new int*[n]; 
		count = n;
		int data;
		for(int i=0; i<n; i++){
			cout<<"Enter the data in "<<i+1<<" Vertex : ";
			cin>>v[i].data;
			v[i].id = i;
			adj[i] = new int[n];
		}
	}

	void generateGraph(int directed){
		for(int i = 0; i <count; i++){
			for(int j=0;j<count;j++){
				adj[i][j]=0;
			}
		}
		int choice,x,y,w;
		cout<<"Enter 0 for Finish!.....Press any key to continue: ";
		cin>>choice;
		while(choice){
			cout<<"Enter X Y : ";
			cin>>x>>y;
			cout<<"Enter Weight : ";
			cin>>w;
			adj[x-1][y-1] = w;
			if(!directed)
				adj[y-1][x-1] = w;
			cout<<"Enter 0 for Finish!.....Press any key to continue: ";
			cin>>choice;
		}
	}

	void printGraph(){
		for(int i = 0; i <count; i++){
			cout<<i+1<<" : ";
			for(int j=0;j<count;j++){
				cout<<adj[i][j]<<"\t";
			}
			cout<<endl;
		}
	}

	void printVertex(){
		for(int i=0; i<count; i++){
			cout<<v[i].id<<"\t"<<v[i].priority<<"\t"<<v[i].parent<<"\n";
		}
	}

	void mst_prim(int id){
		for(int i=0; i<count; i++){
			v[i].priority =INT_MAX;
			v[i].parent = -1;
		}
		v[id].priority = 0;
		for(int i=0; i<count; i++){
			q.insert(v[i]);
		}

		cout<<endl;
		while(!q.empty()){
			vertex u = q.pop();
			cout<<"Popped Element : "<<u.id+1<<endl;
			for(int i = 0; i<count; i++){
				if(adj[u.id][i]){					
					if(q.contains(i) && adj[u.id][i]<v[i].priority){
						v[i].parent = u.id;
						v[i].priority = adj[u.id][i];
						q.changePriority(i,adj[u.id][i]);						
					}
				}
			}
			q.print();
			cout<<endl;
		}
		printVertex();
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
	cout<<"Enter ID : ";
	cin>>choice;
	cout<<"\nPrint MST Queue for "<<choice<<"\n";
	g.mst_prim(choice-1);
	cout<<endl;
	return 0;
}