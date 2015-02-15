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

Maze::Maze( int rowIn, int colIn ):row( nextOdd( rowIn ) ), col( nextOdd( colIn ) )
{
	makeBlocks();

	//makeEdges();

}


Maze::~Maze()
{
}

void Maze::generate()
{

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
	for ( int i = 0; i < row; i += 2 )
	{
		for ( int j = 0; j < col; j += 2 )
		{
			map[i][j].isNode = true;
		}
	}

	// Assign Edges
	for ( int i = 0; i < row; i++ )
	{
		for ( int j = 1 - i % 2; j < col; j += 2 )
		{
			map[i][j].isEdge = true;
		}
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

void Maze::print()
{
	for ( int i = 0; i < row; i++ )
	{
		for ( int j = 0; j < col; j++ )
		{
			if ( map[i][j].isNode )
			{
				cout << "+";
			}
			else if ( map[i][j].isEdge )
			{
				cout << "+";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}

