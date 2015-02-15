// MazeRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Maze.h"

int _tmain(int argc, _TCHAR* argv[])
{

	const int row = 50;
	const int col = 50;

	Maze myMaze( row, col );
	myMaze.print();
	
	return 0;
}

