

#ifndef FileManager_h
#define FileManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif
#include <SD.h>
#include "BaseManager.h"



class FileManager : public BaseManager
{
  public:

	FileManager(unsigned char pinLed): BaseManager(pinLed){

	}



	String readCfg(const char*period, const char *type);
	String readCfgType(File *file, const char *type);



	void begin();

	void printDirectory(File dir, int numTabs);
	bool setCurrentFolder(String currentFoler);
	bool loadMusicIndex();
	bool writeMusicIndex();

	String getNextFile(uint8_t nextFileIndex);
	String getNextFile();
	String getPreviousFile();

	String getClassName(){return "FileManager";}

    String m_currentFoler = "";
    uint8_t m_currentIndex = 0;


    char *m_filesNameArray[50];
    uint8_t m_indexArray = 0;

};

#endif
