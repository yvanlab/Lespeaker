#include "fileManager.h"

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

	File file = SD.open("/cfg.txt", FILE_READ);
	if (!file) {
		DEBUGLOG("open failed");
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
	m_currentFoler = res;
	DEBUGLOGF("Current folder [%s] \n",m_currentFoler.c_str());
	return res;
}

void FileManager::printDirectory(File dir, int numTabs) {
	while (true) {

		File entry = dir.openNextFile();
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

	String previousFile = getNextFile( index).c_str();
	return /*m_currentFoler + */previousFile;

}

String FileManager::getNextFile() {

	String nextFile =
			getNextFile( m_currentIndex + 1).c_str();
	return /*m_currentFoler + */nextFile;

}

bool FileManager::loadMusicIndex() {
	File f = SD.open(m_currentFoler+"/musicIndex.txt");
	if (!f) {
		DEBUGLOGF("Folder [%s] not found\n",m_currentFoler+"/musicIndex.txt");
		m_currentIndex = 0;
		return false;
	}
	String l_line= f.readStringUntil('\n');
	/*Serial.print("Read from file: ");
    while(f.available()){
    	char c = f.read();
    	Serial.print(c );
    	l_line += c;
    }*/
	DEBUGLOGF("Line read [%s]\n",l_line.c_str());
	m_currentIndex = l_line.toInt();
	f.close();
	DEBUGLOGF("Index read [%d]\n",m_currentIndex);
	return true;
}

bool FileManager::writeMusicIndex(){
	File f = SD.open(m_currentFoler+"/musicIndex.txt",FILE_WRITE);
	if (!f) {
		DEBUGLOGF("Folder [%s] not found\n",m_currentFoler+"/musicIndex.txt");
		return false;
	}
	String strToWrite = String(m_currentIndex);// + "\n";
	f.print(strToWrite);
	//f.write((const uint8_t*)strToWrite.c_str(), strToWrite.length());
	f.close();
	return true;

}

bool FileManager::setCurrentFolder(String currentFolder) {
	m_currentFoler = currentFolder;
	//load all folder in memory
	File f = SD.open(currentFolder);
	if (!f) {
		DEBUGLOGF("Folder [%s] not found\n",currentFolder);
		return false;
	}
	f.rewindDirectory();
	uint8_t currentIndex = 0;
	File entry;
	String fileName;

	//clean array
	for (uint8_t i = 0; i < m_indexArray; i++)
		free(m_filesNameArray[i]);
	m_indexArray = 0;

	while (entry = f.openNextFile()) {
		fileName = entry.name();
		entry.close();
		DEBUGLOG(fileName);
		//is it an MP3 ?
		if (fileName.indexOf(".mp3")) {
			char * buf = (char *) malloc(fileName.length() + 1);
			fileName.toCharArray(buf, fileName.length() + 1);
			m_filesNameArray[m_indexArray] = buf;
			m_indexArray++;
		}

		currentIndex++;
	}
	loadMusicIndex();
}

String FileManager::getNextFile(uint8_t nextFileIndex) {
	if (m_indexArray == 0)
		return "";

	uint8_t fileIndex = nextFileIndex;
	if (nextFileIndex >= m_indexArray) {
		fileIndex = 0;
		DEBUGLOGF("Go back to first\n");
	}
	m_currentIndex = fileIndex;
	DEBUGLOGF("Next indes[%d]\n",m_currentIndex);
	writeMusicIndex();
	return m_filesNameArray[fileIndex];

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

	DEBUGLOGF("  res matin/url [%s]\n",readCfg("matin", "url").c_str()); DEBUGLOGF("  res matin/ane [%s]\n",readCfg("matin", "ane").c_str()); DEBUGLOGF("  res matin/msc [%s]\n",readCfg("matin", "msi").c_str()); DEBUGLOGF("  res soir/url  [%s]\n",readCfg("soir", "url").c_str());

	/*String floder = "/soir/msi";	//readCfg("matin", "ane");
	setCurrentFolder(floder);
	DEBUGLOGF(" %d:%s\n", 0, getNextFile(0).c_str()) ;
	DEBUGLOGF(" %d:%s\n", 1, getNextFile( 1).c_str()) ;
	DEBUGLOGF(" %d:%s\n", 2, getNextFile( 2).c_str()) ;
	DEBUGLOGF(" %d:%s\n", 8, getNextFile( 8).c_str()) ;*/

}
