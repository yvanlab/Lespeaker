
#include "main.h"

#include "FileExplorerUI.h"


// All supporting functions from here...
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const char HTML[] PROGMEM =
		"<!DOCTYPE html>\n<html>\n<head>\n<meta http-equiv=\"content-type\"\n\tcontent=\"text/html; charset=windows-1252\">\n<title>lespeaker</title>\n<script type=\"application/x-javascript\"></script>\n</head>\n<body>\n\t<h1 style=\"text-align: center;\">\n\t\t<span id=\"modulename\">Module</span> configuration\n\t</h1>\n\t<div style=\"text-align: center;\">\n\t\t<p>\n\t\t\tVersion : <span id=\"version\">3.0</span>\n\t\t</p>\n\t</div>\n\t<div style=\"text-align: center;\">\n\t\t<p>\n\t\t\tDate build : <span id=\"builddate\">10/08/1900</span>\n\t\t</p>\n\t</div>\n\t<div style=\"text-align: center;\">\n\t\t<p>\n\t\t\tUp time : <span id=\"uptime\">un moment</span>\n\t\t</p>\n\t</div>\n\t<div style=\"text-align: center;\">\n\t\t<p>\n\t\t\t<a href='/'>Parametres</a>\n\t\t</p>\n\t</div>\n\t<hr\n\t\tstyle=\"margin-top: 51px; margin-left: auto; width: 177px; margin-right: auto;\">\n\n\t<div>\n\t\t<div>\n\t\t\t<b> Repertoire: </b> [<span id=\"rep\">/rep/autre</span>] \n\t\t\t\t<input type=\"button\" value=\"back\" id=\"id_back\">\n\t\t\t<hr>\n\t\t\t<input type=\"button\" value=\"Effacer\" id=\"id_del\">\n\t\t\t<input type=\"button\" value=\"play\" id=\"id_play\">\n\t\t\t\n\t\t\t<hr>\n\t\t\t<FORM action=\"upload\" method=\"POST\" enctype=\"multipart/form-data\">\n\t\t\t\t<input type=\"file\" name=\"my_file[]\" multiple id=\"id_file\"> \n\t\t\t\t<input type=\"submit\" value=\"Upload\" value=\"submit\" id=\"submit\"> \n\t\t\t\t<input type=\"reset\" value=\"Clear Form\"><br>\n\t\t\t</FORM>\n\t\t\t<hr>\n\t\t\t<p>\n\t\t\t\t<i><b><span id=\"lstFiles\">Files</span></b></i>\n\t\t\t</p>\n\t\t</div>\n\t</div>\n</body>\n<script type=\"text/javascript\">\n\tfunction deleteFiles(folder) {\n\n\t\tvar t = document.getElementById(\"lf\");\n\t\tvar trs = t.getElementsByTagName(\"tr\");\n\t\tvar tds = null;\n\n\t\t\n\t\tvar xhttp = new XMLHttpRequest();\n\t\txhttp.onreadystatechange = function() {\n\t\t\tif (this.readyState == 4 && this.status == 200) {\n\t\t\t\tvar txt = tds[1].innerHTML;\n\t\t\t\ttds[1].innerHTML = txt.fontcolor(\"green\").strike();\n\t\t\t\tc[0].checked = false;\n\t\t\t\tc[0].disabled=true;\t\t\t\t\n\t\t\t};\n\t\t};\n\t\t\n\t\tfor (var i = 0; i < trs.length; i++) {\n\t\t\ttds = trs[i].getElementsByTagName(\"td\");\n\t\t\tvar c = tds[0].getElementsByTagName(\"input\");\n\t\t\tif (c.length > 0) {\n\t\t\t\tif (c[0].checked == true) {\n\t\t\t\t\tdocument.getElementById(\"version\").innerHTML = buildPath(\n\t\t\t\t\t\t\tfolder, tds[1].innerText);\n\t\t\t\t\txhttp.open(\"GET\", \"del?del=\"\n\t\t\t\t\t\t\t+ buildPath(folder, tds[1].innerText), false);\n\t\t\t\t\txhttp.send();\n\t\t\t\t};\n\t\t\t};\n\t\t};\n\n\t};\n\t\n\t\n\tfunction playFile(folder) {\n\n\t\tvar t = document.getElementById(\"lf\");\n\t\tvar trs = t.getElementsByTagName(\"tr\");\n\t\tvar tds = null;\n\n\t\t\n\t\tvar xhttp = new XMLHttpRequest();\n\t\txhttp.onreadystatechange = function() {\n\t\t\tif (this.readyState == 4 && this.status == 200) {\n\t\t\t\ttds[1].innerHTML = txt.fontcolor(\"bleue\")\n\t\t\t\tc[0].checked = false;\n\t\t\t\tc[0].disabled=true;\t\t\t\t\n\t\t\t};\n\t\t};\n\t\t\n\t\tfor (var i = 0; i < trs.length; i++) {\n\t\t\ttds = trs[i].getElementsByTagName(\"td\");\n\t\t\tvar c = tds[0].getElementsByTagName(\"input\");\n\t\t\tif (c.length > 0) {\n\t\t\t\tif (c[0].checked == true) {\n\t\t\t\t\tdocument.getElementById(\"version\").innerHTML = buildPath(\n\t\t\t\t\t\t\tfolder, tds[1].innerText);\n\t\t\t\t\txhttp.open(\"GET\", \"play?file=\"\n\t\t\t\t\t\t\t+ buildPath(folder, tds[1].innerText), false);\n\t\t\t\t\txhttp.send();\n\t\t\t\t\tbreak;\n\t\t\t\t};\n\t\t\t};\n\t\t};\n\t};\n\n\tfunction buildPath(folder, name) {\n\t\t/*if (name ==null){\n\t\t\treturn folder;\n\t\t}*/\n\t\tif (folder == '/') {\n\t\t\treturn '/' + name;\n\t\t} else  {\n\t\t\treturn folder + '/' + name;\n\t\t};\n\t}\n\n\tfunction nextfolder(name, folder) {\n\n\t\tvar xhttp = new XMLHttpRequest();\n\t\txhttp.onreadystatechange = function() {\n\t\t\tif (this.readyState == 4 && this.status == 200) {\n\t\t\t\tupdate(this.responseText);\n\n\t\t\t};\n\t\t};\n\t\tdocument.getElementById(\"id_back\").onclick = function() {\n\t\t\tvar res = folder.split(\"/\");\n\t\t\tname = res[res.length-1];\n\t\t\tnextfolder(name,folder.replace(name,\"\"));\n\t\t};\n\t\t\n\t\tdocument.getElementById(\"version\").innerHTML = buildPath(folder, name);\n\t\txhttp.open(\"GET\", \"dir?dir=\" + buildPath(folder, name), true);\n\t\txhttp.send();\n\t};\n\n\tfunction update(responseText) {\n\t\tvar myObj = JSON.parse(responseText);\n\t\tvar res = \"<tbody>\";\n\t\tfor (i in myObj.files) {\n\t\t\tf = myObj.files[i];\n\t\t\tif (f.type == 'F') {\n\t\t\t\tres += '<tr><td> <input id=\"chk\"  type=\"checkbox\"></td><td>'\n\t\t\t\t\t\t+ f.name + '</td><td>' + f.size + '</td></tr>';\n\t\t\t} else {\n\t\t\t\tvar tmp = '<tr><td></td>' + '<td onclick=\"nextfolder(\\'' + f.name\n\t\t\t\t+ '\\',\\'' + myObj.folder + '\\')\"> [' + f.name\n\t\t\t\t+ ']  </td>' + '<td>' + f.size + '</td></tr>';\n\t\t\t\tres += tmp;\n\n\t\t\t};\n\t\t};\n\t\tdocument.getElementById(\"lstFiles\").innerHTML = '<table style=\"width: 100%\" border=\"1\" id=\"lf\"><tbody>'\n\t\t\t\t+ res + '</tbody></table>';\n\n\t\tdocument.getElementById(\"rep\").innerHTML = myObj.folder;\n\t\t\t\t\t\n\t\tdocument.getElementById(\"id_del\").onclick = function() {\n\t\t\tdeleteFiles(myObj.folder);\n\t\t};\n\t\t\t\n\t\tdocument.getElementById(\"id_play\").onclick = function() {\n\t\t\tplayFile(myObj.folder);\n\t\t};\n\n\t}\n\n\tfunction init() {\n\t\tvar xhttp = new XMLHttpRequest();\n\t\txhttp.onreadystatechange = function() {\n\t\t\tif (this.readyState == 4 && this.status == 200) {\n\t\t\t\tupdate(this.responseText);\n\t\t\t};\n\t\t};\n\t\txhttp.open(\"GET\", \"dir\", true);\n\t\txhttp.send();\n\t}\n\twindow.onload = init;\n</script>\n</html>\n"
		;
void FileExplorerUI::HomePage(){
	flLedSystem->startLed( LED_RED_PIN, 2);
	DEBUGLOG("dataPage");
	wifiMger->getServer()->send ( 200, "text/html", HTML );
	flLedSystem->stopLed();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*void FileExplorerUI::File_Download(){ // This gets called twice, the first pass selects the input, the second pass then processes the command line arguments
  if (_server->args() > 0 ) { // Arguments were received
    if (_server->hasArg("download")) SD_file_download(_server->arg(0));
  }
  else SelectInput("Enter filename to download","download","download");
}*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*void FileExplorerUI::SD_file_download(String filename){
  if (SD_present) {
    File download = SD.open("/"+filename);
    if (download) {
      _server->sendHeader("Content-Type", "text/text");
      _server->sendHeader("Content-Disposition", "attachment; filename="+filename);
      _server->sendHeader("Connection", "close");
      _server->streamFile(download, "application/octet-stream");
      download.close();
    } else ReportFileNotPresent("download");
  } else ReportSDNotPresent();
}*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*void FileExplorerUI::File_Upload(){
  Serial.println("File upload stage-1");
  append_page_header();
  webpage += F("<h3>Select File to Upload</h3>");
  webpage += F("<FORM action='/fupload' method='post' enctype='multipart/form-data'>");
  webpage += F("<input class='buttons' style='width:40%' type='file' name='fupload' id = 'fupload' value=''><br>");
  webpage += F("<br><button class='buttons' style='width:10%' type='submit'>Upload File</button><br>");
  webpage += F("<a href='/'>[Back]</a><br><br>");
  append_page_footer();
  Serial.println("File upload stage-2");
  _server->send(200, "text/html",webpage);
}*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File UploadFile;
void FileExplorerUI::handleFileUpload(){ // upload a new file to the Filing system
  flLedSystem->startLed( LED_RED_PIN, 2);
  Serial.println("File upload stage-3");
  HTTPUpload& uploadfile = _server->upload(); // See https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer/srcv
                                           // For further information on 'status' structure, there are other reasons such as a failed transfer that could be used

  if(uploadfile.status == UPLOAD_FILE_START)
  {
    Serial.println("File upload stage-4");
    DEBUGLOGF("Uri : [%s]\n",_server->uri().c_str());

    for (int i = 0; i<_server->args();i++){
    	DEBUGLOGF("Arg : [%s][%s]\n",_server->argName(i).c_str(),_server->arg(i).c_str()) ;
    }

    String rep = _currentDirectory;
     String filename;
     DEBUGLOGF("Directpry : [%s]\n",rep.c_str());
      if (!rep.endsWith("/")) {
    	  filename = rep + "/" + uploadfile.filename;
      } else {
    	  filename = rep + uploadfile.filename;
      }

    //if(!filename.startsWith("/")) filename = "/"+filename;
    Serial.print("Upload File Name: "); Serial.println(filename);
    SD.remove(filename);                         // Remove a previous version, otherwise data is appended the file again
    UploadFile = SD.open(filename, FILE_WRITE);  // Open the file for writing in SPIFFS (create it, if doesn't exist)
    filename = String();
  }
  else if (uploadfile.status == UPLOAD_FILE_WRITE)
  {
    Serial.println("File upload stage-5");
    if(UploadFile) UploadFile.write(uploadfile.buf, uploadfile.currentSize); // Write the received bytes to the file
  }
  else if (uploadfile.status == UPLOAD_FILE_END)
  {
    if(UploadFile)          // If the file was successfully created
    {
      UploadFile.close();   // Close the file again
      Serial.print("Upload Size: "); Serial.println(uploadfile.totalSize);
       _server->send(200,"text/html","");
    }
    /*else
    {
      ReportCouldNotCreateFile("upload");
    }*/
  }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SD_dir(){
  //if (SD_present) {
	  flLedSystem->startLed( LED_RED_PIN, 2);
	String str = _server->arg("dir");
	_currentDirectory = "/";
	if (str.length()==0) {
		_currentDirectory = "/";
	} else {
		_currentDirectory = str;
	}
	DEBUGLOGF("Directpry : [%s]\n",_currentDirectory.c_str());
	String files = printDirectory(_currentDirectory.c_str(),0);
	String res = "\"files\":["+ files + "],";
	res += "\"folder\":\""+ _currentDirectory + "\"";
	DEBUGLOGF("fodler : [%s]\n",res.c_str());
	_server->send(200,"text/html","{" + res + "}");
	//_server->sendContent("{" + res + "}");

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
 * "name":"file name"
 * "size":"20>Kb"
 * "type":"D/F"
 */

String FileExplorerUI::printDirectory(const char * dirname, uint8_t levels){
  File root = SD.open(dirname);
  #ifdef ESP8266
  root.rewindDirectory(); //Only needed for ESP8266
  #endif
  if(!root){
    return "";
  }
  if(!root.isDirectory()){
    return "";
  }
  String res;
  File file = root.openNextFile();
  while(file){
      //DEBUGLOG(String(file.isDirectory()?"Dir ":"File ")+String(file.name()));
	  String filename = file.name();
	  //String tmp =
	  DEBUGLOGF("Filename Dir[%s] ", filename.c_str());
	  filename.remove(0,filename.lastIndexOf('/')+1);
	  DEBUGLOGF("Filename [%s]\n", filename.c_str());
      res += "{\"name\":\""+filename +"\", \"size\":\"" + file_size(file.size()) + "\", \"type\":\"" + String(file.isDirectory()?"D":"F") + "\"}";
      file.close();
      file = root.openNextFile();
      if (file) res += ",";
  }
  return res;

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*void FileExplorerUI::File_Stream(){
  if (_server->args() > 0 ) { // Arguments were received
    if (_server->hasArg("stream")) SD_file_stream(_server->arg(0));
  }
  else SelectInput("Enter a File to Stream","stream","stream");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SD_file_stream(String filename) {
  if (SD_present) {
    File dataFile = SD.open("/"+filename, FILE_READ); // Now read data from SD Card
    Serial.print("Streaming file: "); Serial.println(filename);
    if (dataFile) {
      if (dataFile.available()) { // If data is available and present
        String dataType = "application/octet-stream";
        if (_server->streamFile(dataFile, dataType) != dataFile.size()) {Serial.print(F("Sent less data than expected!")); }
      }
      dataFile.close(); // close the file:
    } else ReportFileNotPresent("Cstream");
  } else ReportSDNotPresent();
}*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::File_Delete(){
	  flLedSystem->startLed( LED_RED_PIN, 2);
  if (_server->args() > 0 ) { // Arguments were received
    if (_server->hasArg("del")) SD_file_delete(_server->arg(0));
  }
  //else SelectInput("Select a File to Delete","delete","delete");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SD_file_delete(String filename) { // Delete the file
  if (SD_present) {
    //SendHTML_Header();
    File dataFile = SD.open("/"+filename, FILE_READ); // Now read data from SD Card
    Serial.print("Deleting file: "); Serial.println(filename);
    if (dataFile)
    {
      if (SD.remove("/"+filename)) {
        Serial.println(F("File deleted successfully"));
        /*webpage += "<h3>File '"+filename+"' has been erased</h3>";
        webpage += F("<a href='/delete'>[Back]</a><br><br>");*/
        _server->send(200,"text/html","");
      }
     /* else
      {
        webpage += F("<h3>File was not deleted - error</h3>");
        webpage += F("<a href='delete'>[Back]</a><br><br>");
      }*/
    } //else ReportFileNotPresent("delete");
   /* append_page_footer();
    SendHTML_Content();
    SendHTML_Stop();*/
  } //else ReportSDNotPresent();
}

String FileExplorerUI::file_size(int bytes){
  String fsize = "";
  if (bytes < 1024)                 fsize = String(bytes)+" B";
  else if(bytes < (1024*1024))      fsize = String(bytes/1024.0,3)+" KB";
  else if(bytes < (1024*1024*1024)) fsize = String(bytes/1024.0/1024.0,3)+" MB";
  else                              fsize = String(bytes/1024.0/1024.0/1024.0,3)+" GB";
  return fsize;
}
