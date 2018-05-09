#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>


class InputManager{

public:

	InputManager();
	~InputManager();

	void Update();

	bool IsPressed(Uint8 keyScanCode);
	
	bool IsTriggered(Uint8 keyScanCode);

	bool IsReleased(Uint8 keyScanCode);


private:
	Uint8 mPreviousState[512];
	Uint8 mcurrentState[512];




};



#endif