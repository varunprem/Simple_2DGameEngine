#include "MiniFollowDrones.h"

extern GameObjectInstance* DanJones;

#define ENEMY_AI_ROTATION_SPEED  1.0
#define ENEMY_AI_MOVE_SPEED 0.2

void MiniFollowDrones::Update()
{
	//Enemy Behaviour

	Body* pBody = (Body*)mpOwner->GetComponent(COMPONENT_BODY);
	Transform*pTransform = (Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);

	mVelocity.x = pBody->VelX;
	mVelocity.y = pBody->VelY;
	Vector2DSet(&normal, -mVelocity.y, mVelocity.x);

	float dotProduct;

	Transform* DJ = (Transform*)DanJones->GetComponent(COMPONENT_TRANSFORM);
	Vector2DSub(&mVelocity, &DJ->mPosition, &pTransform->mPosition);
	dotProduct = Vector2DDotProduct(&mVelocity, &normal);


	if (dotProduct < 0)
	{
		pTransform->mAngle -= ENEMY_AI_ROTATION_SPEED;
	}
	else
	{
		pTransform->mAngle += ENEMY_AI_ROTATION_SPEED;
	}

	pBody->VelX = cos((pTransform->mAngle -360)* 3.14 / 180);
	pBody->VelY = sin((pTransform->mAngle -360)* 3.14 / 180);
	pBody->VelX *= ENEMY_AI_MOVE_SPEED;
	pBody->VelY *= ENEMY_AI_MOVE_SPEED;

}

void  MiniFollowDrones::Serialize(FILE** fpp)
{

}