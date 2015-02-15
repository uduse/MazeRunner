#include "stdafx.h"
#include "Maze.h"

int nextOdd( int x )
{
	return x % 2 == 0 ? x + 1 : x;
}

Block::Block():solid( true ), isNode( false ), isEdge( false ), visited( false )
{
}

Block::~Block()
{
}

Maze::Maze()
{
}

Maze::Maze( int rowIn, int colIn ):row( nextOdd( rowIn ) ), col( nextOdd( colIn ) ), numNodes( 0 ), numEdges( 0 )
{
	makeBlocks();
	generate();

}

Maze::~Maze()
{
}

void Maze::generate()
{
	bool getNode = false;
	int startRow = 0;
	int startCol = 0;

	while ( !getNode )
	{
		int randRow = rand() % row;
		int randCol = rand() % col;
		if ( map[randRow][randCol].isNode )
		{
			startRow = randRow;
			startCol = randCol;
			getNode = true;
		}
	}

	todo.push_back( &map[startRow][startCol] );
	//todo.push_back( &map[row-2][col-2] );

	int visitedCount = 0;
	while ( visitedCount < numNodes && !todo.empty() )
	{
		int randIndex = rand() % todo.size();
		if ( rand() % 2 == 0 )
		{
			randIndex = todo.size() - 1;
		}
		bool newVisit = visitAdj( todo[randIndex] );
		if ( newVisit )
		{
			visitedCount++;
		}
		else
		{
			swap( todo[randIndex], todo[todo.size() - 1] );
			todo.pop_back();
		}
	}

	//for ( int visitedCount = 0; visitedCount < numNodes; visitedCount++ )
	//{
	//}
}

bool Maze::visitAdj( Block* source )
{
	bool upBlocked = false;
	bool downBlocked = false;
	bool leftBlocked = false;
	bool rightBlocked = false;

	int upRow = source->row - 2;
	int downRow = source->row + 2;
	int leftRow = source->row;
	int rightRow = source->row;

	int upCol = source->col;
	int downCol = source->col;
	int leftCol = source->col - 2;
	int rightCol = source->col + 2;

	int upEdgeRow = source->row - 1;
	int downEdgeRow = source->row + 1;
	int leftEdgeRow = source->row;
	int rightEdgeRow = source->row;

	int upEdgeCol = source->col;
	int downEdgeCol = source->col;
	int leftEdgeCol = source->col - 1;
	int rightEdgeCol = source->col + 1;

	while ( !upBlocked || !downBlocked || !leftBlocked || !rightBlocked )
	{
		switch ( rand() % 4 )
		{
		case 0:

			// Up
			if ( upRow > 0 && upRow < row && !map[upRow][upCol].visited )
			{
				map[upEdgeRow][upEdgeCol].visited = true;
				map[upEdgeRow][upEdgeCol].solid = false;
				map[upRow][upCol].visited = true;
				map[upRow][upCol].solid = false;
				todo.push_back( &map[upRow][upCol] );
				return true;
			}
			else
			{
				upBlocked = true;
			}

			break;
		case 1:
			// Down
			if ( downRow > 0 && downRow < row && !map[downRow][downCol].visited )
			{
				map[downEdgeRow][downEdgeCol].visited = true;
				map[downEdgeRow][downEdgeCol].solid = false;
				map[downRow][downCol].visited = true;
				map[downRow][downCol].solid = false;
				todo.push_back( &map[downRow][downCol] );
				return true;
			}
			else
			{
				downBlocked = true;
			}

			break;
		case 2:
			// Left
			if ( leftCol > 0 && leftCol < col && !map[leftRow][leftCol].visited )
			{
				map[leftEdgeRow][leftEdgeCol].visited = true;
				map[leftEdgeRow][leftEdgeCol].solid = false;
				map[leftRow][leftCol].visited = true;
				map[leftRow][leftCol].solid = false;
				todo.push_back( &map[leftRow][leftCol] );
				return true;
			}
			else
			{
				leftBlocked = true;
			}

			break;
		case 3:
			// Right
			if ( rightCol > 0 && rightCol < col && !map[rightRow][rightCol].visited )
			{
				map[rightEdgeRow][rightEdgeCol].visited = true;
				map[rightEdgeRow][rightEdgeCol].solid = false;
				map[rightRow][rightCol].visited = true;
				map[rightRow][rightCol].solid = false;
				todo.push_back( &map[rightRow][rightCol] );
				return true;
			}
			else
			{
				rightBlocked = true;
			}
			break;
		default:
			break;
		}
	}

	return false;
}

void Maze::makeBlocks()
{
	map = new Block*[row];
	for ( int i = 0; i < row; i++ )
	{
		map[i] = new Block[col];
	}

	for ( int i = 0; i < row; i++ )
	{
		for ( int j = 0; j < col; j++ )
		{
			map[i][j].row = i;
			map[i][j].col = j;
		}
	}

	// Assign Nodes
	for ( int i = 1; i < row; i += 2 )
	{
		for ( int j = 1; j < col; j += 2 )
		{
			map[i][j].isNode = true;
			map[i][j].solid = false;
			numNodes++;
		}
	}

	// Assign Edges
	for ( int i = 1; i < row; i++ )
	{
		for ( int j = 2 - i % 2; j < col; j += 2 )
		{
			map[i][j].isEdge = true;
			numEdges++;
		}
	}
}

void Maze::print()
{
	for ( int i = 0; i < row; i++ )
	{
		for ( int j = 0; j < col; j++ )
		{
			if ( map[i][j].solid == true )
			{
				cout << char( 178 );
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}

////  Graveyard  ///////////////////////////////////////
