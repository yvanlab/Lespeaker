#ifndef fileManagerUI_h
#define fileManagerUI_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#ifdef ESP32
#include <WebServer.h>
#include <esp_wifi.h>
//#include <HTTPUpdateServer.h>
#else
#include <ESP8266WebServer.h>
#endif

#include "basemanager.h"

class FileExplorerUI: public BaseManager {

public:
	FileExplorerUI(uint8_t pinLed, WebServer *server) : BaseManager (pinLed){
		_server = server;
	};

	void append_page_header();
	void append_page_footer();

	void File_Download();
	void File_Upload();
	void handleFileUpload();
	void HomePage();
	void SD_file_download(String filename);
	void SD_dir();
	String printDirectory(const char * dirname, uint8_t levels);
	void File_Stream();
	void SD_file_stream(String filename);
	void File_Delete();
	void SD_file_delete(String filename);
	void SendHTML_Header();
	void SendHTML_Content();
	void SendHTML_Stop();
	void SelectInput(String heading1, String command, String arg_calling_name);
	void ReportSDNotPresent();
	void ReportFileNotPresent(String target);
	void ReportCouldNotCreateFile(String target);
	String file_size(int bytes);


	String webpage;
	boolean SD_present = true;


	WebServer        *_server;
};

#endif
