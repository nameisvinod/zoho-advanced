#include "iostream"
#include "algorithm"
#include "stdlib.h"
#include "time.h"
#define COMPUTER 0
#define COMPUTERMOVE 'O'
#define HUMAN 1
#define HUMANMOVE 'X'
#define SIDE 4
#define false 0
#define true 1
using namespace std;
void intialize(char board[][SIDE], int moves[]){
	srand(time(NULL));
	for (int i = 0; i < SIDE; ++i)
		for (int j = 0; j < SIDE; ++j)
			board[i][j]= ' ';
	for (int i = 0; i < (SIDE*SIDE); ++i)
		moves[i] = i;
	// for (int i = 0; i < (SIDE*SIDE); ++i)

	random_shuffle(moves, moves + SIDE*SIDE);
}
int colCrossed(char board[][SIDE]){
	for (int i = 0; i < SIDE; ++i){
		int flag = true;
		for(int j=1;j<SIDE;j++){
			if(board[j][i]==' '){
				flag = false;
				break;
			} 
			if(board[j][i]!=board[j-1][i]){
				flag = false;
				break;
			}
		}
		if(flag) return true;
	}
	return false;
}
int rowCrossed(char board[][SIDE]){
	for (int i = 0; i < SIDE; ++i){
		int flag = true;
		for(int j=1;j<SIDE;j++){
			if(board[i][j]==' '){
				flag = false;
				break;
			} 
			if(board[i][j]!=board[i][j-1]){
				flag = false;
				break;
			}
		}
		if(flag) return true;
	}
	return false;
}
int diagonalCrossed(char board[][SIDE]){
	int flag = true;
	for (int i = 1; i < SIDE; ++i){
		if(board[i][i]!=board[i-1][i-1]){
			flag = false;
			break;
		}
	}
	if(flag && board[0][0]!= ' ')
		return true;
	// anti diagonal
	char ch = board[0][SIDE-1];
	if(ch==' ')
		return false;
	for(int i = 1;i<SIDE;i++){
		if(ch!=board[i][SIDE-1-i])
			return false;
	}
	return true;
}
int gameOver(char board[][SIDE]){
	return (colCrossed(board) || rowCrossed(board) || diagonalCrossed(board));
}
void showBoard(char board[][SIDE]){
	for (int i = 0; i < SIDE; ++i){
		for (int j = 0; j < SIDE; ++j)
			cout<< board[i][j] << " | ";
		cout<<endl;
	}
}
void declareWinner(int currentPlayer){
	if(!currentPlayer)
		cout<<"!!! COMPUTER WINS !!!"<<endl;
	else
		cout<<"!!! HUMAN WINS  !!!"<<endl;
}
void humanChoice(char board[][SIDE]){
	int x, y;
	while(true){
		cout<<"Enter Coordinates : "<<endl;
		cin>>x>>y;
		if(board[x][y] == ' '){
			board[x][y] = HUMANMOVE;
			break;
		}
		cout<<"Invalid Choice"<<endl;
	}
	cout<<"\n human move to ("<< x <<", "<<y <<")"<<endl;
}
void computerChoice(char board[][SIDE]){
	int x, y;
	while(true){
		int random = rand()%(SIDE * SIDE);
		x = random / SIDE;
		y = random % SIDE;
		if(board[x][y] == ' '){
			board[x][y] = COMPUTERMOVE;
			break;
		}
	}
	cout<<"\n computer move to ("<< x <<", "<<y <<")"<<endl;

}

void playGame(int currentPlayer){
	char board[SIDE][SIDE];
	int moves[SIDE*SIDE];
	intialize(board, moves);

	showBoard(board);
	int x, y, moveIndex = 0;
	while(!gameOver(board) && moveIndex!= (SIDE*SIDE)){
		if(currentPlayer==0){
			computerChoice(board);
		}	
		else{
			humanChoice(board);
		}	
		moveIndex++;
		showBoard(board);
		currentPlayer=!currentPlayer;
	}
	if(!gameOver(board)&& moveIndex==(SIDE*SIDE) )
		cout<<"DRAW MATCH"<<endl;
	else
		declareWinner(!currentPlayer);
}
int main(int argc, char const *argv[])
{
	playGame(COMPUTER);
	return 0;
}