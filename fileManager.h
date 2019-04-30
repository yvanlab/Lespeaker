

#ifndef FileManager_h
#define FileManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif
#include <SD.h>
#include "BaseManager.h"

class ArrayHelper {
public:
	char *m_filesNameArray[100];
	uint8_t m_indexArray = 0;
	void clean() {
		for (uint8_t i = 0; i < m_indexArray; i++)
			free(m_filesNameArray[i]);
		m_indexArray = 0;
	};

	void add(String str) {
		char * buf = (char *) malloc(str.length() + 1);
		str.toCharArray(buf, str.length() + 1);
		m_filesNameArray[m_indexArray] = buf;
		m_indexArray++;
		//DEBUGLOGF("AHA[%d]\n",m_indexArray);
	}

	char *get(uint8_t index) {
		if (index < m_indexArray)
			return m_filesNameArray[index];
		return NULL;
	}

	bool isEmpty() {
		return m_indexArray == 0;
	}

	uint8_t size() {
		return m_indexArray;
	}

};


class FileManager : public BaseManager
{
  public:
	 const char ane[4] = "ane";
	 const char msi[4] = "msi";
	 const char url[4] = "url";
	 const char soir[5] = "soir";
	 const char matin[6] = "matin";
	 const char entre[6] = "entre";

	const char * const type_name[3]   = {ane,msi,url};
	const char * const preriod_name[3]   = {matin,soir,entre};

	enum CONFIG_TYPE {CONFIG_ANE=0, CONFIG_MSI=1, CONFIG_RADIO=2, CONFIG_NOT_INIT=3};
	enum PERIOD_TYPE {PERIOD_MATIN=0, PERIOD_SOIR=1, PERIOD_ENTRE=2};

	FileManager(unsigned char pinLed): BaseManager(pinLed){};

	String readCfg(const char*period, const char *type);
	String readCfgType(File *file, const char *type);



	void begin();

	void printDirectory(File dir, int numTabs);
	bool loadPlayList(FileManager::PERIOD_TYPE period, FileManager::CONFIG_TYPE type);
	bool loadFromFolder(String folder);
	bool loadFromFile(String folderFile);

	bool loadMusicIndex(String folder);
	bool writeMusicIndex(String folder);

	String getFileIndex(uint8_t nextFileIndex);
	String getNextFile();
	String getFile();
	String getPreviousFile();

	String getClassName(){return "FileManager";};

    String m_currentFoler = "";
    uint8_t m_currentIndex = 0;

    ArrayHelper m_fileRepo;

    FileManager::PERIOD_TYPE m_currentPeriod = PERIOD_MATIN;
	FileManager::CONFIG_TYPE m_currentType =CONFIG_NOT_INIT;


};

#endif
