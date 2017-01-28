#include "GameObject.h"

// Initial value of the first GameObject ID
// (i.e. the unique IDs of the objects will start at this number)
// Note that using an unsigned int, and assuming that it's 32 bits
//	means that it may potentially wrap around at some point. 
// (but you'd have to create 4 billion objects, first)


GameObject::GameObject()
{
	
}

//void GameObject::setMediator( IMediator* pMediator )
//{
//	// The mediator should only be set at construction, so if something
//	//	tries to set it again, we prevent it
//	if ( this->m_pMediator == 0 )
//	{	// Hasn't been set, so assume creator is calling it
//		this->m_pMediator = pMediator;
//	}
//	return;
//}

GameObject::~GameObject()
{
	return;
}




   
		void GameObject::setDelegator(IDelegator* value)
		{
		
			delegator = value;
		}