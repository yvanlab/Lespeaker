

#include "actionManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


ActionManager::ActionManager(unsigned char pinLed,SPEAKER_MODE mode, SPEAKER_SOURCE souce) : BaseManager(pinLed){
	m_previousMode = MODE_NONE;
	m_mode = mode;
	m_previousSource = SOURCE_NONE;
	m_source = souce;
	DEBUGLOGF("Init Mode[%d] Source[%d]\n",mode, souce);
	/*NTP.onNTPSyncEvent(
				std::bind(&HourManager::NTPsyncEvent, this, std::placeholders::_1));*/
	m_presence.setCallback(std::bind(&ActionManager::setRedFlash, this,std::placeholders::_1));
	switchOnOffDelay.startDelay(10000);
	actionDelay.startDelay(10000);

}
//https://github.com/espressif/arduino-esp32/issues/814
void ActionManager::handle(bool _someOneHere) {

	m_touch.handle();
	m_presence.handle();

	bool touchRightFallingdetected	= m_touch.getTouchStat(TouchHelper::TOUCH_RIGHT)==TouchHelper::FALLING_EDGE;
	bool touchLeftFallingdetected	= m_touch.getTouchStat(TouchHelper::TOUCH_LEFT)==TouchHelper::FALLING_EDGE;
	bool touchCommandFallingdetected	= m_touch.getTouchStat(TouchHelper::TOUCH_COMMAND)==TouchHelper::FALLING_EDGE;


	bool touchRightRisingdetected	= m_touch.getTouchStat(TouchHelper::TOUCH_RIGHT)==TouchHelper::RISING_EDGE;
	bool touchLeftRisingdetected	= m_touch.getTouchStat(TouchHelper::TOUCH_LEFT)==TouchHelper::RISING_EDGE;
	bool touchCommandRisingdetected	= m_touch.getTouchStat(TouchHelper::TOUCH_COMMAND)==TouchHelper::RISING_EDGE;

	bool touchRightLongdetected		= m_touch.getTouchStat(TouchHelper::TOUCH_RIGHT)==TouchHelper::SELECTED_LONG;
	bool touchLeftLongdetected		= m_touch.getTouchStat(TouchHelper::TOUCH_LEFT)==TouchHelper::SELECTED_LONG;
	bool touchCommandLongdetected	= m_touch.getTouchStat(TouchHelper::TOUCH_COMMAND)==TouchHelper::SELECTED_LONG;


	m_previousAction = m_action;
	m_previousMode = m_mode;
	m_previousSource = m_source;


	bool someOneHere;
	if (!_someOneHere)
		someOneHere = _someOneHere;
	else
		someOneHere		= m_presence.isPresence();

	/*if (touchCommandLongdetected && switchOnOffDelay.isDone() )  {
		m_bForeceStopStatus  ^= true;
		switchOnOffDelay.startDelay(5000);
	}*/

	if (m_sourceForced != SOURCE_NONE) {
		m_source = m_sourceForced;
		m_sourceForced  = SOURCE_NONE;
	} else if (touchCommandFallingdetected && switchOnOffDelay.isDone() )  {
		switchOnOffDelay.startDelay(5000);
		DEBUGLOGF("source av[%d]\n", m_source);
		if (m_source == SOURCE_NONE || m_source == SOURCE_RADIO ) m_source = SOURCE_MICROSD;
		else m_source = SOURCE_RADIO;
		DEBUGLOGF("source ap[%d]\n", m_source);
	}

	if (m_actionForced != ACTION_NONE) {
		m_action = m_actionForced;
		m_actionForced = ACTION_NONE;
		return;
	}

	if (!someOneHere || m_bForeceStopStatus){
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



	if (m_modeForced != MODE_NONE){
		 m_mode = m_modeForced;
		 m_modeForced  = MODE_NONE;
		 DEBUGLOGF("Mode Forced [%d]\n", m_mode);
		 return;
	} else if ( (touchRightRisingdetected && touchLeftRisingdetected) && modeDelay.isDone() ){
		if (m_mode == MODE_VOLUME) m_mode = MODE_SELECTION;
		else m_mode = MODE_VOLUME;
		DEBUGLOGF("Mode[%d]\n", m_mode);
		modeDelay.startDelay(2000);
		return;
	}
	if ( (touchRightRisingdetected && touchLeftRisingdetected))
		actionDelay.startDelay(500);


	if (actionDelay.isDone()) {
		if (touchRightFallingdetected ) {
			if (m_mode == MODE_VOLUME) m_action = VOLUME_UP;
			else m_action = SELECTION_NEXT;
			DEBUGLOG("UP");
		//	actionDelay.startDelay(1000);
			return;
		}
		if (touchLeftFallingdetected) {
			if (m_mode == MODE_VOLUME) m_action = VOLUME_DOWN;
			else m_action = SELECTION_PREVIOUS;
			DEBUGLOG("DOWN");
			//actionDelay.startDelay(1000);
			return;
		}
	}

	m_action = SELECTION_CHAIN;

	return ;

}


String ActionManager::toString(boolean bJson = false){
	String ss;
	if (bJson ==STD_TEXT) {
		ss = "ACTION["+String(m_action)+"] MODE["+String(m_mode)+"]SOURCE["+String(m_source)+"]";;
	} else {
		ss = ss + "\"Json"+ "\":\""+ "Yes\"" ;
	}
	return ss;
}
