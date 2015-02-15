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

	//makeEdges();
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

	int visitedCount = 0;
	while ( visitedCount < numEdges )
	{
		int randIndex = rand() % todo.size();
		bool newVisit = visitAdj( todo[randIndex] );
		if ( newVisit )
		{
			visitedCount++;
		}
		else
		{
			if ( todo.size() > 1 )
			{
				swap( todo[randIndex], todo[todo.size() - 1] );
				todo.pop_back();
			}
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
			if ( upRow > 0 && upRow < row )
			{
				if ( !map[upRow][upCol].visited )
				{
					map[upEdgeRow][upEdgeCol].visited = true;
					map[upEdgeRow][upEdgeCol].solid = false;
					map[upRow][upCol].visited = true;
					map[upRow][upCol].solid = true;
					todo.push_back( &map[upRow][upCol] );
					return true;
				}
				else
				{
					upBlocked = true;
				}
			}

			break;
		case 1:
			// Down
			if ( downRow > 0 && downRow < row )
			{
				if ( !map[downRow][downCol].visited )
				{
					map[downEdgeRow][downEdgeCol].visited = true;
					map[downEdgeRow][downEdgeCol].solid = false;
					map[downRow][downCol].visited = true;
					map[downRow][downCol].solid = true;
					todo.push_back( &map[downRow][downCol] );
					return true;
				}
				else
				{
					downBlocked = true;
				}
			}

			break;
		case 2:
			// Left
			if ( leftRow > 0 && leftRow < row )
			{
				if ( !map[leftRow][leftCol].visited )
				{
					map[leftEdgeRow][leftEdgeCol].visited = true;
					map[leftEdgeRow][leftEdgeCol].solid = false;
					map[leftRow][leftCol].visited = true;
					map[leftRow][leftCol].solid = true;
					todo.push_back( &map[leftRow][leftCol] );
					return true;
				}
				else
				{
					leftBlocked = true;
				}
			}

			break;
		case 3:
			// Right
			if ( rightRow > 0 && rightRow < row )
			{
				if ( !map[rightRow][rightCol].visited )
				{
					map[rightEdgeRow][rightEdgeCol].visited = true;
					map[rightEdgeRow][rightEdgeCol].solid = false;
					map[rightRow][rightCol].visited = true;
					map[rightRow][rightCol].solid = true;
					todo.push_back( &map[rightRow][rightCol] );
					return true;
				}
				else
				{
					rightBlocked = true;
				}
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
			//if ( map[i][j].isNode )
			//{
			//	cout << "+";
			//}
			//else if ( map[i][j].isEdge )
			//{
			//	cout << "+";
			//}
			//else
			//{
			//	cout << " ";
			//}
		}
		cout << endl;
	}
}

////  Graveyard  ///////////////////////////////////////

void Maze::connectAdj( Block* source )
{
	// Up
	if ( source->row > 0 && source->row < row )
	{
		source->adjacent.push_back( &map[source->row - 1][source->col] );
	}

	// Down
	if ( source->row >= 0 && source->row < row - 1 )
	{
		source->adjacent.push_back( &map[source->row + 1][source->col] );
	}

	// Left
	if ( source->col > 0 && source->col < col )
	{
		source->adjacent.push_back( &map[source->row][source->col - 1] );
	}

	// Right
	if ( source->col >= 0 && source->col < col - 1 )
	{
		source->adjacent.push_back( &map[source->row][source->col + 1] );
	}
}

void Maze::makeEdges()
{
	for ( int i = 0; i < row; i++ )
	{
		for ( int j = 0; j < col; j++ )
		{
			connectAdj( &map[i][j] );
		}
	}
}