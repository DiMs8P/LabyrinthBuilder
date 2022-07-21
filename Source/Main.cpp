#include <vector>
#include <iostream>
#include <stack>
#include <time.h> 

using namespace std;

enum CellsTYpe
{
	CELL, WALL, VISITED
};

typedef struct Cell { 
	int X;
	int Y;
} Cell;

void getNeighbours(int Height, int Width, vector<vector<int>>& Maze, Cell startPoint, vector<Cell>& Neighbors) {
	Cell Temp;

	if (startPoint.X + 2 < Width && Maze[startPoint.X + 2][startPoint.Y] != VISITED) {
		Temp = { startPoint.X + 2 , startPoint.Y };
		Neighbors.push_back(Temp);
	}

	if (startPoint.X - 2 >= 0 && Maze[startPoint.X - 2][startPoint.Y] != VISITED) {
		Temp = { startPoint.X - 2 , startPoint.Y };
		Neighbors.push_back(Temp);
	}
	if (startPoint.Y + 2 < Height && Maze[startPoint.X][startPoint.Y + 2] != VISITED) {
		Temp = { startPoint.X , startPoint.Y + 2 };
		Neighbors.push_back(Temp);
	}
	if (startPoint.Y - 2 >= 0 && Maze[startPoint.X][startPoint.Y - 2] != VISITED) {
		Temp = { startPoint.X , startPoint.Y - 2 };
		Neighbors.push_back(Temp);
	}
}

void MakeHole(int X, int Y, vector<vector<int>>& Maze) {
	Maze[X][Y] = CELL;
}


int main() {
	srand(time(NULL));
	const int Height = 41, Width = 58;
	vector<vector<int>> Maze = vector<vector<int>>(Height, vector<int>(Width)); 

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			if ((i % 2 != 0 && j % 2 != 0) && 
				(i < Height - 1 && j < Width - 1))   
				Maze[i][j] = CELL;
			else Maze[i][j] = WALL;           
		}
	}

	Cell StartCell = { 1, 1 };
	Cell CurrentCell = StartCell;
	Cell neighbourCell;
	vector<Cell> Neighbours;
	stack<Cell> Visited;

	Maze[CurrentCell.X][CurrentCell.Y] = VISITED;
	do {
		getNeighbours(Width, Height, Maze, CurrentCell, Neighbours);

		if (Neighbours.size() == 0) {
			CurrentCell = Visited.top();
			Visited.pop();

		}
		else {
			Visited.push(CurrentCell);
			CurrentCell = Neighbours[(rand() % Neighbours.size())];
			Neighbours.clear();
			Maze[CurrentCell.X][CurrentCell.Y] = VISITED;
			MakeHole((Visited.top().X + CurrentCell.X) / 2, (Visited.top().Y + CurrentCell.Y) / 2, Maze);
		}
		
	} while (Visited.size());


	//Вывод
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			if (Maze[i][j] == VISITED)
				Maze[i][j] = CELL;
			cout << Maze[i][j] << " ";
		}
		cout << endl;
	}

	getchar();
	return 0;
}
