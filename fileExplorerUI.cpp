
#include "main.h"

#include "FileExplorerUI.h"


void FileExplorerUI::append_page_header() {
  webpage  = F("<!DOCTYPE html><html>");
  webpage += F("<head>");
  webpage += F("<title>File Server</title>"); // NOTE: 1em = 16px
  webpage += F("<meta name='viewport' content='user-scalable=yes,initial-scale=1.0,width=device-width'>");
  webpage += F("<style>");
  webpage += F("body{max-width:65%;margin:0 auto;font-family:arial;font-size:105%;text-align:center;color:blue;background-color:#F7F2Fd;}");
  webpage += F("ul{list-style-type:none;margin:0.1em;padding:0;border-radius:0.375em;overflow:hidden;background-color:#dcade6;font-size:1em;}");
  webpage += F("li{float:left;border-radius:0.375em;border-right:0.06em solid #bbb;}last-child {border-right:none;font-size:85%}");
  webpage += F("li a{display: block;border-radius:0.375em;padding:0.44em 0.44em;text-decoration:none;font-size:85%}");
  webpage += F("li a:hover{background-color:#EAE3EA;border-radius:0.375em;font-size:85%}");
  webpage += F("section {font-size:0.88em;}");
  webpage += F("h1{color:white;border-radius:0.5em;font-size:1em;padding:0.2em 0.2em;background:#558ED5;}");
  webpage += F("h2{color:orange;font-size:1.0em;}");
  webpage += F("h3{font-size:0.8em;}");
  webpage += F("table{font-family:arial,sans-serif;font-size:0.9em;border-collapse:collapse;width:85%;}");
  webpage += F("th,td {border:0.06em solid #dddddd;text-align:left;padding:0.3em;border-bottom:0.06em solid #dddddd;}");
  webpage += F("tr:nth-child(odd) {background-color:#eeeeee;}");
  webpage += F(".rcorners_n {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:20%;color:white;font-size:75%;}");
  webpage += F(".rcorners_m {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:50%;color:white;font-size:75%;}");
  webpage += F(".rcorners_w {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:70%;color:white;font-size:75%;}");
  webpage += F(".column{float:left;width:50%;height:45%;}");
  webpage += F(".row:after{content:'';display:table;clear:both;}");
  webpage += F("*{box-sizing:border-box;}");
  webpage += F("footer{background-color:#eedfff; text-align:center;padding:0.3em 0.3em;border-radius:0.375em;font-size:60%;}");
  webpage += F("button{border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:20%;color:white;font-size:130%;}");
  webpage += F(".buttons {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:15%;color:white;font-size:80%;}");
  webpage += F(".buttonsm{border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:9%; color:white;font-size:70%;}");
  webpage += F(".buttonm {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:15%;color:white;font-size:70%;}");
  webpage += F(".buttonw {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:40%;color:white;font-size:70%;}");
  webpage += F("a{font-size:75%;}");
  webpage += F("p{font-size:75%;}");
  webpage += F("</style></head><body><h1>File Server 1.0");
  webpage += "</h1>";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::append_page_footer(){ // Saves repeating many lines of code for HTML page footers
  webpage += F("<ul>");
  webpage += F("<li><a href='/'>Home</a></li>"); // Lower Menu bar command entries
  webpage += F("<li><a href='/download'>Download</a></li>");
  webpage += F("<li><a href='/upload'>Upload</a></li>");
  webpage += F("<li><a href='/stream'>Stream</a></li>");
  webpage += F("<li><a href='/delete'>Delete</a></li>");
  webpage += F("<li><a href='/dir'>Directory</a></li>");
  webpage += F("</ul>");
  webpage += "<footer>&copy;"+String(char(byte(0x40>>1)))+String(char(byte(0x88>>1)))+String(char(byte(0x5c>>1)))+String(char(byte(0x98>>1)))+String(char(byte(0x5c>>1)));
  webpage += String(char((0x84>>1)))+String(char(byte(0xd2>>1)))+String(char(0xe4>>1))+String(char(0xc8>>1))+String(char(byte(0x40>>1)));
  webpage += String(char(byte(0x64/2)))+String(char(byte(0x60>>1)))+String(char(byte(0x62>>1)))+String(char(0x70>>1))+"</footer>";
  webpage += F("</body></html>");
}
// All supporting functions from here...
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const char HTML[] PROGMEM ="<!DOCTYPE html><html><head><meta http-equiv=\"content-type\"content=\"text/html; charset=windows-1252\"><title>lespeaker</title><script type=\"application/x-javascript\"></script></head><body><h1 style=\"text-align: center;\"><span id=\"modulename\">Module</span> configuration</h1><div style=\"text-align: center;\"><p>Version : <span id=\"version\">3.0</span></p></div><div style=\"text-align: center;\"><p>Date build : <span id=\"builddate\">10/08/1900</span></p></div><div style=\"text-align: center;\"><p>Up time : <span id=\"uptime\">un moment</span></p></div><hrstyle=\"margin-top: 51px; margin-left: auto; width: 177px; margin-right: auto;\"><div><div><h3 style=\"height: 3px;\">Repertoire:[<span id=\"rep\">/rep/autre</span>]</h3><input id=\"id_del\" value=\"Effacer\" type=\"button\"> <inputid=\"id_load\" value=\"Importer\" type=\"button\"><FORM ACTION=upload METHOD=\"POST\" ENCTYPE=\"multipart/form-data\"><input type=\"file\" name=\"my_file[]\" multiple> <INPUTTYPE=\"submit\" VALUE=\"BLAST!\" NAME=\"submit\" ID=\"submit\"> <inputtype=\"reset\" value=\"Clear Form\"><br></FORM><hr><p><i><b><span id=\"lstFiles\">Files</span></b></i></p></div></div></body><script>function deleteFiles(folder){var xhttp=new XMLHttpRequest();xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){//update(this.responseText)/*window.alert(this.responseText);*/init;}}var t=document.getElementById(\"lf\");var trs=t.getElementsByTagName(\"tr\");var tds=null;for (var i=0; i < trs.length; i++){tds=trs[i].getElementsByTagName(\"td\");var c=tds[0].getElementsByTagName(\"input\");if (c.length > 0){if (c[0].checked==true){document.getElementById(\"version\").innerHTML=buildPath(folder, tds[1].innerText);xhttp.open(\"GET\", \"del?del=\"+ buildPath(folder, tds[1].innerText), true);xhttp.send();}}}};function buildPath(folder, name){if (folder=='/')return '/' + name;elsereturn folder + '/' + name;}function nextfolder(name, folder){var xhttp=new XMLHttpRequest();xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){update(this.responseText)/*window.alert(this.responseText);*/}};document.getElementById(\"version\").innerHTML=buildPath(folder, name);xhttp.open(\"GET\", \"dir?dir=\" + buildPath(folder, name), true);xhttp.send();};function update(responseText){var myObj=JSON.parse(responseText);var res=\"<tbody>\"for (i in myObj.files){f=myObj.files[i];if (f.type=='F')res +='<tr><td> <input id=\"chk\" type=\"checkbox\"></td><td>'+ f.name + '</td><td>' + f.size + '</td></tr>'elseres +='<tr><td></td>' + '<td onclick=\"nextfolder('' + f.name+ '','' + myObj.folder + '')\"> [' + f.name+ '] </td>' + '<td>' + f.size + '</td></tr>'}document.getElementById(\"lstFiles\").innerHTML='<table style=\"width: 100%\" border=\"1\" id=\"lf\"><tbody>'+ res + '</tbody></table>'document.getElementById(\"rep\").innerHTML=myObj.folderdocument.getElementById(\"id_del\").onclick=function(){deleteFiles(myObj.folder)}//document.getElementById(\"id_load\").onclick=uploadFiles('''+myObj.folder+''')}function init(){var xhttp=new XMLHttpRequest();xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){update(this.responseText)}};xhttp.open(\"GET\", \"dir\", true);xhttp.send();}window.onload=init;</script></html>";

void FileExplorerUI::HomePage(){
	flLedSystem->startLed( LED_RED_PIN, 2);
	DEBUGLOG("dataPage");
	wifiMger->getServer()->send ( 200, "text/html", HTML );
	flLedSystem->stopLed();

	/*SendHTML_Header();
  webpage += F("<a href='/download'><button>Download</button></a>");
  webpage += F("<a href='/upload'><button>Upload</button></a>");
  webpage += F("<a href='/stream'><button>Stream</button></a>");
  webpage += F("<a href='/delete'><button>Delete</button></a>");
  webpage += F("<a href='/dir'><button>Directory</button></a>");
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop(); // Stop is needed because no content length was sent*/
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::File_Download(){ // This gets called twice, the first pass selects the input, the second pass then processes the command line arguments
  if (_server->args() > 0 ) { // Arguments were received
    if (_server->hasArg("download")) SD_file_download(_server->arg(0));
  }
  else SelectInput("Enter filename to download","download","download");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SD_file_download(String filename){
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
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::File_Upload(){
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
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File UploadFile;
void FileExplorerUI::handleFileUpload(){ // upload a new file to the Filing system
  Serial.println("File upload stage-3");
  HTTPUpload& uploadfile = _server->upload(); // See https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer/srcv
                                            // For further information on 'status' structure, there are other reasons such as a failed transfer that could be used
  if(uploadfile.status == UPLOAD_FILE_START)
  {
    Serial.println("File upload stage-4");
    String filename = uploadfile.filename;
    if(!filename.startsWith("/")) filename = "/"+filename;
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
      webpage = "";
      append_page_header();
      webpage += F("<h3>File was successfully uploaded</h3>");
      webpage += F("<h2>Uploaded File Name: "); webpage += uploadfile.filename+"</h2>";
      webpage += F("<h2>File Size: "); webpage += file_size(uploadfile.totalSize) + "</h2><br>";
      append_page_footer();
      _server->send(200,"text/html",webpage);
    }
    else
    {
      ReportCouldNotCreateFile("upload");
    }
  }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SD_dir(){
  //if (SD_present) {
	String str = _server->arg("dir");
	String dir = "/";
	if (str.length()>0) {
		dir += str;
	}
	DEBUGLOGF("Directpry : [%s]",dir.c_str());
	String files = printDirectory(dir.c_str(),0);
	String res = "\"files\":["+ files + "],";
	res += "\"folder\":\""+ dir + "\"";
	DEBUGLOGF("fodler : [%s]\n",res.c_str());
	_server->sendContent("{" + res + "}");

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
void FileExplorerUI::File_Stream(){
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
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::File_Delete(){
  if (_server->args() > 0 ) { // Arguments were received
    if (_server->hasArg("del")) SD_file_delete(_server->arg(0));
  }
  else SelectInput("Select a File to Delete","delete","delete");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SD_file_delete(String filename) { // Delete the file
  if (SD_present) {
    SendHTML_Header();
    File dataFile = SD.open("/"+filename, FILE_READ); // Now read data from SD Card
    Serial.print("Deleting file: "); Serial.println(filename);
    if (dataFile)
    {
      if (SD.remove("/"+filename)) {
        Serial.println(F("File deleted successfully"));
        webpage += "<h3>File '"+filename+"' has been erased</h3>";
        webpage += F("<a href='/delete'>[Back]</a><br><br>");
      }
      else
      {
        webpage += F("<h3>File was not deleted - error</h3>");
        webpage += F("<a href='delete'>[Back]</a><br><br>");
      }
    } else ReportFileNotPresent("delete");
    append_page_footer();
    SendHTML_Content();
    SendHTML_Stop();
  } else ReportSDNotPresent();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SendHTML_Header(){
  _server->sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  _server->sendHeader("Pragma", "no-cache");
  _server->sendHeader("Expires", "-1");
  _server->setContentLength(CONTENT_LENGTH_UNKNOWN);
  _server->send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  append_page_header();
  _server->sendContent(webpage);
  webpage = "";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SendHTML_Content(){
  _server->sendContent(webpage);
  webpage = "";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SendHTML_Stop(){
  _server->sendContent("");
  _server->client().stop(); // Stop is needed because no content length was sent
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::SelectInput(String heading1, String command, String arg_calling_name){
  SendHTML_Header();
  webpage += F("<h3>"); webpage += heading1 + "</h3>";
  webpage += F("<FORM action='/"); webpage += command + "' method='post'>"; // Must match the calling argument e.g. '/chart' calls '/chart' after selection but with arguments!
  webpage += F("<input type='text' name='"); webpage += arg_calling_name; webpage += F("' value=''><br>");
  webpage += F("<type='submit' name='"); webpage += arg_calling_name; webpage += F("' value=''><br><br>");
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::ReportSDNotPresent(){
  SendHTML_Header();
  webpage += F("<h3>No SD Card present</h3>");
  webpage += F("<a href='/'>[Back]</a><br><br>");
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::ReportFileNotPresent(String target){
  SendHTML_Header();
  webpage += F("<h3>File does not exist</h3>");
  webpage += F("<a href='/"); webpage += target + "'>[Back]</a><br><br>";
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FileExplorerUI::ReportCouldNotCreateFile(String target){
  SendHTML_Header();
  webpage += F("<h3>Could Not Create Uploaded File (write-protected?)</h3>");
  webpage += F("<a href='/"); webpage += target + "'>[Back]</a><br><br>";
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
String FileExplorerUI::file_size(int bytes){
  String fsize = "";
  if (bytes < 1024)                 fsize = String(bytes)+" B";
  else if(bytes < (1024*1024))      fsize = String(bytes/1024.0,3)+" KB";
  else if(bytes < (1024*1024*1024)) fsize = String(bytes/1024.0/1024.0,3)+" MB";
  else                              fsize = String(bytes/1024.0/1024.0/1024.0,3)+" GB";
  return fsize;
}
