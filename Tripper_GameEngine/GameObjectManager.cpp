#include "GameObjectManager.h"
#include "Transform.h"
#include "Controller.h"
#include "Body.h"
#include "DroneLowerDiagonal.h"
#include "DroneUpperDiagonal.h"
#include "UpDownMove.h"
#include "KillShot.h"
#include "SentinelEnemy.h"

extern int no_of_drones;
GameObjectInstance* GameObjectManager::LoadObject(char* filePath)
{
	
	GameObjectInstance* pInst = new GameObjectInstance();

	FILE* fp;
	fp = fopen(filePath, "r");

	char stringName[256];
	memset(stringName, 0, 256 * sizeof(char));
	//While we reach the end of file
	while (fscanf(fp, "%s \n", stringName) != EOF)
	{
		
				//Comparing the transform string
				if (0 == strcmp("Transform", stringName))
				{
					pInst->AddComponent(COMPONENT_TRANSFORM);
					Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
					pTr->mpOwner = pInst;
					pTr->Serialize(&fp);
				}
				if (0 == strcmp("Sprite", stringName))
				{
					char verticesName[256];
					pInst->AddComponent(COMPONENT_SPRITE);
					Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
					pSp->mpOwner = pInst;
					fscanf(fp, "%s", verticesName);
					printf("String: %s \n", verticesName);
					//pSp->Serialize(spritePath);
					pSp->SerializeVertices(verticesName);
					//pSp->Serialize(&fp);
				}
				if (0 == strcmp("Controller", stringName))
				{
					pInst->AddComponent(COMPONENT_CONTROLLER);
					Controller* pCtr = (Controller *)pInst->GetComponent(COMPONENT_CONTROLLER);
					pCtr->mpOwner = pInst;
					pCtr->Serialize(&fp);
				}
				if (0 == strcmp("Body", stringName))
				{
					pInst->AddComponent(COMPONENT_BODY);
					Body* pBody = (Body*)pInst->GetComponent(COMPONENT_BODY);
					pBody->mpOwner = pInst;
					pBody->Serialize(&fp);
				}
				if (0 == strcmp("DRONEUP", stringName))
				{
					pInst->AddComponent(COMPONENT_DRONEUP);
					DroneUpperDiagonal* pDrone = (DroneUpperDiagonal *)pInst->GetComponent(COMPONENT_DRONEUP);
					pDrone->mpOwner = pInst;
					pDrone->Serialize(&fp);
				}
				if (0 == strcmp("DRONEDOWN", stringName))
				{
					pInst->AddComponent(COMPONENT_DRONEDOWN);
					DroneLowerDiagonal* pDrone = (DroneLowerDiagonal *)pInst->GetComponent(COMPONENT_DRONEDOWN);
					pDrone->mpOwner = pInst;
					pDrone->Serialize(&fp);
				}
				if (0 == strcmp("DRONEUPDOWN", stringName))
				{
					pInst->AddComponent(COMPONENT_UPDOWNMOVE);
					UpDownMove* pDrone = (UpDownMove *)pInst->GetComponent(COMPONENT_UPDOWNMOVE);
					pDrone->mpOwner = pInst;
					pDrone->Serialize(&fp);
				}
				if (0 == strcmp("KILLSHOT", stringName))
				{
					pInst->AddComponent(COMPONENT_KILLSHOT);
					KillShot* pDrone = (KillShot *)pInst->GetComponent(COMPONENT_KILLSHOT);
					pDrone->mpOwner = pInst;
					pDrone->Serialize(&fp);
				}
				if (0 == strcmp("SENTINEL", stringName))
				{
					pInst->AddComponent(COMPONENT_SENTINELENEMY);
					SentinelEnemy* pDrone = (SentinelEnemy *)pInst->GetComponent(COMPONENT_SENTINELENEMY);
					pDrone->mpOwner = pInst;
					pDrone->Serialize(&fp);
				}
				if (0 == strcmp("MiniFollowDrone", stringName))
				{
					pInst->AddComponent(COMPONENT_MINIFOLLOWDRONES);
					MiniFollowDrones* pDrone = (MiniFollowDrones *)pInst->GetComponent(COMPONENT_MINIFOLLOWDRONES);
					pDrone->mpOwner = pInst;
					pDrone->Serialize(&fp);
				}
	}

	mGameObjects.push_back(pInst);

	return pInst;
}



void GameObjectManager::LoadLevel(char* levelPath)
{
	GameObjectInstance* pInst = new GameObjectInstance();

	FILE* levelP;
	levelP = fopen(levelPath, "r");

	char stringName[256];
	memset(stringName, 0, 256 * sizeof(char));

	while (fscanf(levelP, "%s", stringName) != EOF)
	{
		if (0 == strcmp("Dan", stringName))
		{
			
			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = DAN;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);
		}
		if (0 == strcmp("Gunship", stringName))
		{

			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = GUNSHIP;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);
		}
		if (0 == strcmp("Bullet", stringName))
		{
			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = BULLET;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);

		}
		if (0 == strcmp("Drones", stringName))
		{
			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = DRONES;
			pSp->active = true;
			fscanf(levelP, "%f %f %f\n", &pTr->mPosition.x, &pTr->mPosition.y, &pTr->mAngle);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);
			no_of_drones++;
		}
		if (0 == strcmp("KillShot", stringName))
		{
			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = KILLSHOT;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);
		}
		if (0 == strcmp("DanJonesBody", stringName))
		{

			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);

		}
		if (0 == strcmp("Shield", stringName))
		{

			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);

		}
		if (0 == strcmp("NightSky", stringName))
		{

			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);

		}
		if (0 == strcmp("BulletFire", stringName))
		{

			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = BULLETFIRE;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);

		}
		if (0 == strcmp("SkyboxScroll", stringName))
		{
			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = SKYBOX_SCROLL;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);
		}
		if (0 == strcmp("Sentinel", stringName))
		{
			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = RANGE_DRONES;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);
		}
		if (0 == strcmp("Sentinel_Bullet", stringName))
		{
			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = SENTINEL_BULLET;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);
		}
		if (0 == strcmp("FollowDrones", stringName))
		{
			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = DRONES;
			pSp->active = true;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);
			no_of_drones++;
		}
		if (0 == strcmp("HealthBarBase", stringName))
		{

			fscanf(levelP, "%s", stringName);
			pInst = LoadObject(stringName);
			Transform* pTr = (Transform *)pInst->GetComponent(COMPONENT_TRANSFORM);
			Sprite* pSp = (Sprite *)pInst->GetComponent(COMPONENT_SPRITE);
			pSp->mType = HEALTHBAR;
			fscanf(levelP, "%f %f\n", &pTr->mPosition.x, &pTr->mPosition.y);
			printf("%f %f\n", pTr->mPosition.x, pTr->mPosition.y);

		}
	}

}



