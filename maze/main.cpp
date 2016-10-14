#include "iostream"
#include "queue"
#include "vector"
#include "math.h"
#include "time.h"
#define path 1
#define hole 2
#define mons 3
#define trig 4 
#define R 5
#define C 5
using namespace std;
class Point{
	protected:
		int x, y;
		int value;
	public:
		Point(){};
		Point(int x, int y, int value=0):x(x), y(y), value(value){};
		int getX(){
			return x;
		}
		int getY(){
			return y;
		}
		void setValue(int v){this->value = v;}
		int getValue(){return value;}
		bool equal(Point p){
			return (p.x==x) && (p.y==y);
		}
};
class External{
	Point p;
	public:
		External(){
			p = Point(0,0);
		};
		// External(Point point):p(point){};
		Point getPosition(){
			return p;
		}
		void setPosition(Point p){
			this->p = p;
		}
		int getX(){
			return this->p.getX();
		}
		int getY(){
			return this->p.getY();
		}
};
class Maze
{
	int maze[R][C];
	External monster;
	External trigger;
	public:
		Maze(){};
		void showMaze(){
			cout<<"MAZE STATE"<<endl;
			for (int i = 0; i < R; ++i){
				for (int j = 0; j < C; ++j)
					cout<<maze[i][j]<<" | ";
				cout<<endl;
			}
			cout<<endl;
		}
		void initialize(){
			for (int i = 0; i < R; ++i)
				for (int j = 0; j < C; ++j)
					maze[i][j] = 0;
		}
		void initializeHoles(int n){
			srand(time(NULL));
			for (int i = 0; i < n; ++i){
				int index = rand()%(R*C);
				int indexX = index / R;
				int indexY = index % R;
				maze[indexX][indexY] = hole; 
			}
		}
		void initializeMonster(){
			bool done = false;
			// cout<<monster.getX() <<" "<< monster.getY()<<endl;
			if(maze[monster.getX()][monster.getY()]==mons)
				maze[monster.getX()][monster.getY()] = 0;
			while(!done){
				srand(time(NULL));
				int index = rand()%(R*C);
				// cout<<"index "<<index<<endl;
				int indexX = index / R;
				int indexY = index % R;
				if(maze[indexX][indexY]!=1){
					maze[indexX][indexY] = mons;
					monster.setPosition(Point(indexX, indexY));
					// cout<<"inside "<<monster.getX() <<" "<< monster.getY()<<endl;
					done = true;
				}	
			}
		}
		void initializeTrigger(){
			bool done = false;
			while(!done){
				srand(time(NULL));
				int index = rand()%(R*C);
				int indexX = index / R;
				int indexY = index % R;
				if(maze[indexX][indexY]!=mons){
					maze[indexX][indexY] = trig;
					trigger.setPosition(Point(indexX, indexY));
					done = true;
				}	
			}
		}
		void killMonster(){
			maze[monster.getX()][monster.getY()] = 0;
		}
		bool isSafe(Point p){
			int x = p.getX();
			int y = p.getY();
			if(x>=0 && x<R && y>=0 && y<C && (maze[x][y]==0 || maze[x][y]==4))
				return true;
			return false;
		}
		bool reached(Point p, Point dest){
			// return (p.getX()==dest.getX()) &&  (p.getY()==dest.getY());
			return p.equal(dest);
		}
		bool solveMazeHelper(Point p, Point dest){
			int x = p.getX();
			int y = p.getY();
			// initializeMonster();
			if(reached(p, monster.getPosition())){
				cout<<"Monster attack!!!!"<<endl;
				return false;
			}
			if(reached(p, trigger.getPosition())){
				killMonster();
				cout<<"Monster killed!!!!"<<endl;
			}
			if(reached(p, dest)){
				maze[x][y] = path;
				return true;
			}
			if(isSafe(p)){
				maze[x][y] = path;
				showMaze();
				if(solveMazeHelper(Point(x+1, y), dest))
					return true;
				if(solveMazeHelper(Point(x, y+1), dest))
					return true;
				maze[x][y]=0;
				return false;
			}
		}
		void solveMaze(Point src, Point dest){
			cout<<"Source :  ["<< src.getX()<< ", "<<src.getY()<<"]"<<endl;
			cout<<"Destination :  ["<< dest.getX()<< ", "<<dest.getY()<<"]"<<endl;
			if(solveMazeHelper(src, dest)== false){
				cout<<"No path "<<endl;
				return;
			}
			// showMaze();
		}
		
};
void playMaze(){
	Maze maze;
	maze.initialize();
	maze.initializeHoles(4);
	maze.initializeMonster();
	maze.initializeTrigger();
	maze.showMaze();
	maze.solveMaze(Point(1,1), Point(3,3));
	maze.showMaze();
}
int main(int argc, char const *argv[])
{
	playMaze();
	return 0;
}