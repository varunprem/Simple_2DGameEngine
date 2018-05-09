#include "Controller.h"
#include "GameObjectInstance.h"
#include "FrameRateController.h"
#include "GameObjectManager.h"

extern EventManager* gpEventManager;
extern FrameRateController* pF;
extern GameObjectManager* gOM;
extern bool _gameControl;
//extern bool drawDebug;
//extern Mix_Music *bgm;
//extern Mix_Chunk *sfx;


Controller::Controller():Component(COMPONENT_CONTROLLER)
{
	_mHealth = 50.0f;
	flag = false;
}

void Controller::Update()
{
	if (_mHealth < 0)
	{
		_gameControl = false;
	}
	if (gpInputManager != NULL)
	{
		
		if (mpOwner)
		{
			//Updating the keyboard state
		//	gpInputManager->Update();

			Transform* pTr = (Transform *)mpOwner->GetComponent(COMPONENT_TRANSFORM);
			Body* pBdy = (Body *)mpOwner->GetComponent(COMPONENT_BODY);

			if (pTr)
			{
				//Checking for keypress events
				if (gpInputManager->IsPressed(SDL_SCANCODE_UP))
				{
					
				}
				if (gpInputManager->IsPressed(SDL_SCANCODE_DOWN))
				{
					/*if (NULL != pBdy)
					{
						float accelerationValue = -3.0f;

						pBdy->AccX = accelerationValue * cosf(pTr->mAngle + 90)*3.14 / 180;
						pBdy->AccY = accelerationValue * sinf(pTr->mAngle + 90)*3.14 / 180;
					}*/
				}
				if (gpInputManager->IsPressed(SDL_SCANCODE_LEFT))
				{
					pTr->mAngle += 0.3f * pF->GetFrameTime();
					if (pTr->mAngle >= 90.0f)
						pTr->mAngle = 90.0f;
				}
				if (gpInputManager->IsPressed(SDL_SCANCODE_RIGHT))
				{
					pTr->mAngle -= 0.3f *pF->GetFrameTime();
					if (pTr->mAngle <= -90.0f)
						pTr->mAngle = -90.0f;
				}
				if (gpInputManager->IsReleased(SDL_SCANCODE_SPACE))
				{
					//Get the bullet object
					for (GameObjectInstance* pObj : gOM->mGameObjects)
					{
						Sprite* pSp = (Sprite*)pObj->GetComponent(COMPONENT_SPRITE);

						for (auto i : pObj->mComponents)
						{
							if (pSp->mType == BULLET)
							{
								Transform* bulletpTr= (Transform*)pObj->GetComponent(COMPONENT_TRANSFORM);

								bulletpTr->mPosition = pTr->mPosition;	
								bulletpTr->mAngle = pTr->mAngle;

								Body* bulletBody = (Body *)pObj->GetComponent(COMPONENT_BODY);
								GameObjectInstance* ship = pTr->mpOwner;

								Body* shipBody = (Body *)ship->GetComponent(COMPONENT_BODY);

								bulletBody->VelX = 0;
								bulletBody->VelY = 0;


								if (NULL != bulletBody)
								{
									#define BULLET_SPEED 40.0f
									bulletBody->AccX = shipBody->AccX + (BULLET_SPEED * cosf((pTr->mAngle) *3.14 / 180));
									bulletBody->AccY = shipBody->AccY + (BULLET_SPEED * sinf((pTr->mAngle) *3.14 / 180));
								//	Mix_PlayChannel(-1, sfx, 0);
								}
								//printf("Bullet Angle: %f\n", bulletpTr->mAngle);
								//printf("Ship Angle: %f\n", pTr->mAngle);	
							}
						}
					}
				}
				if (gpInputManager->IsReleased(SDL_SCANCODE_K))
				{

					//Get the bullet object
					for (GameObjectInstance* pObj : gOM->mGameObjects)
					{

						Sprite* pSp = (Sprite*)pObj->GetComponent(COMPONENT_SPRITE);

						for (auto i : pObj->mComponents)
						{
							if (pSp->mType == KILLSHOT)
							{
								Transform* killShotTransform = (Transform*)pObj->GetComponent(COMPONENT_TRANSFORM);
								Body* killShotBody = (Body *)pObj->GetComponent(COMPONENT_BODY);

								killShotTransform->mPosition = pTr->mPosition;
								killShotTransform->mAngle = pTr->mAngle;
								killShotBody->VelX = 0;
								killShotBody->VelY = 0;
								
								GameObjectInstance* ship = pTr->mpOwner;

								Body* shipBody = (Body *)ship->GetComponent(COMPONENT_BODY);

								
								if (NULL != killShotBody)
								{
									#define KILLSHOTSPEED 5.0f
									killShotBody->VelX = shipBody->VelX + (KILLSHOTSPEED * cosf((pTr->mAngle) *3.14 / 180));
									killShotBody->VelY = shipBody->VelY + (KILLSHOTSPEED * sinf((pTr->mAngle) *3.14 / 180));
								}
								//printf("Bullet Angle: %f\n", killShotTransform->mAngle);
							}
						}
					}
				}
				
			}
		}
	}
}


Controller::~Controller()
{

}

void Controller::Serialize(FILE** fpp)
{
	int subscribe;
	fscanf(*fpp, "%f ", &speed, &subscribe);
	if(1 == subscribe)
		gpEventManager->SubscribeEvent(EVENT_TYPE::PLAYER_HIT, this->mpOwner);
}

void Controller::HandleEvent(Event* ev)
{
	if (ev->mType == EVENT_TYPE::COLLIDE)
	{
		Body* pBody = (Body *)mpOwner->GetComponent(COMPONENT_BODY);
		Transform* pTrans = (Transform *)mpOwner->GetComponent(COMPONENT_TRANSFORM);
		Sprite* pSprite = (Sprite *)mpOwner->GetComponent(COMPONENT_SPRITE);
		_mHealth -= 5.0f;
		flag = true;
	//	pBody->Xpos = -0.75f;
	//	pBody->Ypos = 0.0f;
	//	pTrans->mAngle = 0.0f;
	//	pBody->VelX = 0.0f;
	//	pBody->VelY = 0.0f;

		/*PlayerHitEvent* pHitEvent = new PlayerHitEvent();
		pHitEvent->mtimer = 3.0f;
		gpEventManager->AddEvent(pHitEvent);
		*/	
	//	printf("Dan Collided \n");
	}		

}