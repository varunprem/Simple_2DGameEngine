#include "DroneLowerDiagonal.h"
#include "Component.h"
#include "Controller.h"
#include "GameObjectInstance.h"
#include "EventManager.h"
#include "Sprite.h"

DroneLowerDiagonal::DroneLowerDiagonal() :Component(COMPONENT_TYPE::COMPONENT_DRONEDOWN)
{
	xShift = 0.0f;
	yShift = 0.0f;
}

void DroneLowerDiagonal::Update(void)
{
	//Transform *pTransform = static_cast<Transform*>(mpOwner->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	Transform *pTransform = (Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);

	pTransform->mPosition.x -= xShift;
	pTransform->mPosition.y -= yShift;
}

void DroneLowerDiagonal::Serialize(FILE ** fp)
{
	fscanf(*fp, "%f %f", &xShift, &yShift);
}

void DroneLowerDiagonal::HandleEvent(Event * pEvent)
{

}
