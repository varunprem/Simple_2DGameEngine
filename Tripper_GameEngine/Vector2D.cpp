#include "Vector2D.h"

#define EPSILON 0.0001
#define PI 3.141592653589793

// ---------------------------------------------------------------------------

void Vector2DZero(Vector2D *pResult)
{
	pResult->x = 0.0;
	pResult->y = 0.0;

}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D *pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
{
	pResult->x = -pVec0->x;
	pResult->y = -pVec0->y;
}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x + pVec1->x;
	pResult->y = pVec0->y + pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x - pVec1->x;
	pResult->y = pVec0->y - pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
{
	float x, y, mag;
	x = pVec0->x;
	y = pVec0->y;

	mag = sqrt((x * x) + (y * y));

	pResult->x = x / mag;
	pResult->y = y / mag;


}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
{
	pResult->x = pVec0->x * c;
	pResult->y = pVec0->y * c;

}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = (pVec0->x * c) + pVec1->x;
	pResult->y = (pVec0->y * c) + pVec1->y;

	// ---------------------------------------------------------------------------
}

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{

		pResult->x = (pVec0->x * c) - pVec1->x;
		pResult->y = (pVec0->y * c) - pVec1->y;
}


// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D *pVec0)
{
	float x, y, length;
	x = pVec0->x;
	y = pVec0->y;
	length = sqrt((x * x) + (y * y));
	return length;
}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D *pVec0)
{
	float length;
	length = Vector2DLength(pVec0);

	return (length * length);
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return sqrt(Vector2DSquareDistance(pVec0, pVec1));
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	float x, y, x1, x2, y1, y2, distance;

	x1 = pVec0->x;
	y1 = pVec0->y;

	x2 = pVec1->x;
	y2 = pVec1->y;

	x = pow(x2 - x1, 2);
	y = pow(y2 - y1, 2);


	distance = x + y;

	return distance;
}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
{
	float product;

	product = (pVec0->x * pVec1->x) + (pVec0->y * pVec1->y);
	return product;
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{
	if (!pResult)
		return;

	Vector2DFromAngleRad(pResult, angle * PI/ 180);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	if (!pResult)
		return;

	pResult->x = cos(angle);
	pResult->y = sin(angle);


}

// ---------------------------------------------------------------------------
