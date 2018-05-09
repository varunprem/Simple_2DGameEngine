#include "KillShot.h"
#include "Vector2D.h"

#define KILLSHOT_ROT_SPEED	0.1f
#define KILLSHOT_SPEED      0.5f


extern EventManager* gpEventManager;
extern FrameRateController* pF;
extern GameObjectManager* gOM;

KillShot::KillShot() :Component(COMPONENT_TYPE::COMPONENT_KILLSHOT)
{

}

KillShot::~KillShot()
{

}

void KillShot::Update(void)
{
	if (mType == KILLSHOT)
	{
		GameObjectInstance* missile;
		missile = mpOwner;
		GameObjectInstance * myTarget = NULL;
		//Acquiring the target

		//Get the asteroid Object
		for (GameObjectInstance* pObj : gOM->mGameObjects)
		{
			for (auto i : pObj->mComponents)
			{
				Sprite* sprite = (Sprite *)pObj->GetComponent(COMPONENT_SPRITE);

				if (sprite->mType == DRONES)
				{
					if (sprite->active)
					{
						if (droneTarget == NULL)
						{
							float minDistance;
							int minSet = 0;

							GameObjectInstance* asteroid;
							asteroid = sprite->mpOwner;

							//Get missile and asteroid transform
							Transform* missileTransform = (Transform *)missile->GetComponent(COMPONENT_TRANSFORM);
							Transform* asteroidTransform = (Transform *)asteroid->GetComponent(COMPONENT_TRANSFORM);


							//if (active)
							//{
							if (!minSet)
							{
								minSet = 1;
								minDistance = Vector2DDistance(&missileTransform->mPosition, &asteroidTransform->mPosition);
								if (minDistance > 10)
								{
									return;
								}

								else
								{
									myTarget = asteroid;
								}


							}
							else if (Vector2DDistance(&missileTransform->mPosition, &asteroidTransform->mPosition) < minDistance)
							{
								minDistance = Vector2DDistance(&missileTransform->mPosition, &asteroidTransform->mPosition);
								if (minDistance > 10)
								{
									return;
								}
								else
								{
									myTarget = asteroid;
								}


							}

							if (minSet)
							{
								droneTarget = myTarget;
							}

						}

						//If there is target
						else //if(target != NULL)
						{

							if (sprite->active)
							{
								Vector2D missileVelocity;
								Vector2D normal;
								float dotPr;
								float angle;

								Body* missileBody = (Body *)missile->GetComponent(COMPONENT_BODY);


								Vector2DSet(&normal, -missileBody->VelY, missileBody->VelX);

								Transform* targetTransform = (Transform *)droneTarget->GetComponent(COMPONENT_TRANSFORM);
								Transform* missileTransform = (Transform *)missile->GetComponent(COMPONENT_TRANSFORM);

								Vector2DSub(&missileVelocity, &targetTransform->mPosition, &missileTransform->mPosition);

								dotPr = Vector2DDotProduct(&missileVelocity, &normal);

								Vector2D currentMissileVelocity;

								currentMissileVelocity.x = missileBody->VelX;
								currentMissileVelocity.y = missileBody->VelY;


								if (dotPr < 0)
								{
									missileTransform->mAngle -= KILLSHOT_ROT_SPEED * pF->GetFrameTime();
								}
								else
								{
									missileTransform->mAngle += KILLSHOT_ROT_SPEED  * pF->GetFrameTime();
								}

								currentMissileVelocity.x = cosf((missileTransform->mAngle + 90)* 3.14 / 180);
								currentMissileVelocity.y = sinf((missileTransform->mAngle + 90)* 3.14 / 180);

								currentMissileVelocity.x *= KILLSHOT_SPEED;
								currentMissileVelocity.y *= KILLSHOT_SPEED;

								missileBody->VelX = currentMissileVelocity.x;
								missileBody->VelY = currentMissileVelocity.y;

							}

						}




					}
				}



			}

		}

	}
}

void KillShot::Serialize(FILE ** fp)
{

}

void KillShot::HandleEvent(Event* ev)
{
	if (ev->mType == EVENT_TYPE::DRONE_HIT)
	{
		droneTarget = NULL;
	}
}
