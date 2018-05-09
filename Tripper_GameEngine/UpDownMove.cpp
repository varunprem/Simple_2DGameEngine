#include "UpDownMove.h"

UpDownMove::UpDownMove() :Component(COMPONENT_TYPE::COMPONENT_UPDOWNMOVE)
{
	_upDown_Limit = 0.0f;
	_upDown_Speed = 0.0f;
	forwardSpeed = 0.0f;
	move = false;
}
void UpDownMove::Update(void)
{
	Transform* pTransform = (Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);
	pTransform->mPosition.x -= forwardSpeed;
	if (!move)
	{
			pTransform->mPosition.y += _upDown_Speed;
		//	printf("%f \n", pTransform->mPosition.y);
			if (pTransform->mPosition.y >= _upDown_Limit)
			{
				move = true;
			}
	}

	 if (move) 
	{
			pTransform->mPosition.y -= _upDown_Speed;
			if (pTransform->mPosition.y <= -_upDown_Limit)
			{
				move = false;
			}
	}
}

void UpDownMove::Serialize(FILE ** fp)
{
	fscanf(*fp, "%f %f %f \n", &_upDown_Limit, &forwardSpeed,&_upDown_Speed);
}
