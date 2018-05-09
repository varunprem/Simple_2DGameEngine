#include "EventManager.h"
#include "GameObjectManager.h"
#include <algorithm>
extern GameObjectManager* gOM;

Event::Event(EVENT_TYPE type)
{
	mType = type;
	mtimer = 0.0f;
}

EventManager::EventManager()
{

}

EventManager::~EventManager()
{
	for (auto e : mEvents)
		delete e;

	mEvents.clear();
}

void EventManager::BroadcastEvent(Event* ev)
{
	for (auto gameObj : gOM->mGameObjects)
	{
		gameObj->HandleEvent(ev);
	}
}
void EventManager::BroadcastEventToSubscribe(Event* ev)
{
	std::list<GameObjectInstance* > &listofsubscribers = mSubscriptions[ev->mType];
	
	for (auto pGO : listofsubscribers)
	{
		pGO->HandleEvent(ev);
	}
}
void EventManager::AddEvent(Event* ev)
{
	mEvents.push_back(ev);
}

void EventManager::Update(float frameTime)
{
	std::list<Event *>::iterator itBegin, itTemp, itEnd;
	itBegin = mEvents.begin();
	itEnd = mEvents.end();

	while (itBegin != itEnd)
	{
		Event* pEvent = *itBegin;
		pEvent->mtimer -= frameTime;

		if (pEvent->mtimer <= 0)
		{
			//BroadcastEvent(pEvent);
			BroadcastEventToSubscribe(pEvent);
			delete pEvent;
			itTemp = itBegin;
			++itTemp;
			mEvents.erase(itBegin);
			itBegin = itTemp;
		}
		else
		{
			++itBegin;
		}
	}
}
void EventManager::SubscribeEvent(EVENT_TYPE ev, GameObjectInstance * pGO)
{
	std::list<GameObjectInstance* > &listofsubscribers = mSubscriptions[ev];

	if (std::find(listofsubscribers.begin(), listofsubscribers.end(), pGO) == listofsubscribers.end())
		listofsubscribers.push_back(pGO);
}