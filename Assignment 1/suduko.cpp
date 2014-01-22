#include <iostream>
#include <cstdio>
#define N 9
using namespace std;

int suduku[9][9];

bool notInRow(int row, int num){
	for(int i=0; i< N; i++){
		if(suduku[row][i] == num)
			return false;
	}
	return true;
}

bool notInColumn(int column, int num){
	for(int i=0; i< N; i++){
		if(suduku[i][column] == num)
			return false;
	}
	return true;
}

bool notInBox(int x, int y, int num){
	for(int i=0 ; i<3; i++){
		for(int j=0; j < 3;j++){
			if(suduku[x+i][y+i]==num)
				return false;
		}
	}
	return true;
}

bool isSafe(int x, int y, int num){
	return (notInRow(x,num) && notInColumn(y,num) && notInBox(x-x%3, y-y%3,num));
}

bool emptyCell(int& row, int& column){
	for(row=0; row<N; row++){
		for(column=0; column<N; column++){
			if(suduku[row][column] == 0){
				return true;
			}
		}
	}
	return false;
}

bool sudukuSolver(){
	int row,column;
	if(!emptyCell(row, column))
		return true;
	for(int num=1;num<=9;num++){
		if(isSafe(row,column,num)){
			suduku[row][column]=num;
			if(sudukuSolver())
				return true;
			suduku[row][column] = 0;
		}
	}
	return false;
}

void printGrid()
{
    for (int row = 0; row < N; row++)
    {
       for (int col = 0; col < N; col++)
             printf("%2d", suduku[row][col]);
        printf("\n");
    }
}
 
/* Driver Program to test above functions */
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++) {
        for(int j=0;j<9;j++) {
            for(int k=0;k<9;k++) {
                suduku[j][k] = 0;
                cin>>suduku[j][k];
            }
        }
        sudukuSolver();printGrid();
    }
    return 0;
}
