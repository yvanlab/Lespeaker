

#ifndef TouchHelper_h
#define TouchHelper_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#include "DelayHelper.h"


//static bool m_touchRightdetected;


class TouchHelper
{

public:
	enum TOUCH {TOUCH_LEFT=0, TOUCH_RIGHT=1};
	enum TOUCH_STAT {UNSELECTED, SELECTED, SELECTED_LONG};
	//static TOUCH_STAT m_touchDetected[2];



	TouchHelper();

	static void getTouchLeft();
	static void getTouchRight();

	TOUCH_STAT getTouchStat(TOUCH touch);

	static void handle();

	/*static bool m_touchLeftdetected;
	static bool m_touchRightdetected;*/
/*	DelayHelper modeDelay;
	DelayHelper actionDelay;*/

};



#endif
