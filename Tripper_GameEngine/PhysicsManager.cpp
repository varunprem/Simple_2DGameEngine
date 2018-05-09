#include "PhysicsManager.h"
#include "GameObjectManager.h"
#include "Body.h"
#include "CollisionManager.h"

extern CollisionManager* gpCollisionManager;
extern EventManager* gpEventManager;
extern int count_death;

PhysicsManager::PhysicsManager()
{


}


PhysicsManager::~PhysicsManager()
{


}
void PhysicsManager::Integrate(float deltaTime, float gravity, GameObjectManager* pTrGameObjManager)
{

	for (GameObjectInstance* pObj : pTrGameObjManager->mGameObjects)
	{
		Body* pBody = (Body*)pObj->GetComponent(COMPONENT_BODY);
		if (NULL != pBody)
		{
			pBody->Integrate(deltaTime * 0.001, gravity);
		}
	}

	//Reset the Contacts
	gpCollisionManager->ResetContacts();

	unsigned int objectNum = pTrGameObjManager->mGameObjects.size();

	for (unsigned int i = 0; i < objectNum; i++)
	{
		Body* pBody1 = (Body *)pTrGameObjManager->mGameObjects[i]->GetComponent(COMPONENT_BODY);


		if (pBody1 == NULL)
			continue;

		for (unsigned int j = i + 1; j < objectNum; j++)
		{
			Body* pBody2 = (Body *)pTrGameObjManager->mGameObjects[j]->GetComponent(COMPONENT_BODY);


			if (pBody2 == NULL)
				continue;

			gpCollisionManager->CheckCollisionAndGenerateContacts(pBody1->mShape, pBody1->Xpos, pBody1->Ypos, pBody2->mShape, pBody2->Xpos, pBody2->Ypos);	
		}
	}

	//Handle the Events
	for (auto contact : gpCollisionManager->mContacts)
	{
		CollideEvent cEvent;
		cEvent.pObj1 = contact->mBodies[0]->mpOwner;
		cEvent.pObj2 = contact->mBodies[1]->mpOwner;

		DroneHitEvent droneEvent;
		droneEvent.pObj1 = contact->mBodies[0]->mpOwner;
		droneEvent.pObj2 = contact->mBodies[1]->mpOwner;

		Sprite* pSprite1 = (Sprite *)droneEvent.pObj1->GetComponent(COMPONENT_SPRITE);
		Sprite* pSprite2 = (Sprite *)droneEvent.pObj2->GetComponent(COMPONENT_SPRITE);


		//Drones and Ship Collision Event
		if (pSprite1->mType == DAN && pSprite2->mType == DRONES || pSprite1->mType == GUNSHIP && pSprite2->mType == DRONES 
			|| pSprite1->mType == DAN && pSprite2->mType == SENTINEL_BULLET || pSprite1->mType == GUNSHIP && pSprite2->mType == SENTINEL_BULLET)
		{
			cEvent.pObj1->HandleEvent(&cEvent);
			cEvent.pObj2->HandleEvent(&cEvent);
	//			count_death++;
		}

		//Drones and Bullet Collision Event 
		GameObjectInstance* bullet;
		bullet = pSprite1->mpOwner;

		if (pSprite1->mType == BULLET && pSprite2->mType == DRONES 
			|| pSprite1->mType == DRONES && pSprite1->mType == BULLET
			|| pSprite1->mType == KILLSHOT && pSprite2->mType == DRONES
			|| pSprite1->mType == DRONES && pSprite2->mType == KILLSHOT
			||pSprite1->mType == BULLET && pSprite2->mType == RANGE_DRONES
			|| pSprite1->mType == RANGE_DRONES && pSprite1->mType == BULLET
			|| pSprite1->mType == KILLSHOT && pSprite2->mType == RANGE_DRONES
			|| pSprite1->mType == RANGE_DRONES && pSprite2->mType == KILLSHOT)
		{
			droneEvent.pObj1->HandleEvent(&droneEvent);
			droneEvent.pObj2->HandleEvent(&droneEvent);

			pSprite1->active = false;
			pSprite2->active = false;
			printf("Drone and Bullet Collsion taken place \n");
		}
	}
	

	//Commit CHanges back to transform
	for (GameObjectInstance* pObj : pTrGameObjManager->mGameObjects)
	{
		Body* pBody = (Body *)pObj->GetComponent(COMPONENT_BODY);

		if (NULL != pBody)
		{
			Transform* pTr = (Transform *)pObj->GetComponent(COMPONENT_TRANSFORM);
			pTr->mPosition.x = pBody->Xpos;
			pTr->mPosition.y = pBody->Ypos;
		}
	}


	


}
