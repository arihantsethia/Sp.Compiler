#include <iostream>
#include <list>
#include <vector>
#include <climits>

using namespace std;

class node{
public:
	int weight,data;

	node(int x,int y){
		data = x;
		weight = y;
	}
	node(){}

};

class vertex{
public:
	int data,id,parent,priority;
	vertex(int x,int y){
		id = x;
		data = y;
	}

	vertex(){

	}

	bool operator < (vertex& v2){
		return priority < v2.priority;
	}
};

class priority_queue{
	vector<vertex> queue;

	void swap(int i, int j){
		vertex temp = queue[i];
		queue[i] = queue[j];
		queue[j] =  temp;
	}

	void decrease_key(int i){
		while(i>=0 && queue[i]< queue[(i-1)/2]){
			swap(i,(i-1)/2);
			i = (i-1)/2;
		}
	}
public:
	void insert(vertex v){
		queue.push_back(v);
		decrease_key(queue.size()-1);
	}

	void changePriority(int id, int new_key){
		for(int i=0; i <queue.size(); i++){
			if(queue[i].id == id){
				if(queue[i].priority > new_key) {
					queue[i].priority = new_key;
					decrease_key(i);
				}
				break;
			}
		}
		//print();
	}

	vertex pop(){
		vertex temp = queue[0];
		swap(queue.size()-1,0);
		queue.pop_back();
		minHeapify(0);
		return temp; 
	}

	void minHeapify(int i){
		int l = 2*i+1;
		int r = 2*(i+1);
		int min;
		if(l < queue.size() && queue[l]<queue[i])
			min = l;
		else
			min = i;
		if( r < queue.size() && queue[r] < queue[i])
			min = r;
		if( min != i){
			swap(min,i);
			minHeapify(min);
		}
	}

	bool empty(){
		return queue.empty();
	}

	void print(){
		vector<vertex>::iterator it;
		for(it = queue.begin(); it!=queue.end(); it++){
				cout<<it->id<<"\t"<<it->priority<<endl;
		}
	}
};

class Graph{
	int n;
	vertex *v;
	list<node> *adj;
	priority_queue queue;

	void addToList(int directed, int i, int j, int w){
		node newnode(j,w);
		adj[i].push_front(newnode);
	}

public: 
	Graph(int x){
		n = x;
		v = new vertex[n];
		adj = new list<node>[n];
	}

	void generateGraph(int directed){
		int choice,x,y,weight;
		cout<<"Enter 0 for Finish!.....Press any key to continue: ";
		cin>>choice;
		while(choice){
			cout<<"Enter X Y : ";
			cin>>x>>y;
			cout<<"Enter Weight : ";
			cin>>weight;
			addToList(directed, x-1, y-1,weight);
			cout<<"Enter 0 for Finish!.....Press any key to continue: ";
			cin>>choice;
		}
	}

	void printGraph(){
		list<node>:: iterator it;
		for(int i = 0; i<n; i++){
			for(it=adj[i].begin(); it!=adj[i].end(); it++ ){
				cout<<it->data<<"\t";
			}
			cout<<endl;
		}
	}

	void dijkstra(int k){
		for(int i = 0; i<n; i++ ){
			v[i].id = i;
			v[i].priority = INT_MAX;
			v[i].parent = -1; 
		}
		v[k].priority = 0;
		for(int i = 0; i<n; i++ ){
			queue.insert(v[i]); 
		}
		vector<vertex> s;
		while(!queue.empty()){
			vertex u = queue.pop();
			s.push_back(u);
			list<node>::iterator it;
			for(it = adj[u.id].begin(); it!= adj[u.id].end(); it++ ){
				if( v[it->data].priority > u.priority +(*it).weight ){
					v[it->data].parent = u.id; 
					v[it->data].priority = u.priority +(*it).weight ;
					queue.changePriority(it->data, v[it->data].priority);
				}
			}	
		}

		for(int i = 0; i<s.size();i++)
			cout<<s[i].id<<"\t"<<s[i].priority<<endl;
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
	cout<<"\nPrint Dijastra  for "<<choice<<"\n";
	g.dijkstra(choice-1);
	cout<<endl;
	return 0;
}