

#include "SettingManager.h"

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
  gain = readEEPROM();
  readEEPROM(input,3);
  switchOff();
  return m_iEEprom;
}
unsigned char SettingManager::writeData(){
  BaseSettingManager::writeData();
  switchOn();
  writeEEPROM(gain);
  writeEEPROM(input);
  EEPROM.commit();
  switchOff();
  return m_iEEprom;
}

String SettingManager:: toString(boolean bJson = false){
  String ss;
  if (bJson ==STD_TEXT) {
    ss = BaseSettingManager::toString(bJson);
    ss = ss + "input ["+String(input) + "] gain["+ String(gain)+"]";
  } else {
    ss = ss + "\"gain\":\""+ String(gain) + "\"," ;
  }
  return ss;
}
