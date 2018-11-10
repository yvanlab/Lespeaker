

#include "TouchHelper.h"
#include "BaseManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class TouchDetail
{
	public:
	TouchDetail(/*uint8_t _pin, TouchHelper::TOUCH_STAT _touchStatus*/){};
		TouchHelper::TOUCH_STAT m_touchStatus = TouchHelper::UNSELECTED;
		uint8_t m_pin = 0;
		uint32_t m_initialTouchMS = 0;

};
static TouchDetail m_touch[3];

TouchHelper::TouchHelper(){
	//server->on ( "/",        std::bind(&WifiManager::displayCredentialCollection, this) );
	m_touch[TOUCH_LEFT].m_pin = 32;
	touchAttachInterrupt(m_touch[TOUCH_LEFT].m_pin, TouchHelper::getTouchLeft, 40);

	m_touch[TOUCH_RIGHT].m_pin = 33;
	touchAttachInterrupt(m_touch[TOUCH_RIGHT].m_pin, TouchHelper::getTouchRight, 40);

	m_touch[TOUCH_COMMAND].m_pin = 13;
	touchAttachInterrupt(m_touch[TOUCH_COMMAND].m_pin, TouchHelper::getTouchCommand, 40);
	//touchSetCycles(0x1000, 0xFFFF);
}

void TouchHelper::getTouchCommand(){
		m_touch[TOUCH_COMMAND].m_touchStatus = RISING_EDGE;
		if (m_touch[TOUCH_COMMAND].m_initialTouchMS ==0)
			m_touch[TOUCH_LEFT].m_initialTouchMS = millis();
		//DEBUGLOGF("TOUCH_COMMAND [%d] \n",m_touch[TOUCH_COMMAND].m_initialTouchMS);
	}

void TouchHelper::getTouchLeft(){
		m_touch[TOUCH_LEFT].m_touchStatus = RISING_EDGE;
		if (m_touch[TOUCH_LEFT].m_initialTouchMS ==0)
			m_touch[TOUCH_LEFT].m_initialTouchMS = millis();
		//DEBUGLOGF("TOUCH_LEFT [%d] \n",m_touch[TOUCH_LEFT].m_initialTouchMS);
	}

void TouchHelper::getTouchRight(){
		m_touch[TOUCH_RIGHT].m_touchStatus = RISING_EDGE;
		if (m_touch[TOUCH_RIGHT].m_initialTouchMS ==0)
			m_touch[TOUCH_RIGHT].m_initialTouchMS = millis();
		//DEBUGLOGF("TOUCH_RIGHT [%d] \n",m_touch[TOUCH_RIGHT].m_initialTouchMS);
	}

//https://github.com/espressif/arduino-esp32/issues/814
void TouchHelper::handle() {
	for(uint8_t t=TOUCH_LEFT; t<TOUCH_LAST; t++) {
		if(m_touch[t].m_touchStatus == RISING_EDGE || m_touch[t].m_touchStatus == SELECTED_LONG){
			if (touchRead(m_touch[t].m_pin)>50){
				m_touch[t].m_touchStatus = FALLING_EDGE;
				m_touch[t].m_initialTouchMS = 0;
			} else if ((millis() - m_touch[t].m_initialTouchMS) > 3000) {
				m_touch[t].m_touchStatus = SELECTED_LONG;
				//DEBUGLOGF("Touch [%d] Long\n",t);
			}
		}
	}
	return ;

}

TouchHelper::TOUCH_STAT TouchHelper::getTouchStat(TOUCH touch){
	TOUCH_STAT ts = m_touch[touch].m_touchStatus;
	if (ts == FALLING_EDGE)
		m_touch[touch].m_touchStatus = UNSELECTED;
	return ts;
};

