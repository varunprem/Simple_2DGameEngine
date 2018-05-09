#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Body.h"
#include <list>

class Body;



class Shape
{
public:
	enum class Type
	{
		CIRCLE,
		RECTANGLE,

		NUM,
	};
	//Shape(){}
	Shape(Type type) 
	{
		mType = type;
		mBodyOwner = NULL;
	}
	virtual bool TestPoint() = 0;
	virtual ~Shape(){}
public:
	Type mType;
	Body* mBodyOwner;
};


class ShapeCircle : public Shape
{

public:

	ShapeCircle() : Shape(Shape::Type::CIRCLE)
	{
		radius = 0;
	}
	bool TestPoint()
	{
		return false; 
	}

	~ShapeCircle(){}

public:
	float radius;


};

class ShapeRectangle : public Shape
{
public:

	ShapeRectangle() :Shape(Shape::Type::RECTANGLE)
	{
		width = height = 0.0f;
	}
	bool TestPoint()
	{ 
		return false; 
	}

	~ShapeRectangle(){}

public:
	float width, height;

};

class Contact;

class CollisionManager 
{

public:


	CollisionManager();
	~CollisionManager();

	//Clearing the list of contacts
	void ResetContacts();

	//Universal Collision Function
	bool CheckCollisionAndGenerateContacts(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2);
	
public:
	std::list <Contact* >mContacts;

	bool ( *mCollisionTable[(int)Shape::Type::NUM][(int)Shape::Type::NUM] )(Shape* shape1, float xPos1, float yPos1, Shape* shape2, float xPos2, float yPos2, std::list<Contact*> &mContacts) ;

};

class Contact
{

public:

	Contact()
	{
		mBodies[0] = NULL;
		mBodies[1] = NULL;

	}

public:
	Body* mBodies[2];

};


#endif