#include "CollisionManager.h"
#include "Math2D.h"

//Forward Declare the functions
bool CheckCollisionCircleCircle(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2, std::list<Contact*> &mContacts);
bool CheckCollisionCircleRectangle(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2, std::list<Contact*> &mContacts);
bool CheckCollisionRectangleCircle(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2, std::list<Contact*> &mContacts);
bool CheckCollisionRectangleRectangle(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2, std::list<Contact*> &mContacts);




CollisionManager::CollisionManager() :mContacts()
{

	mCollisionTable[(int)Shape::Type::CIRCLE][(int)Shape::Type::CIRCLE] = CheckCollisionCircleCircle;
	mCollisionTable[(int)Shape::Type::CIRCLE][(int)Shape::Type::RECTANGLE] = CheckCollisionCircleRectangle;
	mCollisionTable[(int)Shape::Type::RECTANGLE][(int)Shape::Type::CIRCLE] = CheckCollisionRectangleCircle;
	mCollisionTable[(int)Shape::Type::RECTANGLE][(int)Shape::Type::RECTANGLE] = CheckCollisionRectangleRectangle;

}

//-------------------------------------------------------------------------------------------------------------------------

CollisionManager::~CollisionManager()
{

}
//-------------------------------------------------------------------------------------------------------------------------
void CollisionManager::ResetContacts()
{
	for (auto c : mContacts)
	{
		delete c;
	}
	mContacts.clear();

}
//-------------------------------------------------------------------------------------------------------------------------

bool CollisionManager::CheckCollisionAndGenerateContacts(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2)
{
	
	//Function Pointer
	return mCollisionTable[(int)shape1->mType][(int)shape2->mType](shape1, xPos1, yPos1, shape2, xPos2, yPos2, mContacts);
}

//Individual Collision Functions
//-------------------------------------------------------------------------------------------------------------------------
/*
Checks collision between a Circle and a Circle

*/
bool CheckCollisionCircleCircle(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2, std::list<Contact*> &mContacts)
{
	ShapeCircle* pCirc1 = (ShapeCircle *)shape1;
	ShapeCircle* pCirc2 = (ShapeCircle *)shape2;

	bool CollisionResult;

	//Check for Circle to Circle Collision here

	float distance, radius;

	distance = sqrt(abs(pow((xPos1 - xPos2), 2) + pow((yPos1 - yPos2), 2) ));

	radius = pCirc1->radius + pCirc2->radius;

	//printf("Distance: %f, Radius: %f\n", distance, radius);

	if (distance <= radius)
		CollisionResult = true;
	else
		CollisionResult = false;


	
		//If Collision,
	if (CollisionResult)
	{
		//Create Contact
		Contact* pC = new Contact();

		//Save the Body Owner
		pC->mBodies[0] = shape1->mBodyOwner;
		pC->mBodies[1] = shape2->mBodyOwner;

		//Add it to the list of Contacts
		mContacts.push_back(pC);


	}

		return CollisionResult;
			

}


//-------------------------------------------------------------------------------------------------------------------------

/*
Checks collision between a Circle and a Rectangles
*/
bool CheckCollisionCircleRectangle(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2, std::list<Contact*> &mContacts)
{
	//Check Collision Here
	bool CollisionResult = CheckCollisionRectangleCircle(shape2, xPos2, yPos2, shape1, xPos1, yPos1, mContacts);

	return CollisionResult;

}
//-------------------------------------------------------------------------------------------------------------------------
/*
Checks collision between a Rectangle and a Circel
*/
bool CheckCollisionRectangleCircle(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2, std::list<Contact*> &mContacts)
{
	bool CollisionResult;

	//Check Collision Here
	ShapeRectangle* pRect = (ShapeRectangle *)shape1;
	ShapeCircle* pCirc = (ShapeCircle *)shape2;


	float left, top, bottom, right;

	left = xPos1 -  (pRect->width / 2);
	right = xPos1 + (pRect->width / 2);
	bottom = yPos1 -(pRect->height /2);
	top = yPos1 + (pRect->height/ 2);

	if (xPos2 > right) {
		xPos2 = right;
	}
	else if (xPos2 < left) {
		xPos2 = left;
	}

	if (yPos2 > top) {
		yPos2 = top;
	}
	else if (yPos2 < bottom) {
		yPos2 = bottom;
	}


	/*float squaredDistance;
	squaredDistance = Vector2DSquareDistance(&point, &circleCenter);*/

	float distance = abs(pow((xPos1 - xPos2), 2) + pow((yPos1 - yPos2), 2));
	float radius = pow(pCirc->radius, 2.0f);

	if (distance < (radius))
		CollisionResult = true;
	else
		CollisionResult = false;

	//If Collision,

	if (CollisionResult)
	{
		//Create Contact
		Contact* pC = new Contact();

		//Save the Body Owner
		pC->mBodies[0] = shape1->mBodyOwner;
		pC->mBodies[1] = shape2->mBodyOwner;

		//Add it to the list of Contacts
		mContacts.push_back(pC);
	}

	

	return CollisionResult;

}

//-------------------------------------------------------------------------------------------------------------------------

/*
	Checks collision between a Rectangle and a Rectangle
*/

bool CheckCollisionRectangleRectangle(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2, std::list<Contact*> &mContacts)
{
	
	ShapeRectangle* pRect1 = (ShapeRectangle *)shape1;
	ShapeRectangle* pRect2 = (ShapeRectangle *)shape2;

	bool CollisionResult;

	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	leftA = xPos1 - pRect1->width / 2;
	leftB = xPos2 - pRect2->width / 2;

	rightA = xPos1 + pRect1->width / 2;
	rightB = xPos2 + pRect2->width / 2;

	topA = yPos1 + pRect1->height / 2;
	topB = yPos2 + pRect2->height / 2;

	bottomA = yPos1 - pRect1->height / 2;
	bottomB = yPos2 - pRect2->height / 2;


	if (leftA > rightB || leftB > rightA || topA < bottomB || topB < bottomA)
		CollisionResult = false;
	else
		CollisionResult = true;


	//If Collision,

	if (CollisionResult)
	{
		
		//Create Contact
		Contact* pC = new Contact();

		//Save the Body Owner
		pC->mBodies[0] = shape1->mBodyOwner;
		pC->mBodies[1] = shape2->mBodyOwner;

		//Add it to the list of Contacts
		mContacts.push_back(pC);


	}

	return CollisionResult;
	

}

//-------------------------------------------------------------------------------------------------------------------------
