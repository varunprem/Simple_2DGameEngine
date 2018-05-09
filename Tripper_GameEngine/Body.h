#ifndef BODY_H
#define BODY_H
#include "Component.h"
#include "CollisionManager.h"
#include "EventManager.h"



class CollisionManager;

class Shape;

class Body : public Component{
public:
	Body();
	
	~Body();
	

	void Update();
	void Serialize(FILE **fp);
	void Integrate(float deltaTime, float gravity);
	void HandleEvent(Event* ev);

public:
	float Xpos, Ypos;
	float prevXpos, prevYpos;
	float VelX, VelY;
	float AccX, AccY;
	float mTotalForceX, mTotalForceY;
	float mMass, mInverseMass;

	//Pointer to the shapes
	Shape* mShape;
};


#endif