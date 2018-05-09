#include "Transform.h"
#include <string>
#include <iostream>

extern GameObjectManager* gOM;
extern EventManager* gpEventManager;
extern SentinelEnemy* sm;
extern bool shoot_Sentinel;
using namespace std;


void Transform::Serialize(FILE** fp)
{
	//Reading the x and y positions and storing them in the component
	fscanf(*fp, "%f %f %f", &mScaleX, &mScaleY, &mAngle);

}

void Transform::Update()
{
	//Compute the transformation matrice every frame
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(mPosition.x, mPosition.y, 0.0f));

	glm::mat4 scale;
	scale = glm::scale(scale, glm::vec3(mScaleX ,mScaleY, 0.0f));

	glm::mat4 rotate;
	rotate = glm::rotate(rotate, glm::radians(mAngle), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 intermediate;
	intermediate = scale * rotate;

	mpTransform = trans * intermediate ;

}
void Transform::HandleEvent(Event* ev)
{
	if (ev->mType == EVENT_TYPE::DRONE_HIT)
	{
		Sprite* pSprite = (Sprite *)mpOwner->GetComponent(COMPONENT_SPRITE);
		Body* pBody = (Body *)mpOwner->GetComponent(COMPONENT_BODY);

		if (pSprite->mType == BULLET || pSprite->mType == DRONES || pSprite->mType == KILLSHOT)
		{
			if (pSprite->mType == BULLET)
			{
				pBody->Xpos = -50.0f;
				pBody->Ypos = -50.0f;
			}
			if (pSprite->mType == DRONES)
			{
				pBody->Xpos = 100.0f;
				pBody->Ypos = 100.0f;
			}
			if (pSprite->mType == KILLSHOT)
			{
				pBody->Xpos = -200.0f;
				pBody->Ypos = -200.0f;
			}
			gOM->no_of_drones--;
		}
		
	}
	else if (ev->mType == EVENT_TYPE::COLLIDE)
	{
		Sprite* pSprite = (Sprite *)mpOwner->GetComponent(COMPONENT_SPRITE);
		Body* pBody = (Body *)mpOwner->GetComponent(COMPONENT_BODY);
		if ( pSprite->mType == DRONES || pSprite->mType == KILLSHOT || pSprite->mType == SENTINEL_BULLET)
		{
			if (pSprite->mType == DRONES)
			{
				pBody->Xpos = -100.0f;
				pBody->Ypos = -100.0f;
			}
			if (pSprite->mType == KILLSHOT)
			{
				pBody->Xpos = -200.0f;
				pBody->Ypos = -200.0f;
			}
			if (pSprite->mType == SENTINEL_BULLET)
			{
				shoot_Sentinel = true;
				pBody->Xpos = -400.0f;
				pBody->Ypos = -400.0f;
			}
		}

	}
}

