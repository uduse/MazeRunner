#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>

using namespace std;

class Block
{
public:
	Block();
	~Block();
	int row;
	int col;
	bool solid;

	bool isNode;
	bool isEdge;
	bool visited;
	vector<Block*> adjacent;
};

class Maze
{
public:
	Maze();
	Maze( int row, int col );


	void print();
	
	~Maze();

private:
	int row;
	int col;

	Block** map;

	void makeBlocks();
	void makeEdges();
	void generate();
	void connectAdj( Block* source );
};

