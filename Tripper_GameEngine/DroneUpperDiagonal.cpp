#include "DroneUpperDiagonal.h"
#include "Component.h"
#include "Controller.h"
#include "GameObjectInstance.h"
#include "EventManager.h"
#include "Sprite.h"

DroneUpperDiagonal::DroneUpperDiagonal() :Component(COMPONENT_TYPE::COMPONENT_DRONEUP)
{
	xShift = 0.0f;
	yShift = 0.0f;
}

void DroneUpperDiagonal::Update(void)
{
	//Transform *pTransform = static_cast<Transform*>(mpOwner->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	Transform *pTransform = (Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);

	pTransform->mPosition.x -= xShift;
	pTransform->mPosition.y += yShift;
}

void DroneUpperDiagonal::Serialize(FILE ** fp)
{
	fscanf(*fp, "%f %f", &xShift, &yShift);
}

void DroneUpperDiagonal::HandleEvent(Event * pEvent)
{

}
