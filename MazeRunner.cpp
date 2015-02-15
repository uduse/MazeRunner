// MazeRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Maze.h"
#include <time.h>

int _tmain( int argc, _TCHAR* argv[] )
{
	srand( time( NULL ) );
	//srand( 7 );

	const int row = 70;
	const int col = 120;

	Maze myMaze( row, col );
	myMaze.print();

	return 0;
}

