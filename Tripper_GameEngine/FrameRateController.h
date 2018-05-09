#ifndef FRAMERATECONTROLLER_H
#define FRAMERATECONTROLLER_H

class FrameRateController{

public:

	FrameRateController(unsigned int maxFrameRate_);
	~FrameRateController(){}

	void FrameStart(void);
	void FrameEnd(void);
	unsigned int GetFrameTime(void);

public:
	unsigned int maxFrameRate;
	unsigned int mMaxTicksPerFrame;
	unsigned int mTickStart;
	unsigned int mTickEnd;


};


#endif
