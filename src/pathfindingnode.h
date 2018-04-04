#ifndef PATHFINDING_NODE_H
#define PATHFINDING_NODE_H

#include <vector>

struct Node{
	Node(){}
	Node(int x, int y) : x(x), y(y){}
	int x, y; // position
	// calculating the value
	float globalValue=0;
	float localValue=0;

	bool operator==(Node& other){
		return other.x == x && other.y==y;
	}

	bool visited=false;
	bool block=false;
	std::vector<Node*> neighbors;
	Node* parent=nullptr;
};

#endif
