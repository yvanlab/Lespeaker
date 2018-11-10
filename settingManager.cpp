

#include "SettingManager.h"
#include "actionManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

SettingManager::SettingManager(unsigned char pinLed) : BaseSettingManager(pinLed){

}

unsigned char SettingManager::readData(){
  BaseSettingManager::readData();
  switchOn();
  volume = readEEPROM();
  if (volume>30) volume  = 10;

  source = readEEPROM();
  if (source>=ActionManager::SOURCE_LAST || source==ActionManager::SOURCE_NONE) source = ActionManager::SOURCE_MICROSD;

  mode = readEEPROM();
  if (mode>=ActionManager::MODE_LAST || mode>=ActionManager::MODE_NONE) mode = ActionManager::MODE_VOLUME;
  switchOff();
  return m_iEEprom;
}
unsigned char SettingManager::writeData(){
  BaseSettingManager::writeData();
  switchOn();
  writeEEPROM(volume);
  writeEEPROM(source);
  writeEEPROM(mode);
  EEPROM.commit();
  switchOff();
  return m_iEEprom;
}

String SettingManager:: toString(boolean bJson = false){
  String ss;
  if (bJson ==STD_TEXT) {
    ss = BaseSettingManager::toString(bJson);
    ss = ss + "source ["+String(source) + "] mode ["+String(mode)+"] volume["+ String(volume)+"]";
  } else {
    ss = ss + "\"volume\":\""+ String(volume) + "\"," ;
    ss = ss + "\"mode\":\""+ String(mode) + "\"," ;
    ss = ss + "\"source\":\""+ String(source) + "\"" ;
  }
  return ss;
}
