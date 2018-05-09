#ifndef DRONELOWER_DIAGONAL_H
#define DRONELOWER_DIAGONAL_H

#include "Component.h"
#include "transform.h"

class DroneLowerDiagonal : public Component
{
	public:
		DroneLowerDiagonal();
		~DroneLowerDiagonal() {};

		void Update(void);

		void Serialize(FILE **fp);
		void HandleEvent(Event *pEvent);

	public:
		float xShift, yShift;
};

#endif