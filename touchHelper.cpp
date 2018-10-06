

#include "TouchHelper.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

static TouchHelper::TOUCH_STAT m_touchDetected[2];

TouchHelper::TouchHelper(){
	//server->on ( "/",        std::bind(&WifiManager::displayCredentialCollection, this) );
	touchAttachInterrupt(32, TouchHelper::getTouchLeft, 40);
	touchAttachInterrupt(33, TouchHelper::getTouchRight, 40);
	//touchSetCycles(0x1000, 0xFFFF);
}

	void TouchHelper::getTouchLeft(){
		m_touchDetected[TOUCH_LEFT] = SELECTED;
		//DEBUGLOG("gotTouchLeft");
	}
	void TouchHelper::getTouchRight(){
		m_touchDetected[TOUCH_RIGHT] = SELECTED;
		//DEBUGLOG("gotTouchRight");
	}

//https://github.com/espressif/arduino-esp32/issues/814
void TouchHelper::handle() {
	return ;

}

TouchHelper::TOUCH_STAT TouchHelper::getTouchStat(TOUCH touch){
	TOUCH_STAT ts = m_touchDetected[touch];
	m_touchDetected[touch] = UNSELECTED;
	return ts;
};

