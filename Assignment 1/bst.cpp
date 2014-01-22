#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class node{
public:
	int data;
	node *left,*right,*parent;
	node(int x){
		data=x;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	node(){}
};


class BinaryTree{
	node *root;

	void transplant(node *u, node *v){
		if(u->parent == NULL){
			root = v;
		} else if( u = u->parent->left){
			u->parent->left = v;
		}else
			u->parent->right = v;
		if(v!=NULL)
			v->parent = u->parent;
	}
public:
	BinaryTree(){
		root = NULL;
	}
	void addNode(int x){
		if(root == NULL){
			root = new node(x);
		} else {
			node *temp = root;
			node *y;
			while(temp != NULL){
				y=temp;
				if(temp->data > x){
					temp = temp->left;
				} else
					temp = temp->right;
			}
			if(y->data > x){
				y->left = new node(x);
				y->left->parent = y;
			} else {
				y->right = new node(x);
				y->right->parent = y;
			}	
		}
	}

	node* getRoot(){
		return root; 
	}

	node* getNode(int x){
		node *temp = root;
		while(temp != NULL){
			if(temp->data == x){
				return temp;
			} else if(temp->data > x){
				temp = temp->left;
			} else
				temp = temp->right;
		}
		return temp;
	}

	node* minimum(node *a){
		node *temp = new node();
		if(a == NULL)	
			return temp;
		while(a->left!=NULL){
			temp = a;
			a= a->left;
		}
		return temp;
	}

	node* maximum(node *a){
		node *temp = new node();
		if(a == NULL)	
			return temp;
		while(a->right!=NULL){
			temp = a;
			a= a->right;
		}
		return temp;
	}

	node* succesor(node *x){
		if(x->right != NULL){
			return minimum(x->right);
		}
		node *y =x->parent;
		while(y != NULL && y->right==x){
			x =y;
			y = y->parent;
		}
		return y;
	}

	node* predessor(node *x){
		if(x->left != NULL)
			return maximum(x->left);
		node *y = x->parent;
		while(y!=NULL && y->left == x){
			x = y;
			y = y->parent;
		}
		return y;
	}

	void deleteNode(int x){
		node *p = getNode(x);
		if(p == NULL)
			return;
		else if(p->left == NULL)
			transplant(p,p->right);
		else if(p->right == NULL)
			transplant(p,p->left);
		else{
			node *y = minimum(p->right);
			if(y->parent != p){
				transplant(y,y->right);
				y->right = p->right;
				y->right->parent = y;
			}
			transplant(p,y);
			y->left = p->left;
			y->left->parent = y;
		}
	}

	void inorderTraversal(node *p){
		if(p){
			inorderTraversal(p->left);
			cout<<p->data<<"\t";
			inorderTraversal(p->right);
		}
	}

	void printZigZag(){
		stack<node*> curr,next;
		bool leftToRight = true;
		curr.push(root);
		while(!curr.empty()){
			node *temp = curr.top();
			curr.pop();
			if(temp){
				cout<<temp->data<<" ";
				if(leftToRight){
					next.push(temp->left);
					next.push(temp->right);
				}
				else {
					next.push(temp->right);
					next.push(temp->left);
				}
			}
			if(curr.empty()){
				cout<<endl;
				leftToRight = !leftToRight;
				swap(curr,next);
			}
		}

	}
};


int main(){
	int choice,temp;
	BinaryTree sk;
	cout<<"Enter 1 for inserting into Tree | 2 for printing tree| 0 for exit"<<endl;
	cin>>choice;
	while(choice){
		if(choice==1){
			cout<<"Enter Element : ";
			cin>>temp;
			sk.addNode(temp);
		}
		else if(choice==2){
			sk.printZigZag();
		}
		else if(choice==3){
			cout<<"Enter Element : ";
			cin>>temp;
			sk.deleteNode(temp);
		}
		else if(choice==4){
			sk.inorderTraversal(sk.getRoot());
		}
		cout<<"Enter 1 for inserting into List | 2 for printing tree | 3 for Delete| 0 for exit"<<endl;
		cin>>choice;
	}
	return 0;
}