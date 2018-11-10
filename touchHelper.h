

#ifndef TouchHelper_h
#define TouchHelper_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#include "DelayHelper.h"




class TouchHelper
{

public:
	enum TOUCH {TOUCH_LEFT=0, TOUCH_RIGHT=1,TOUCH_COMMAND=2,TOUCH_LAST=3};
	enum TOUCH_STAT {UNSELECTED, RISING_EDGE, SELECTED_LONG, FALLING_EDGE};
	//static TOUCH_STAT m_touchDetected[2];



	TouchHelper();

	static void getTouchLeft();
	static void getTouchRight();
	static void getTouchCommand();

	TOUCH_STAT getTouchStat(TOUCH touch);

	static void handle();

};



#endif
