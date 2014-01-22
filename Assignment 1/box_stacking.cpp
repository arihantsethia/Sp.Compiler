#include <iostream>
#include <algorithm>

using namespace std;

class box{
public:
	int l,h,w;
	void insert(int _height,int _length, int _width){
		l=_length;w=_width;h=_height;
	}
};

bool compare (box a, box b)
{
    return (b.l)*(b.w) < (a.l)*(a.w);
}

int min (int x, int y)
{ return (x < y)? x : y; }
 
// A utility function to get maximum of two intgers
int max (int x, int y)
{ return (x > y)? x : y; }

int main(){
	int n,l,h,w;
	cin>>n;
	box *boxes = new box[3*n];
	int *stack;
	stack = new int[3*n];
	int index = 0;
	for(int i = 0; i<n;i++){
		cin>>w>>l>>h;
		boxes[index].h = h;
	    boxes[index].l = l;
	    boxes[index].w = w;
      	index++;

	    boxes[index].h = w;
	    boxes[index].l = max(h, l);
	    boxes[index].w = min(h, l);
	    index++;

	    boxes[index].h = l;
	    boxes[index].l = max(h, w);
	    boxes[index].w = min(h, w);
	    index++;
	}
	sort(boxes,boxes+3*n,compare);
	for (int i = 0; i < 3*n; i++ ){
      	stack[i] = boxes[i].h;
	}
	for(int i=1;i<3*n;i++){
		for(int j=0;j<i;j++){
			if(boxes[j].l > boxes[i].l && boxes[j].w > boxes[i].w ){
				if(stack[i]<stack[j]+boxes[i].h){
					stack[i]=stack[j]+boxes[i].h;
				}
			}
		}
	}
	int max = -1;
   for ( int i = 0; i < 3*n; i++ )
      if ( max < stack[i] )
         max = stack[i];
 
   cout<<max<<endl;
}