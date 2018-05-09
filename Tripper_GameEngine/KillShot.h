#ifndef  KILLSHOT_H
#define  KILLSHOT_H

#include "Component.h"
#include "EventManager.h"
#include "FrameRateController.h"
#include "GameObjectManager.h"
#include "GameObjectInstance.h"


class KillShot : public Component
{
	public:
		KillShot();
		~KillShot();

		void Update(void);
		void Serialize(FILE** fp);
		void HandleEvent(Event* ev);
		GameObjectInstance* droneTarget;
};
#endif // ! KILLSHOT_H
