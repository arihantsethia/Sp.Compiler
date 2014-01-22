#include <iostream>

using namespace std;

#define N 8


void printSoln(int sol[N][N]){
	for (int i=0;i<N;i++){
		for(int j=0; j< N; j++)
			cout<<sol[i][j]<<"\t";
		cout<<endl;
	}
}

bool isvalid(int x, int y){
	if(x >= 0 && y >= 0 && x < N && y<N)
		return true;
	return false;
}


bool solveKTUtil(int x,int y, int moves, int sol[N][N],int moveX[N], int moveY[N]){
	if(moves == N*N)
		return true;
	for(int k =0 ; k<8; k++){
		int nextX = x + moveX[k];
		int nextY = y + moveY[k];
		if(isvalid(nextX,nextY) && sol[nextX][nextY]==-1){
			sol[nextX][nextY]=moves;
			if(solveKTUtil(nextX,nextY,moves+1,sol,moveX,moveY))
				return true;
			sol[nextX][nextY] = -1;
		}
	}
	return false;
}


void solveKT(){
	int sol[N][N];
	for(int i=0; i<N;i++)
		for(int j=0; j<N;j++)
			sol[i][j] = -1;
	int moveX[8]={  2, 1, -1, -2, -2, -1,  1,  2 };
	int moveY[8]={  1, 2,  2,  1, -1, -2, -2, -1 };
	sol[0][0] = 0;
	//if(
	solveKTUtil(0,0,1,sol,moveX,moveY);//)
		printSoln(sol);
	//else
	//	cout<<"Not Possible"<<endl;
}


int main(){
	solveKT();

	return 0;
}