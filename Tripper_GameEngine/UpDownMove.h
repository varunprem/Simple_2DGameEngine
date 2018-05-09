#ifndef UPDOWNMOVE_H
#define UPDOWNMOVE_H

#include "Transform.h"
#include "Component.h"

class UpDownMove : public Component
{
	public:
		UpDownMove();
		~UpDownMove() {}

		void Update(void);
		void Serialize(FILE** fp);
		void HandleEvent(Event* ev) {}

		float _upDown_Limit, forwardSpeed, _upDown_Speed;
		bool move;
};
#endif // !UPDOWNMOVE_H

