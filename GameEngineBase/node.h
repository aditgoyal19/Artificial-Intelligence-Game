#ifndef _NODE_
#define _NODE_

#include "gameObject.h"

class Node : public GameObject
{
public:
Node();
~Node();


void setCost(float value);
void setHeuristics(float value);
void setTotalCost();
void setMovable(bool value);
void setHasTraversed(bool value);
void setIsDiag(bool value);


float getCost();
float getHeuristics();
float getTotalCost();
bool getIsMovable();
bool getHasTraversed();
int getNodeID();
bool getIsDiag();


	static int id ;
private:
	float cost;
	float heuristic;
	float totalCost;
	bool isMovable;
	bool hasTraversed;
	bool isDiag;
	int node_id;


};


#endif