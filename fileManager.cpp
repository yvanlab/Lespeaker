#include "fileManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



String FileManager::readCfgType(File *file, const char *type) {
	while (file->available() != 0) {
		//A inconsistent line length may lead to heap memory fragmentation
		String l_line = file->readStringUntil('\n');
		int8_t pos = l_line.indexOf(type);
		//DEBUGLOGF("pos %s,%d\n",type,pos);
		if (pos == 1) {
			return l_line.substring(pos + sizeof(type), l_line.length() - 1);
		}
		if (!l_line.startsWith(" ")) {
			return "";
		}
	}
	return "";
}

String FileManager::readCfg(const char*period, const char *type) {

	File file = SD.open("/cfg.txt", FILE_READ); // @suppress("Abstract class cannot be instantiated")
	if (!file) {
		DEBUGLOG("CDFG failed");
		return "";
	}

	String res;

	while (file.available() != 0) {
		//A inconsistent line length may lead to heap memory fragmentation
		String l_line = file.readStringUntil('\n');
		//DEBUGLOGF("  > %s\n",l_line.c_str());
		if (l_line.startsWith(period)) {
			//DEBUGLOGF("period %s found\n",period);
			res = readCfgType(&file, type);
			break;
		}
	}

	file.close();
	//m_currentFoler = res;
	DEBUGLOGF("CFG[%s] \n",res.c_str());
	return res;
}

void FileManager::printDirectory(File dir, int numTabs) {
	while (true) {

		File entry = dir.openNextFile(); // @suppress("Abstract class cannot be instantiated")
		if (!entry) {
			// no more files
			//Serial.println("fin");
			break;
		}
		for (uint8_t i = 0; i < numTabs; i++) {
			Serial.print('\t');
		}
		Serial.print(entry.name());
		if (entry.isDirectory()) {
			Serial.println("/");
			printDirectory(entry, numTabs + 1);
		} else {
			// files have sizes, directories do not
			Serial.print("\t\t");
			Serial.println(entry.size(), DEC);
		}
		entry.close();
	}
}

String FileManager::getPreviousFile() {
	uint8_t index = 0;
	if (m_currentIndex > 1)
		index = m_currentIndex - 1;
	else
		index = 0;

	String previousFile = getFileIndex( index).c_str();
	return /*m_currentFoler + */previousFile;

}

String FileManager::getNextFile() {
	return  getFileIndex( m_currentIndex + 1).c_str();
}

String FileManager::getFile() {
	return getFileIndex( m_currentIndex).c_str();

}

bool FileManager::loadMusicIndex(String folder) {
	File f = SD.open(folder+"/musicIndex.txt");
	if (!f) {
		DEBUGLOGF("LMI[%s][%s] failed\n",folder.c_str(),"musicIndex.txt");
		m_currentIndex = 0;
		return false;
	}
	String l_line= f.readStringUntil('\n');
	DEBUGLOGF("LMI[%s]\n",l_line.c_str());
	m_currentIndex = l_line.toInt();
	f.close();
	DEBUGLOGF("LMI[%d]\n",m_currentIndex);
	return true;
}

bool FileManager::writeMusicIndex(String folder){
	File f = SD.open(folder+"/musicIndex.txt",FILE_WRITE);
	if (!f) {
		DEBUGLOGF("WMI[%s][%s] not found\n",m_currentFoler.c_str(),"/musicIndex.txt");
		return false;
	}
	String strToWrite = String(m_currentIndex);// + "\n";
	f.print(strToWrite);
	//f.write((const uint8_t*)strToWrite.c_str(), strToWrite.length());
	f.close();
	return true;

}

bool FileManager::loadPlayList(FileManager::PERIOD_TYPE period, FileManager::CONFIG_TYPE type){


	if (m_currentPeriod == period && m_currentType == type) {
		DEBUGLOGF("Not need to reload\n");
		return true;
	}

	DEBUGLOGF("TYPE \n");
	DEBUGLOGF("LPL [%s] [%s]\n",type_name[type],preriod_name[period]);
	String folder = readCfg(preriod_name[period], type_name[type]);
	bool res;
	if (type == FileManager::CONFIG_RADIO) {
		DEBUGLOGF("LPLr [%s] [%s]\n",folder.c_str(),"radio.txt");
		res = loadFromFile(folder+String("/radio.txt"));
	}else{
		DEBUGLOGF("LPLf [%s]\n",folder.c_str());
		res = loadFromFolder(folder);
	}
	if (res) {
		loadMusicIndex(folder);
		m_currentFoler = folder;
		m_currentType = type;
		m_currentPeriod = period;
	}
	return res;
}

bool FileManager::loadFromFile(String folderFile) {
	File file = SD.open(folderFile);
	if (!file) {
		DEBUGLOGF("LFFi [%s] failed\n",folderFile.c_str());
		return false;
	}
	m_fileRepo.clean();
	while (file.available() != 0) {
		String l_line = file.readStringUntil('\n');
		l_line.replace("\n","");
		l_line.replace("\r","");
		m_fileRepo.add(l_line);
		DEBUGLOGF("LFFi > %s\n",l_line.c_str());
	}

	file.close();
	return true;

}

bool FileManager::loadFromFolder(String folder) {
	//m_currentFoler = currentFolder;
	//load all folder in memory
	File f = SD.open(folder);
	if (!f) {
		DEBUGLOGF("LFF[%s] failed\n",folder);
		return false;
	}
	f.rewindDirectory();
	//uint8_t currentIndex = 0;
	File entry;
	String fileName;

	//clean array
	m_fileRepo.clean();

	while ((entry = f.openNextFile()) == true) {
		fileName = entry.name();
		entry.close();
		//is it an MP3 ?
		DEBUGLOGF("LFF[%s]",fileName.c_str());
		if (fileName.indexOf(".mp3")>0 || fileName.indexOf(".MP3")>0) {
			m_fileRepo.add(fileName);
			DEBUGLOG(":added");
		}else
			DEBUGLOG("");
		//currentIndex++;
	}
	return true;

}

String FileManager::getFileIndex(uint8_t nextFileIndex) {
	/*if (m_indexArray == 0)
		return "";*/
	if (m_fileRepo.isEmpty())
		return "";

	uint8_t fileIndex = nextFileIndex;
	DEBUGLOGF("GNF:i[%d] s[%d]\n",fileIndex,m_fileRepo.size());
	if (nextFileIndex >= m_fileRepo.size()) {
		fileIndex = 0;
		DEBUGLOGF("GNF:First\n");
	}
	m_currentIndex = fileIndex;
	DEBUGLOGF("GNF[%d][%s]\n",m_currentIndex,m_fileRepo.get(fileIndex));
	writeMusicIndex(m_currentFoler);
	return m_fileRepo.get(fileIndex);

}



void FileManager::begin() {
	DEBUGLOG("SD initiatization start");
	if (!SD.begin()) {
		DEBUGLOG("SD initiatization failed. Retrying.");
		delay(200);
		while (!SD.begin()) {
			DEBUGLOG("SD initiatization failed. Retrying.");
			delay(200);
		}
	}

	DEBUGLOG("SD Initialized.");

#ifdef MCPOC_TEST
	File root = SD.open("/");
	printDirectory(root, 0);
	root.close();
#endif

	//DEBUGLOGF("  res matin/url [%s]\n",readCfg("matin", "url").c_str()); DEBUGLOGF("  res matin/ane [%s]\n",readCfg("matin", "ane").c_str()); DEBUGLOGF("  res matin/msc [%s]\n",readCfg("matin", "msi").c_str()); DEBUGLOGF("  res soir/url  [%s]\n",readCfg("soir", "url").c_str());

	/*String floder = "/soir/msi";	//readCfg("matin", "ane");
	setCurrentFolder(floder);
	DEBUGLOGF(" %d:%s\n", 0, getNextFile(0).c_str()) ;
	DEBUGLOGF(" %d:%s\n", 1, getNextFile( 1).c_str()) ;
	DEBUGLOGF(" %d:%s\n", 2, getNextFile( 2).c_str()) ;
	DEBUGLOGF(" %d:%s\n", 8, getNextFile( 8).c_str()) ;*/

}
