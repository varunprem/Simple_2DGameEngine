#include "FrameRateController.h"
#include "SDL_timer.h"
#include "limits.h"
#include "SDL.h"

FrameRateController::FrameRateController(unsigned int maxFrameRate_){
	if(0== maxFrameRate)
		maxFrameRate = UINT_MAX;

	maxFrameRate = maxFrameRate_;
	mMaxTicksPerFrame = 1000 / maxFrameRate;

	 mTickStart = 0;
	 mTickEnd = 0;

}

void FrameRateController:: FrameStart(void){
	mTickStart = SDL_GetTicks();

}
void FrameRateController:: FrameEnd(void){
	mTickEnd = SDL_GetTicks() - mTickStart;
	while(SDL_GetTicks() - mTickStart < mMaxTicksPerFrame){
		mTickEnd = SDL_GetTicks() - mTickStart;
	}
		
}
unsigned int FrameRateController:: GetFrameTime(void){

	return mTickEnd;
}