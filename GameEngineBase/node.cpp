#include "node.h"


	int Node::id = 0;

Node::Node()
{
	cost = 999.0f;
	 heuristic = 0.0f;
	totalCost = 999.0f;
	node_id = Node::id;
	isMovable = true;
	hasTraversed = false;
	isDiag= false;
	Node::id++;
}
Node::~Node()
{

}

int Node::getNodeID()
{

	return node_id;
}

void Node::setCost(float value)
{
	cost = value;
	setTotalCost();
}
void Node::setHeuristics(float value)
{
	heuristic = value;
	setTotalCost();
}
void Node::setTotalCost()
{
	totalCost = cost + heuristic;

}

float Node::getCost()
{
	return cost;

}
float Node::getHeuristics()
{

	return heuristic;
}
float Node::getTotalCost()
{
	return totalCost;


}


void  Node::setMovable(bool value)
{

	isMovable = value;
}

bool  Node::getIsMovable()
{

	return isMovable;
}


void  Node::setHasTraversed(bool value)
{

	hasTraversed = value;
}

bool  Node::getHasTraversed()
{

	return hasTraversed;
}


void Node::setIsDiag(bool value)
{

	isDiag = value;
}

bool Node::getIsDiag()
{

	return isDiag;
}