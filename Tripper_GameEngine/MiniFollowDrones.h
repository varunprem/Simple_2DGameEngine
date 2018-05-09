#ifndef MINIFOLLOWDRONES
#define MINIFOLLOWDRONES

#include "Vector2D.h"
#include "Component.h"
#include "Transform.h"

class MiniFollowDrones : public Component 
{

public:
	MiniFollowDrones() :Component(COMPONENT_MINIFOLLOWDRONES) {}
	~MiniFollowDrones() {}

	void Update();

	void Serialize(FILE** fpp);
	void HandleEvent(Event* ev) {}




public:

	Vector2D mVelocity;
	Vector2D normal;
};


#endif 
