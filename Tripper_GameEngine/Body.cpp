#include "Body.h"
#include "Transform.h"

Body::Body():Component(COMPONENT_BODY)
{
	Xpos = 0, Ypos = 0;
	prevXpos = 0, prevYpos = 0;
	VelX = 0, VelY = 0;
	AccX = 0, AccY = 0;
	mTotalForceX = 0, mTotalForceY = 0;
	mMass = 0, mInverseMass = 0;

	mShape = NULL;


}

Body::~Body()
{

	//If shape exists then delete the shape
	if (mShape)
	{
		delete mShape;
	}
}

void Body::Update()
{


}
void Body::Serialize(FILE** fpp)
{
	//Body Mass Serializations
	fscanf(*fpp, "%f\n", &mMass, &VelX, &VelY);
	
	if (0 != mMass)
	{
		mInverseMass = 1.0f / mMass;
	}
	else
	{
		mInverseMass = 0.0f;
	}
	char ShapeTypeName[255];
	memset(ShapeTypeName, 0, 255 * sizeof(char));

	//Shape serializations
	while (fscanf(*fpp, "%s\n", ShapeTypeName) != EOF)
	{

		if (0 == strcmp("Circle", ShapeTypeName))
		{
			mShape = new ShapeCircle();
			ShapeCircle* pShCircle = (ShapeCircle*)mShape;
			mShape->mBodyOwner = this;
			fscanf(*fpp, "%f\n", &pShCircle->radius);
			
		}
		if (0 == strcmp("Rectangle", ShapeTypeName))
		{
			mShape = new ShapeRectangle();
			ShapeRectangle* pShRect = (ShapeRectangle*)mShape;
			mShape->mBodyOwner = this;
			fscanf(*fpp, "%f %f \n", &pShRect->width, &pShRect->height);

		}
		

	}
	
	
	
	


}

void Body::Integrate(float deltaTime, float gravity)
{
	if (mpOwner)
	{
		//Getiing the transform component
		Transform* pTr = (Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);
		if (pTr)
		{
			Xpos = pTr->mPosition.x;
			Ypos = pTr->mPosition.y;
		}
	}

	//Saving it in the previous position
	prevXpos = Xpos;
	prevYpos = Ypos;

	//Calculate acceleration
	//mTotalForceY += gravity;
	//AccX = mTotalForceX * mInverseMass;
	//AccY = mTotalForceY * mInverseMass;

	AccX *= 0.8f;
	AccY *= 0.8f;


	//Calculate velocity
	VelX = AccX*deltaTime + VelX;
	VelY = AccY*deltaTime + VelY;

	Sprite* pSprite = (Sprite *)mpOwner->GetComponent(COMPONENT_SPRITE);
	if (pSprite->mType == DAN)
	{
		VelX *= 0.98f;
		VelY *= 0.98f;

	}

	

	//Calculate position
	Xpos = VelX*deltaTime + Xpos;
	Ypos = VelY*deltaTime + Ypos;

	//Reset the forces
	mTotalForceX = 0;
	mTotalForceY = 0;

	//Update the transform
	if (mpOwner)
	{
		//Getiing the transform component
		Transform* pTr = (Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);
		if (pTr)
		{
			pTr->mPosition.x = Xpos;
			pTr->mPosition.y = Ypos;
		}
	}

}

void Body::HandleEvent(Event* ev)
{

}