#include "collisionTest.h"

#include "sphere.h"
#include "node.h"

#include <iostream>

Collision::Collision()
{

}

Collision::~Collision()
{

}




void  Collision::SphereToEnvCollision(GameObject* sphere , GameObject* envObj ,std::vector<Physics::Point> &listOfClosestPt)
{
Physics::Point playerPos;
playerPos = sphere->getPosition();

 float distance = 99.0f; 
	float radius;

if(sphere->getName() == "Sphere"){
   Sphere* s = (Sphere*)sphere;
   radius = s->getRadius();
}
else if(sphere->getName() == "Enemy")
{
	radius = 0.01f;
}
else
{
	radius = 0.15f;

}


std::vector<PLYVERTEX> m_verticies = envObj->getVerticiesForSimulation();
std::vector<PLYELEMENT> m_elements = envObj->getElements();
std::vector<Physics::Point> closestPointsofObj ;
Physics::Point closestPoint ;
	
for(int i=0; i< m_elements.size(); i++ )
	{

		Physics::Point a(m_verticies[m_elements[i].vertex_1].pos.x,
			             m_verticies[m_elements[i].vertex_1].pos.y,
						 m_verticies[m_elements[i].vertex_1].pos.z) ;

		Physics::Point b(m_verticies[m_elements[i].vertex_2].pos.x,
			             m_verticies[m_elements[i].vertex_2].pos.y,
						 m_verticies[m_elements[i].vertex_2].pos.z) ;

		Physics::Point c(m_verticies[m_elements[i].vertex_3].pos.x,
			             m_verticies[m_elements[i].vertex_3].pos.y,
						 m_verticies[m_elements[i].vertex_3].pos.z) ;

		
		bool bIsInsideFace = false;
	

	   Physics::Point newclosestPoint = Physics::ClosestPtPointTriangle(playerPos, a, b, c, bIsInsideFace );
	   float newDist = Physics::Distance(newclosestPoint,playerPos);
	   
	   if(newDist < distance)
		{
			closestPoint = newclosestPoint;
		    distance = newDist;

		
			if(distance <= radius)
			{
				closestPointsofObj.push_back(newclosestPoint);
			}
		  
	  
	
		}
			 
	}

			//Calculate actual closest dist of that object 
	if( closestPointsofObj.size() > 0)
	{
		Physics::Point sumObj(0.0f,0.0f,0.0f);
		for(int i = 0 ; i < closestPointsofObj.size(); i++)
		{
			sumObj += closestPointsofObj[i];
		}
		
		sumObj /= closestPointsofObj.size();
	
		listOfClosestPt.push_back(sumObj);
	}

}
void Collision::SphereToSphereCollision(GameObject* sphere1 , GameObject* sphere2,  std::vector<Physics::Point> &listOfClosestPt)
{
	// Proximity test for sphere to sphere
	Physics::Sphere a ;
	a.c = sphere1->getPosition();
	a.vel = sphere1->getVelocity();
	a.r = ((Sphere*)sphere1)->getRadius() ;

	Physics::Sphere b ; 
	b.c = sphere2->getPosition();
	b.r = ((Sphere*)sphere2)->getRadius();
	b.vel = sphere2->getVelocity(); 
	
	Physics::Point closestPt;
	Vector3D newVel ; 
					
	if(Physics::ClosestPtSphereSphere( a,b, closestPt))
	{
		listOfClosestPt.push_back(closestPt);

		//Calculate change in velocity
		Vector3D newVelocityA ; 
	    Vector3D newVelocityB ; 
		newVelocityA.x = ((a.vel.x * (a.r - b.r)) + (2 * b.r * b.vel.x)) / (a.r + b.r);
		newVelocityA.y = ((a.vel.y * (a.r - b.r)) + (2 * b.r *b.vel.y)) / (a.r + b.r);
		newVelocityA.z = ((a.vel.z * (a.r - b.r)) + (2 * b.r * b.vel.z)) / (a.r + b.r);
					  
		sphere1->setVelocity(newVelocityA);

		newVelocityB.x = ((b.vel.x * (a.r - b.r)) + (2 * b.r * a.vel.x )) / (a.r + b.r);
		newVelocityB.y = ((b.vel.y  * (a.r - b.r)) + (2 * b.r *a.vel.y)) / (a.r + b.r);
		newVelocityB.z = ((b.vel.z  * (a.r - b.r)) + (2 * b.r * a.vel.z)) / (a.r + b.r);

	
		sphere2->setVelocity(newVelocityB);
	}
		
}


void Collision::NodeToEnvCollision(GameObject* node , GameObject* envObj)
{
	
Physics::Point playerPos;
playerPos = node->getPosition();

float distance = 99.0f;

std::vector<PLYVERTEX> m_verticies = envObj->getVerticiesForSimulation();
std::vector<PLYELEMENT> m_elements = envObj->getElements();
std::vector<Physics::Point> closestPointsofObj ;
Physics::Point closestPoint ;
	
for(int i=0; i< m_elements.size(); i++ )
	{

		Physics::Point a(m_verticies[m_elements[i].vertex_1].pos.x,
			             m_verticies[m_elements[i].vertex_1].pos.y,
						 m_verticies[m_elements[i].vertex_1].pos.z) ;

		Physics::Point b(m_verticies[m_elements[i].vertex_2].pos.x,
			             m_verticies[m_elements[i].vertex_2].pos.y,
						 m_verticies[m_elements[i].vertex_2].pos.z) ;

		Physics::Point c(m_verticies[m_elements[i].vertex_3].pos.x,
			             m_verticies[m_elements[i].vertex_3].pos.y,
						 m_verticies[m_elements[i].vertex_3].pos.z) ;

		
		bool bIsInsideFace = false;
	

	   Physics::Point newclosestPoint = Physics::ClosestPtPointTriangle(playerPos, a, b, c, bIsInsideFace );
	   float newDist = Physics::Distance(newclosestPoint,playerPos);
	   
	   if(newDist < distance)
		{
			closestPoint = newclosestPoint;
		    distance = newDist;

		
			if(distance <= 0.2)
			{
				((Node*)node)->setMovable(false);
				//std::cout<<((Node*)node)->getNodeID()<<std::endl;
				//node->setPosition(node->getPosition() + Vector3D(0.0f,3.0f,0.0f));
				break;
			}
		}
			 
	}


}
void Collision::NodeToSphereCollision(GameObject* node , GameObject* sphere2)
{




}


void Collision::CollisionCheckForNode(GameObject* node, std::vector< GameObjectBase* > vec_pGameObjects)
{
	Node* currNode = (Node*)node;

	for(int j =0; j < vec_pGameObjects.size(); j++)
	{
		

		if(((GameObject*)vec_pGameObjects[j])->getName() != "SPHERE")
		{
			// Proximity test for Node to other objects
			NodeToEnvCollision(currNode, (GameObject*)vec_pGameObjects[j] );
		}
		else
		{
		    // Proximity test for Node to sphere
			NodeToSphereCollision(currNode, (GameObject*)vec_pGameObjects[j] );
		}
				
							
	}



}


void Collision::CollisionCheckForSphere(std::vector< GameObjectBase* > vec_pGameObjects, int playerIndex)
{
	//check for collisions
	Sphere* sphere = (Sphere*)vec_pGameObjects[playerIndex];

	Vector3D playerPos = sphere->getPosition();
	float radius = sphere->getRadius();

	std::vector<Vector3D> closestPointsInEnv ; //It contains list of closest points of all objects
	Physics::Point closestPoint ;
	     
	float distance = 99.0f; 

	 
	for(int j =0; j < vec_pGameObjects.size(); j++)
	{
		if(j == playerIndex)
		{
			continue;
		}

		if(((GameObject*)vec_pGameObjects[j])->getName()  != "SPHERE")
		{
			// Proximity test for sphere to other objects
			SphereToEnvCollision((GameObject*)vec_pGameObjects[playerIndex], (GameObject*)vec_pGameObjects[j] , closestPointsInEnv);
		}
		else
		{
		    // Proximity test for sphere to sphere
			SphereToSphereCollision((GameObject*)vec_pGameObjects[playerIndex], (GameObject*)vec_pGameObjects[j] , closestPointsInEnv);
		}
				
							
	}

	Physics::Point sumEnv(0.0f,0.0f,0.0f);

	for(int i = 0 ; i < closestPointsInEnv.size(); i++)
	{
		sumEnv += closestPointsInEnv[i];
	}
	
	sumEnv /= closestPointsInEnv.size();

		//if distance is less than radius bind the ball
	if(closestPointsInEnv.size() > 0 )
	{
		Physics::Point dist =  playerPos -sumEnv ;
	    Vector3D::Normalize( dist.x, dist.y,dist.z);
		
		dist = dist * radius;
		

		Physics::Point distToTraverse = sumEnv + dist;
		((GameObject*)vec_pGameObjects[playerIndex])->setPosition(distToTraverse);// newPoint;
		
		
	}


}




void Collision::CollisionCheckForPlayer(std::vector< GameObjectBase* > vec_pGameObjects, int playerIndex)
{
	//check for collisions
	//Sphere* sphere = (vec_pGameObjects[playerIndex];

	Vector3D playerPos = vec_pGameObjects[playerIndex]->getPosition();
	float radius =  0.15f; //vec_pGameObjects[playerIndex]->getMaxExtent();

	std::vector<Vector3D> closestPointsInEnv ; //It contains list of closest points of all objects
	Physics::Point closestPoint ;
	     
	float distance = 99.0f; 

	 
	for(int j =0; j < vec_pGameObjects.size(); j++)
	{
		if(j == playerIndex)
		{
			continue;
		}

		if(((GameObject*)vec_pGameObjects[j])->getName()  == "Terrain")
		{
			// Proximity test for sphere to other objects
			SphereToEnvCollision((GameObject*)vec_pGameObjects[playerIndex], (GameObject*)vec_pGameObjects[j] , closestPointsInEnv);
		}
		//else
		//{
		//    // Proximity test for sphere to sphere
		//	SphereToSphereCollision((GameObject*)vec_pGameObjects[playerIndex], (GameObject*)vec_pGameObjects[j] , closestPointsInEnv);
		//}
				
							
	}

	Physics::Point sumEnv(0.0f,0.0f,0.0f);

	for(int i = 0 ; i < closestPointsInEnv.size(); i++)
	{
		sumEnv += closestPointsInEnv[i];
	}
	
	sumEnv /= closestPointsInEnv.size();

		//if distance is less than radius bind the ball
	if(closestPointsInEnv.size() > 0 )
	{
		Physics::Point dist =  playerPos -sumEnv ;
	    Vector3D::Normalize( dist.x, dist.y,dist.z);
		
		dist = dist * radius;
		

		Physics::Point distToTraverse = sumEnv + dist;
		((GameObject*)vec_pGameObjects[playerIndex])->setPosition(distToTraverse);// newPoint;
		
		
	}


}



void Collision::CollisionCheckForEnemy(std::vector< GameObjectBase* > vec_pGameObjects)
{
	//check for collisions
	//Sphere* sphere = (vec_pGameObjects[playerIndex];

	//Vector3D playerPos = vec_pGameObjects[playerIndex]->getPosition();
	float radius =  0.15f; //vec_pGameObjects[playerIndex]->getMaxExtent();

	std::vector<Vector3D> closestPointsInEnv ; //It contains list of closest points of all objects
	Physics::Point closestPoint ;
	     
	float distance = 99.0f; 

	 
	for(int j =0; j < vec_pGameObjects.size(); j++)
	{
		closestPointsInEnv.clear();

		if(((GameObject*)vec_pGameObjects[j])->getName()   == "Enemy")
		{
			radius = vec_pGameObjects[j]->getScale() / 2;

			for(int k =0; k < vec_pGameObjects.size(); k++)
			{
				if(k == j)
				{
					continue;
				}


				if(((GameObject*)vec_pGameObjects[k])->getName()   == "Enemy")
				{
			
					EnemyToEnemyCollision((GameObject*)vec_pGameObjects[k], (GameObject*)vec_pGameObjects[j] , closestPointsInEnv);
		
				}

			/*	if(((GameObject*)vec_pGameObjects[k])->getName()  == "Terrain")
				{
				// Proximity test for sphere to other objects
				SphereToEnvCollision((GameObject*)vec_pGameObjects[j], (GameObject*)vec_pGameObjects[k] , closestPointsInEnv);
				}*/
	

			}
		}

		


		Physics::Point sumEnv(0.0f,0.0f,0.0f);

	for(int i = 0 ; i < closestPointsInEnv.size(); i++)
	{
		sumEnv += closestPointsInEnv[i];
	}
	
	sumEnv /= closestPointsInEnv.size();

		//if distance is less than radius bind the ball
	if(closestPointsInEnv.size() > 0 )
	{
		Physics::Point dist =  vec_pGameObjects[j]->getPosition() -sumEnv ;
	    Vector3D::Normalize( dist.x, dist.y,dist.z);
		
		dist = dist * radius;
		

		Physics::Point distToTraverse = sumEnv + dist;
		((GameObject*)vec_pGameObjects[j])->setPosition(distToTraverse);// newPoint;
		
		
	}


	}//	if(((GameObject*)vec_pGameObjects[j])->getName()  == "Terrain")
	//	{
	//		// Proximity test for sphere to other objects
	//		SphereToEnvCollision((GameObject*)vec_pGameObjects[playerIndex], (GameObject*)vec_pGameObjects[j] , closestPointsInEnv);
	//	}
	//	//else
	//	//{
	//	//    // Proximity test for sphere to sphere
	//	//	SphereToSphereCollision((GameObject*)vec_pGameObjects[playerIndex], (GameObject*)vec_pGameObjects[j] , closestPointsInEnv);
	//	//}
	//			
	//						
	//}

	

}



void Collision::EnemyToEnemyCollision(GameObject* sphere1 , GameObject* sphere2,  std::vector<Physics::Point> &listOfClosestPt)
{
	// Proximity test for sphere to sphere
	Physics::Sphere a ;
	a.c = sphere1->getPosition();
	a.vel = sphere1->getVelocity();
	a.r = sphere1->getScale() / 3; //((Sphere*)sphere1)->getRadius() ;

	Physics::Sphere b ; 
	b.c = sphere2->getPosition();
	b.r = sphere2->getScale() / 3;//((Sphere*)sphere2)->getRadius();
	b.vel = sphere2->getVelocity(); 
	
	Physics::Point closestPt;
	Vector3D newVel ; 
					
	if(Physics::ClosestPtSphereSphere( a,b, closestPt))
	{
		listOfClosestPt.push_back(closestPt);
		//std::cout<<"Sphere "<<sphere1->getID()<<" collided with "<<sphere2->getID()<<std::endl; 
		//Calculate change in velocity
		Vector3D newVelocityA ; 
	    Vector3D newVelocityB ; 
		newVelocityA.x = ((a.vel.x * (a.r - b.r)) + (2 * b.r * b.vel.x)) / (a.r + b.r);
		newVelocityA.y = ((a.vel.y * (a.r - b.r)) + (2 * b.r *b.vel.y)) / (a.r + b.r);
		newVelocityA.z = ((a.vel.z * (a.r - b.r)) + (2 * b.r * b.vel.z)) / (a.r + b.r);
					  
		//sphere1->setVelocity(newVelocityA);

		newVelocityB.x = ((b.vel.x * (a.r - b.r)) + (2 * b.r * a.vel.x )) / (a.r + b.r);
		newVelocityB.y = ((b.vel.y  * (a.r - b.r)) + (2 * b.r *a.vel.y)) / (a.r + b.r);
		newVelocityB.z = ((b.vel.z  * (a.r - b.r)) + (2 * b.r * a.vel.z)) / (a.r + b.r);

	
		//sphere2->setVelocity(newVelocityB);
	}
		
}

