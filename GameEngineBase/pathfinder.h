#ifndef _PATHFINDER_H
#define _PATHFINDER_H

#include "node.h"
#include <vector>



/*
Endpoint will be set whenever player moves and is devoid of any instance...

to get ,first create object
1. call searchPath with start node as parameter 
2. get path by calling getPath


*/

class Pathfinder
{
public:
	Pathfinder();
	void searchPath(Node* startNode,int &endNodeId);

	static void setEndNode(Node* node);

	Node* getNodeWithLowestCost(std::vector<Node*> list);
	std::vector<Node*> getAdjacentNodes(Node* currNode);
	std::vector<Node*> getAdjacentNodesForPath(Node* currNode);
	std::vector<GameObjectBase*> getPath(int endNodeId, bool &reCalculate);



	~Pathfinder();
  
	 static Node* nodeGrid[16][16];


private:
	//Start Node 
	//End Node
	//vector <map>
	//current Node
	Node* startNode;
	static Node* endNode;
   

	std::vector<Node*> openList;
	std::vector<Node*> closedList;




};


#endif