#ifndef  SENTINELENEMY
#define SENTINELENEMY

#include "Component.h"
#include "Transform.h"

class SentinelEnemy : public Component
{
	public: 
		SentinelEnemy();
		~SentinelEnemy() {}

		void Update(void);
		void Serialize(FILE** fp);
		void HandleEvent(Event* ev);
		void SentinelShootMechanism();
	public:
		float _upDown_Limit = 0.0f;
		bool move = false;
};
#endif // ! SENTINELENEMY
