

#include "actionManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


ActionManager::ActionManager(unsigned char pinLed) : BaseManager(pinLed){

}
//https://github.com/espressif/arduino-esp32/issues/814
void ActionManager::handle(bool _someOneHere) {

	bool touchRightdetected	= m_touch.getTouchStat(TouchHelper::TOUCH_RIGHT);
	bool touchLeftdetected	= m_touch.getTouchStat(TouchHelper::TOUCH_LEFT);
	bool someOneHere		= _someOneHere;



	if (!someOneHere){
		if (m_action == STOPPED)
			return;
		if (m_action != SWITH_OFF) {
			m_action = SWITH_OFF;
		} else
			m_action = STOPPED;
		return;
	}

	if (m_action == STOPPED) {
		//wake up
		m_action = WAKE_UP;
		return;
	}



	if ( (touchRightdetected && touchLeftdetected) && modeDelay.isDone() ){
		if (m_mode == VOLUME) m_mode = SELECTION;
		else m_mode = VOLUME;
		DEBUGLOG("Mode");
		modeDelay.startDelay(1000);
		return;
	}
	if (actionDelay.isDone()) {
		if (touchRightdetected ) {
			if (m_mode == VOLUME) m_action = VOLUME_UP;
			else m_action = SELECTION_NEXT;
			DEBUGLOG("UP");
			actionDelay.startDelay(1000);
			return;
		}
		if (touchLeftdetected) {
			if (m_mode == VOLUME) m_action = VOLUME_DOWN;
			else m_action = SELECTION_PREVIOUS;
			DEBUGLOG("DOWN");
			actionDelay.startDelay(1000);
			return;
		}
	}

	m_action = SELECTION_CHAIN;

	return ;

}


String ActionManager::toString(boolean bJson = false){
	String ss;
	if (bJson ==STD_TEXT) {
		ss = "ACTION["+String(m_action)+"] MODE["+String(m_mode)+"]";
	} else {
		ss = ss + "\"Json"+ "\":\""+ "Yes\"" ;
	}
	return ss;
}
