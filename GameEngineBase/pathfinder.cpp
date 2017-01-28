#include "pathfinder.h"
#include <iostream>
#include <algorithm>


Node* Pathfinder::endNode;
Node* Pathfinder::nodeGrid[16][16];


Pathfinder::Pathfinder()
{
	
}



Pathfinder::~Pathfinder()
{

}
//... Whenever our player moves... this function gets called .. and new endNode is set 
void Pathfinder::setEndNode(Node* node)
{
	
	endNode = node;


}
/*...This function is called by AI enemy bots when it senses Player within its proximity. ->  (2.0 units radius )
  This function simply computes cost and heuristics of all nodes on the basis of start node (Enemy bot's position ) 
  and end Node (player's position)

  cost - 10 (normal) and 14 (diagonal)
  heuristics - magnitude of distance vector between current node to end node.
  */
void Pathfinder::searchPath(Node* start, int &endNodeId)
{
	
	Node* currentNode;
	
	if(endNode != NULL)
	{
		endNodeId = endNode->getNodeID();


		startNode = start; 
		bool validStart = false;
	
		for(int i = 0 ; i< 16; i++)
		{
			for(int j = 0 ; j< 16; j++)
			{
				if(nodeGrid[i][j]->getNodeID() == startNode->getNodeID())
				{
					////std::cout<<"Start Node found"<<std::endl;
					startNode->setCost(0.0f);
					validStart = true;
					break;	
				}
			}

			if(validStart)
				break;
	    }

		if (validStart) {

						//Add start Node to open List
						openList.push_back(startNode);

						//While OpenList is not empty
						while (openList.size() != 0) {
				
								currentNode = (Node*)getNodeWithLowestCost (openList);

								//If current node is end node then stop search
								if (currentNode->getNodeID() == Pathfinder::endNode->getNodeID()) {
										//closedList.push_back(currentNode);
										break;
								} 
								else 
								{

									std::vector<Node*>::iterator position = std::find(openList.begin(), openList.end(), currentNode);
									if (position != openList.end()) // == vector.end() means the element was not found
											openList.erase(position);

										currentNode->setHasTraversed(true);
									
										closedList.push_back(currentNode);

										//get Adjacent nodes
										std::vector<Node*> adjacentList = getAdjacentNodes (currentNode);

										//Validating Adjacent list
										for(int i= 0 ; i < adjacentList.size(); i++)
										{
											bool inOpen = false;
											bool inClose = false;
											//Is it in open list 
											for(int j=0; j< openList.size(); j++)
											{
												if(adjacentList[i]->getNodeID() == openList[j]->getNodeID())
												{
													inOpen = true;
													break;
													
												}
											
											}


											//Is it in closed list
											for(int j=0; j< closedList.size(); j++)
											{
												if(adjacentList[i]->getNodeID() == closedList[j]->getNodeID())
												{
													inClose = true;
													break;
												
												}
											
											}
										
											//Now add it to the open list
											if(!inClose && !inOpen && adjacentList[i]->getIsMovable())
											{
												Vector3D	scalerDist = endNode->getPosition() - adjacentList[i]->getPosition();
										    	float distance= scalerDist.Magnitude();

												int addedCost = 10;
												if(adjacentList[i]->getIsDiag())
												{
													addedCost = 14;
												}


												adjacentList[i]->setCost(currentNode->getCost() + addedCost);
												adjacentList[i]->setHeuristics(distance * 10);

											openList.push_back(adjacentList[i]);
											}
										
										}

									

								}
						}
				}


	}
	//std::cout<<"Search Path end"<<std::endl;
}


Node* Pathfinder::getNodeWithLowestCost(std::vector<Node*> list)
{
	GameObject* bestNode = new GameObject() ;
		float lowestTotal = 999.00f;

		//fetch lowest total cost
		for(int i=0; i< list.size(); i++)
		{
			if(list[i]->getTotalCost() < lowestTotal)
			{
			  bestNode = list[i];
			  lowestTotal = list[i]->getTotalCost();

			}
		
		}

		return (Node*)bestNode;

}


std::vector<Node*> Pathfinder::getAdjacentNodes(Node* currNode)
{
	std::vector<Node*> adjacentList;
	bool indexFound = false;
	Node* adjacentNode;
	

	//Find position of currNode in Graph
	int i = 0;
	int j = 0;

	for(i = 0 ; i< 16; i++)
	{
		for(j = 0 ; j< 16; j++)
		{
			if(nodeGrid[i][j]->getNodeID() == currNode->getNodeID())
			{
				//std::cout<<" Node found"<<std::endl;
				indexFound = true;
				break;
			
			}
		
		
		}

		if(indexFound)
			break;
	}

	if(indexFound)
	{
	//std::cout<<"here adjacentNode start"<<currNode->getNodeID()<<std::endl;
	if(i >= 0 && i < 16)
	{
					//..................Top....................................
					if(i != 15)
					{
						adjacentNode = nodeGrid[i + 1][j];  
								
								if (adjacentNode->getIsMovable()) {

									adjacentList.push_back(adjacentNode);
								}
					}

					//................Top Left .....................................
					if(i != 15 && j > 0)
					{
								adjacentNode = nodeGrid[i + 1][j - 1];  //Top Left
								adjacentNode->setIsDiag(true);
										
						
										if (adjacentNode->getIsMovable()) {

											
											adjacentList.push_back(adjacentNode);
										}
					
					}

					//..................Top Right................................................
					if(i != 15 && j != 15)
					{
							adjacentNode = nodeGrid[i + 1][j + 1];  
						    adjacentNode->setIsDiag(true);
						 
						
							if (adjacentNode->getIsMovable()) {

											
											adjacentList.push_back(adjacentNode);
							}
			
					}
		

					//........................Left .....................................
					if(j > 0)
					{
						adjacentNode =  nodeGrid[i][j - 1];  //Left
							
						
						if (adjacentNode->getIsMovable()) {

						
							
								adjacentList.push_back(adjacentNode);
							}
					
					}


					//.......................Right.............................................
					if(j < 15)
					{
					      adjacentNode =  nodeGrid[i][j + 1];  //Right
						
						
						 if (adjacentNode->getIsMovable()) {

							
									adjacentList.push_back(adjacentNode);
								}
		
					}


					//................Bottom..................................................
					if(i > 0)
					{
							adjacentNode = nodeGrid[i - 1][j];  //Bottom
							
							if (adjacentNode->getIsMovable()) {

									adjacentList.push_back(adjacentNode);
							}
					}


					//.....................Bottom Right................................
					if(i > 0 && j < 15)
					{
						adjacentNode =  nodeGrid[i - 1][j + 1];   //Bottom Right
						adjacentNode->setIsDiag(true);
						
						
								if (adjacentNode->getIsMovable()) {

							
							
									adjacentList.push_back(adjacentNode);
								}
		
					}

					//.................Bottom Left..........................................
					if(i> 0 && j > 0)
					{
					adjacentNode =  nodeGrid[i - 1][j - 1];   //Bottom left
					adjacentNode->setIsDiag(true);	
					
						
								if (adjacentNode->getIsMovable()) {

								
							
									adjacentList.push_back(adjacentNode);
								}
				
					}


	
	}
	////std::cout<<"here adjacentNode end"<<std::endl;
	}
	return adjacentList;

}


std::vector<Node*> Pathfinder::getAdjacentNodesForPath(Node* currNode)
{
	std::vector<Node*> adjacentList;
	bool indexFound = false;
	Node* adjacentNode;
	Vector3D scalerDist; 
	float distance;

	//Find position of currNode in Graph
	int i = 0;
	int j = 0;

	for(i = 0 ; i< 16; i++)
	{
		for(j = 0 ; j< 16; j++)
		{
			if(nodeGrid[i][j]->getNodeID() == currNode->getNodeID())
			{
				//std::cout<<" Node found"<<std::endl;
				indexFound = true;
				break;
			
			}
		
		
		}

		if(indexFound)
			break;
	}

	if(indexFound)
	{
	//std::cout<<"here adjacentNodePath start"<<currNode->getNodeID()<<std::endl;
	if(i >= 0 && i < 16)
	{
					//..................Top....................................
					if(i != 15)
					{
						adjacentNode = nodeGrid[i + 1][j];  
						
								if (adjacentNode->getIsMovable()) {

									adjacentList.push_back(adjacentNode);
								}
					}

					//................Top Left .....................................
					if(i != 15 && j > 0)
					{
								adjacentNode = nodeGrid[i + 1][j - 1];  //Top Left
										
						
										if (adjacentNode->getIsMovable()) {
					
											adjacentList.push_back(adjacentNode);
										}
					
					}

					//..................Top Right................................................
					if(i != 15 && j != 15)
					{
							adjacentNode =  nodeGrid[i+1][j + 1];  //Right
							if (adjacentNode->getIsMovable()) {

											
											adjacentList.push_back(adjacentNode);
							}
			
					}
		

					//........................Left .....................................
					if(j > 0)
					{
						adjacentNode =  nodeGrid[i][j - 1];  //Left
						
						if (adjacentNode->getIsMovable()) {

								
								adjacentList.push_back(adjacentNode);
							}
					
					}


					//.......................Right.............................................
					if(j < 15)
					{
					      adjacentNode =  nodeGrid[i][j + 1];  //Right
						 
						
						 if (adjacentNode->getIsMovable()) {

								
									adjacentList.push_back(adjacentNode);
								}
		
					}


					//................Bottom..................................................
					if(i > 0)
					{
							adjacentNode = nodeGrid[i - 1][j];  //Bottom
							
						
							if (adjacentNode->getIsMovable()) {

							
								adjacentList.push_back(adjacentNode);
							}
					}


					//.....................Bottom Right................................
					if(i > 0 && j < 15)
					{
						adjacentNode =  nodeGrid[i - 1][j + 1];   //Bottom Right
								
						
								if (adjacentNode->getIsMovable()) {

									
									adjacentList.push_back(adjacentNode);
								}
		
					}

					//.................Bottom Left..........................................
					if(i> 0 && j > 0)
					{
					adjacentNode =  nodeGrid[i - 1][j - 1];   //Bottom left
								
								if (adjacentNode->getIsMovable()) {

									
							
									adjacentList.push_back(adjacentNode);
								}
				
					}


	
	}
	////std::cout<<"here adjacentNodePath end"<<std::endl;
	}
	return adjacentList;

}
/*
This function is called after searchPath function 
it simply fetches a vector of nodes to traverse on .... 
*/

std::vector<GameObjectBase*> Pathfinder::getPath(int endNodeId, bool &reCalculate)
{
	if(endNode->getNodeID() != endNodeId)
	{
		reCalculate = true;
	}


	bool startPathFound = false;

	std::vector<GameObjectBase*> path ;

	Node* currentNode = Pathfinder::endNode;

	if(currentNode != NULL)
	{
		path.push_back(currentNode);

		//Check if current Node is the Goal
		if(currentNode->getNodeID() == startNode->getNodeID())
						startPathFound = true;

		//Check if same node is recurring again (Such scenario may take place when endNode during searchPath is different than now)
		int recCnt = 0;
		int nodeName = currentNode->getNodeID();

		while (!startPathFound)
		{
		//get Adjacent nodes
			std::vector<Node*> adjacentList = getAdjacentNodesForPath (currentNode);
			//std::cout << currentNode->getNodeID() << std::endl;
		//Validating Adjacent list
								int pathSize = path.size();
										for(int i= 0 ; i < adjacentList.size(); i++)
										{
										bool inPath = false;

											//Is it the startNode 
											if(adjacentList[i]->getNodeID() == startNode->getNodeID())
												startPathFound = true;

											//Is this node already in Path ?
											for(int j=0; j< path.size(); j++)
											{
												if(adjacentList[i]->getNodeID() == ((Node*)path[j])->getNodeID())
												{
													inPath = true;
													break;
													
												}
											
											}

									
											//Now add it to the path
											if(adjacentList[i]->getHasTraversed() && !inPath)
											{
												if(adjacentList[i]->getCost() <= currentNode->getCost())
												{
													bool highH = false;
													if((adjacentList[i]->getCost() == currentNode->getCost())
														&& (adjacentList[i]->getHeuristics() < currentNode->getHeuristics()))
													{
													   highH =true;
													}

													if(!highH)
													{
												    	currentNode = adjacentList[i];
													   path.push_back(adjacentList[i]);
													nodeName = currentNode->getNodeID();
													recCnt = 0;
        												 break;
													}
												}
											
											}
										
										
										}

										if(pathSize == path.size() && !startPathFound)
										{
										//all adjacent nodes were not traversed in search path so check if they are present in open node
											for(int i= 0 ; i < adjacentList.size(); i++)
										{
										
											//Is it the startNode 
											if(adjacentList[i]->getNodeID() == startNode->getNodeID())
												startPathFound = true;

											bool inOpen = false;
											bool inPath = false;
												
											//Is this node already in Path ?
											for(int j=0; j< path.size(); j++)
											{
												if(adjacentList[i]->getNodeID() == ((Node*)path[j])->getNodeID())
												{
													inPath = true;
													break;
													
												}
											
											}



											//Is it in open list 
											for(int j=0; j< openList.size(); j++)
											{
												if(adjacentList[i]->getNodeID() == openList[j]->getNodeID())
												{
													inOpen = true;
													break;
													
												}
											
											}

									
											//Now add it to the path
											if(inOpen && !inPath)
											{
												if(adjacentList[i]->getCost() <= currentNode->getCost())
												{
													bool highH = false;
													if((adjacentList[i]->getCost() == currentNode->getCost())
														&& (adjacentList[i]->getHeuristics() < currentNode->getHeuristics()))
													{
													   highH =true;
													}

													if(!highH)
													{
												    	currentNode = adjacentList[i];
													   path.push_back(adjacentList[i]);
													   nodeName = currentNode->getNodeID();
													recCnt = 0;
        												 break;
													}
												}
											
											}
										
										
										}
										


										
										}

										if(nodeName == currentNode->getNodeID())
										{
											recCnt++;
										}

										if(recCnt > 3)
										{
											reCalculate = true;
											break;
										}
	
	
	
	}

	
	}

	//Reverse it 
	std::reverse(path.begin(), path.end());
	return path;
	
}