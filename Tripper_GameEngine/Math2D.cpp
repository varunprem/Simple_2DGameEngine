#include "Math2D.h"
#include "stdio.h"

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	float distance;

	Radius = pow(Radius, 2);

	distance = pow((pCenter->x - pP->x), 2) + pow((pCenter->y - pP->y), 2);

	if (distance < Radius)
		return 1;
	else
		return 0;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	
	if (pPos->x > pRect->x + Width || pPos->x < pRect->x - Width || pPos->y < pRect->y - Height || pPos->y > pRect->y + Height) {
		return 0;
	}
	else
		return 1;

}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
  
	float distance, radius;

	distance = pow((pCenter0->x - pCenter1->x), 2) - pow((pCenter0->y - pCenter1->y), 2);

	radius = pow((Radius0 + Radius1),2);

	if (distance <= radius)
		return 1;
	else
		return 0;

}


/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	/*float sqrdistance, totalWidth, totalHeight;

	sqrdistance = pow((pRect0->x - pRect1->x), 2) + pow((pRect0->y, pRect1->y), 2);
	totalWidth = pow(((Width0/2) + (Width1/2) ), 2);
	totalHeight = pow( ( (Height0 / 2) + (Height1 / 2) ), 2);

	if (sqrdistance <= totalWidth || sqrdistance < totalHeight)
		return 1;
	else
		return 0;*/

	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	leftA = pRect0->x - Width0 /2;
	leftB = pRect1->x - Width1 / 2;

	rightA = pRect0->x + Width0 / 2;
	rightB = pRect1->x + Width1 / 2;

	topA = pRect0->y + Height0 / 2;
	topB = pRect1->y + Height1 / 2;

	bottomA = pRect0->y - Height0 / 2;
	bottomB = pRect1->y - Height1 / 2;

	if (leftA > rightB || leftB > rightA || topA < bottomB || topB < bottomA)
		return 0;
	else
		return 1;


	

}
