#ifndef GAMEOBJECTINSTANCE_H
#define GAMEOBJECTINSTANCE_H



//#include "Component.h"


#include "Transform.h"
#include "Sprite.h"
#include "Controller.h"
#include "Body.h"
#include "DroneLowerDiagonal.h"
#include "DroneUpperDiagonal.h"
#include "UpDownMove.h"
#include "KillShot.h"
#include "SentinelEnemy.h"
#include "MiniFollowDrones.h"
#include "EventManager.h"
#include <vector>

class Component;


class GameObjectInstance{


public:
	GameObjectInstance()
	{
		mActive = false;


	}
	~GameObjectInstance(){}

	Component* GetComponent(unsigned int mType);
	void AddComponent(unsigned int mType);
	void HandleEvent(Event* ev);
	

public:
	bool mActive;

	std::vector<Component *> mComponents;
	
};


#endif