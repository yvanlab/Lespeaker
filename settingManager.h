

#ifndef SettingManager_h
#define SettingManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#include <EEPROM.h>
#include <BaseManager.h>
#include <BaseSettingManager.h>

class SettingManager : public BaseSettingManager
{
  public:

    SettingManager(unsigned char pinLed);
    unsigned char readData();
    unsigned char writeData();

    String getClassName(){return "SettingManager";}
    String toString(boolean bJson);
    int8_t gain;

};

#endif
