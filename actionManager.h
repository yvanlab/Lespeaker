

#ifndef ActionManager_h
#define ActionManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#include "delayHelper.h"
#include "touchHelper.h"
#include "baseManager.h"

class ActionManager : public BaseManager
{

public:

	enum SPEAKER_ACTION {ACTION_NONE, VOLUME_UP,VOLUME_DOWN,SELECTION_CHAIN,SELECTION_NEXT,SELECTION_PREVIOUS,SWITH_OFF,WAKE_UP,STOPPED};
	enum SPEAKER_MODE {VOLUME, SELECTION};

	ActionManager(uint8_t pinLed);

	void handle(bool _someOneHere);

	SPEAKER_ACTION getAction() {
		return m_action;
	}

	String getClassName(){return "ActionManager";}
	String toString(boolean bJson);

	SPEAKER_MODE m_mode = SELECTION;
	SPEAKER_ACTION m_action = ACTION_NONE;
	TouchHelper  m_touch;
	DelayHelper modeDelay;
	DelayHelper actionDelay;
};

#endif
