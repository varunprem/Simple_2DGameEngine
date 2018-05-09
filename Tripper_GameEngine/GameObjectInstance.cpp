#include "GameObjectInstance.h"

Component* GameObjectInstance::GetComponent(unsigned int mType)
{
	for (auto c : mComponents)
	{
		if (c->mType == mType)
		{
			return c;
		}
	}
	return NULL;
}

void GameObjectInstance::AddComponent(unsigned int mType)
{
	Component* newComponent = NULL;
	switch (mType)
	{
	case COMPONENT_TRANSFORM:
		newComponent = new Transform();
		break;
	case COMPONENT_SPRITE:
		newComponent = new Sprite();
		break;
	case COMPONENT_CONTROLLER:
		newComponent = new Controller();
		break;
	case COMPONENT_BODY:
		newComponent = new Body();
		break;
	case COMPONENT_DRONEDOWN:
		newComponent = new DroneLowerDiagonal();
		break;
	case COMPONENT_DRONEUP:
		newComponent = new DroneUpperDiagonal();
		break;
	case COMPONENT_UPDOWNMOVE:
		newComponent = new UpDownMove();
		break;
	case COMPONENT_KILLSHOT:
		newComponent = new KillShot();
		break;
	case COMPONENT_SENTINELENEMY:
		newComponent = new SentinelEnemy();
		break;
	case COMPONENT_MINIFOLLOWDRONES:
		newComponent = new MiniFollowDrones();
		break;
	}
	//Push it to the list
	mComponents.push_back(newComponent);

}

void GameObjectInstance::HandleEvent(Event* ev)
{
	for (auto i : mComponents)
	{
		i->HandleEvent(ev);
	}
}