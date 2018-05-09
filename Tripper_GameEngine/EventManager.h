#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H
#include <list>
#include <unordered_map>
enum class EVENT_TYPE
{
	COLLIDE,
	PLAYER_HIT,
	GAME_OVER,
	DRONE_HIT,

	NUM
};

class Event
{
public:

	Event(EVENT_TYPE type);
	virtual ~Event()
	{

	}

public:
	EVENT_TYPE mType;
	float mtimer;


};

class GameObjectInstance;
class EventManager
{
public:

	EventManager();
	~EventManager();
	void BroadcastEvent(Event* ev);
	void BroadcastEventToSubscribe(Event* ev);
	void AddEvent(Event* ev);  // timed event
	void SubscribeEvent(EVENT_TYPE ev, GameObjectInstance* pGO);
	void Update(float frameTime);
	bool drawDebug = false;

	std::list<Event *> mEvents;

	std::unordered_map <EVENT_TYPE, std::list<GameObjectInstance* > > mSubscriptions;


};


#endif