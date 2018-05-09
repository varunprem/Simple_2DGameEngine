#ifndef DRONEUPPER_DIAGONAL_H
#define DRONEUPPER_DIAGONAL_H

#include "Component.h"
#include "transform.h"

class DroneUpperDiagonal : public Component
{
	public:
		DroneUpperDiagonal();
		~DroneUpperDiagonal() {};

		void Update(void);

		void Serialize(FILE **fp);
		void HandleEvent(Event *pEvent);

	public:
		float xShift, yShift;
};

#endif