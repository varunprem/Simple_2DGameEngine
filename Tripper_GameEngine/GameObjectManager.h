#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "GameObjectInstance.h"
#include <vector>

class GameObjectManager{
public:
	GameObjectManager()
	{
		no_of_drones = 0;
	}
	~GameObjectManager()
	{

	}
	GameObjectInstance* LoadObject(char* filePath);
	void LoadLevel(char* Levelpath);
	
	
public:
	
	std::vector<GameObjectInstance *> mGameObjects;
	int no_of_drones;
};

#endif