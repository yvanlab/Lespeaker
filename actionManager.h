

#ifndef ActionManager_h
#define ActionManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#include "FlashLed.h"

#else

#include "WProgram.h"

#endif

#include "delayHelper.h"
#include "touchHelper.h"
#include "presenceHelper.h"
#include "baseManager.h"

extern FlashLed				*flLedSystem;

class ActionManager : public BaseManager
{

public:

	enum SPEAKER_ACTION {ACTION_NONE=0, VOLUME_UP=1,VOLUME_DOWN=2,SELECTION_CHAIN=3,SELECTION_NEXT=4,SELECTION_PREVIOUS=5,CHANGE_SOURCE=6, SWITH_OFF=7,WAKE_UP=8,STOPPED=9};
	enum SPEAKER_MODE {MODE_NONE=0,MODE_VOLUME=1, MODE_SELECTION=2, MODE_LAST=3};
	enum SPEAKER_SOURCE {SOURCE_NONE=0, SOURCE_RADIO=1,SOURCE_MICROSD=2, SOURCE_LAST = 3};

	ActionManager(uint8_t pinLed,SPEAKER_MODE mode, SPEAKER_SOURCE souce);

	void handle(bool _someOneHere);

	SPEAKER_ACTION getAction() {
		return m_action;
	}

	void setActionForced(SPEAKER_ACTION action) {

		if (action == SPEAKER_ACTION::WAKE_UP) {
			m_presence.forceStatus(true);
		} else if (action == SPEAKER_ACTION::SWITH_OFF) {
			m_presence.forceStatus(false);
		} else
			m_actionForced = action;
	}

	SPEAKER_MODE getMode() {
		return m_mode;
	}

	void setModeForce(SPEAKER_MODE mode) {
		m_modeForced = mode;
	}

	boolean isModeChanged() {
		return m_previousMode != m_mode;
	}

	void  setSourceForce(SPEAKER_SOURCE source ) {
		m_sourceForced = source;
	}

	SPEAKER_SOURCE getSource() {
		return m_source;
	}

	boolean isSourceChanged() {
		return m_previousSource != m_source;
	}

	void setRedFlash(boolean activated) {
		if (activated) {
			flLedSystem->startLed( 12/*LED_RED_PIN*/, 2);
			flLedSystem->startFlashLed(200);
		} else {
			flLedSystem->stopLed();

		}
		//DEBUGLOGF("Presence detected [%d]\n",millis());
	}



	String getClassName(){return "ActionManager";}
	String toString(boolean bJson);

	SPEAKER_MODE m_modeForced = MODE_NONE;
	SPEAKER_MODE m_mode = MODE_VOLUME;
	SPEAKER_MODE m_previousMode = MODE_NONE;

	SPEAKER_ACTION m_actionForced = ACTION_NONE;
	SPEAKER_ACTION m_action = ACTION_NONE;
	SPEAKER_ACTION m_previousAction = ACTION_NONE;

	SPEAKER_SOURCE m_sourceForced = SOURCE_NONE;
	SPEAKER_SOURCE m_source = SOURCE_NONE;
	SPEAKER_SOURCE m_previousSource= SOURCE_NONE;

	TouchHelper  m_touch;
	PresenceHelper m_presence;

	DelayHelper modeDelay;
	DelayHelper actionDelay;
	DelayHelper switchOnOffDelay;
	bool m_bForeceStopStatus = false;
};

#endif
