#include "SentinelEnemy.h"
#include "InputManager.h"
#include "EventManager.h"
extern EventManager* gpEventManager;
extern FrameRateController* pF;
extern GameObjectManager* gOM;
extern bool shoot_Sentinel;
SentinelEnemy::SentinelEnemy() :Component(COMPONENT_TYPE::COMPONENT_SENTINELENEMY)
{
	_upDown_Limit = 0.0f;
	move = false;
}

void SentinelEnemy::Update(void)
{
	Transform* pTransform = (Transform *)mpOwner->GetComponent(COMPONENT_TRANSFORM);
	pTransform->mPosition.x -= 0.001f;
	if (pTransform->mPosition.x < 0.7f)
	{
		pTransform->mPosition.x = 0.7f;
		SentinelShootMechanism();
	}
		
		
}
void SentinelEnemy::SentinelShootMechanism()
{
	if (mpOwner)
	{
		Transform* pTr = (Transform *)mpOwner->GetComponent(COMPONENT_TRANSFORM);
		Body* pBdy = (Body *)mpOwner->GetComponent(COMPONENT_BODY);
		//	if (gpInputManager->IsReleased(SDL_SCANCODE_L))
		//	{
		if (shoot_Sentinel)
		{
			for (GameObjectInstance* pObj : gOM->mGameObjects)
			{
				Sprite* pSp = (Sprite*)pObj->GetComponent(COMPONENT_SPRITE);

				for (auto i : pObj->mComponents)
				{
					if (pSp->mType == SENTINEL_BULLET)
					{
						Transform* bulletpTr = (Transform*)pObj->GetComponent(COMPONENT_TRANSFORM);

						bulletpTr->mPosition = pTr->mPosition;
						bulletpTr->mPosition.x = pTr->mPosition.x - 0.1f;
						bulletpTr->mAngle = pTr->mAngle;

						Body* bulletBody = (Body *)pObj->GetComponent(COMPONENT_BODY);
						GameObjectInstance* ship = pTr->mpOwner;

						Body* shipBody = (Body *)ship->GetComponent(COMPONENT_BODY);

						bulletBody->VelX = 0;
						bulletBody->VelY = 0;


						if (NULL != bulletBody)
						{
							#define BULLET_SPEED -25.0f
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
		shoot_Sentinel = false;
	}
}
void SentinelEnemy::Serialize(FILE ** fp)
{

}

void SentinelEnemy::HandleEvent(Event * ev)
{

}
