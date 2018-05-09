#include "memory.h"
#include "SDL.h"
#include "InputManager.h"

InputManager::InputManager(){
	memset(mcurrentState, 0, 512 * sizeof(Uint8));
	memset(mPreviousState, 0, 512 * sizeof(Uint8));

}

InputManager::~InputManager(){

}

void InputManager::Update(){
	//Copy current->Previous
	memcpy(mPreviousState, mcurrentState, 512 * sizeof(Uint8));

	//Refresh the current state
	int numberofFetchedElements = 0;
	const Uint8* currentkeyStates = SDL_GetKeyboardState(&numberofFetchedElements);

	if(numberofFetchedElements > 512)
		numberofFetchedElements = 512;

	memcpy(mcurrentState, currentkeyStates, 512 * sizeof(Uint8) );



}

bool InputManager:: IsPressed(Uint8 keyScanCode){
	if(mcurrentState[keyScanCode] >= 512)
		return false;

	if(mcurrentState[keyScanCode] != 0)
		return true;

	return false;
}

bool InputManager::IsTriggered(Uint8 keyScanCode){

	if(mcurrentState[keyScanCode] >= 512)
		return false;
	
	if(mcurrentState[keyScanCode] != 0 && mPreviousState[keyScanCode] == 0)
		return true;

	return false;
}

bool InputManager::IsReleased(Uint8 keyScanCode){
	if(mcurrentState[keyScanCode] >= 512)
		return false;
	
	if(mcurrentState[keyScanCode] == 0 && mPreviousState[keyScanCode] != 0)
		return true;

	return false;

}