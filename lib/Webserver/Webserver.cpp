#include "Webserver.h"
#include "websites.h"

ESP8266WebServer server(80);

void webserverSetup() {
    server.onNotFound(handleNotFound);
    server.on("/info", handleInfo);
    server.begin();
}


void webserverLoop() {
     server.handleClient();
}


void handleInfo() {
   String message = "{\n";
   message += "\"FreeHeap\": \"" + String(ESP.getFreeHeap()) + "\",\n";
   message += "\"ChipID\": \"" + String(ESP.getChipId()) + "\",\n";
   message += "\"FlashChipId\": \"" + String(ESP.getFlashChipId()) + "\",\n";
   message += "\"FlashChipSize\": \"" + String(ESP.getFlashChipSize()) + "\",\n";
   message += "\"CycleCount\": \"" + String(ESP.getCycleCount()) + "\"\n";
   message += "}";
  server.send(200, "application/json", message);
}


void handleNotFound() {

  // try to find the file in the flash
  if(loadFromFlash(server.uri())) return;

  String message = "File Not Found\n\n";
  message += "URI..........: ";
  message += server.uri();
  message += "\nMethod.....: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments..: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  message += "\n";
  message += "FreeHeap.....: " + String(ESP.getFreeHeap()) + "\n";
  message += "ChipID.......: " + String(ESP.getChipId()) + "\n";
  message += "FlashChipId..: " + String(ESP.getFlashChipId()) + "\n";
  message += "FlashChipSize: " + String(ESP.getFlashChipSize()) + " bytes\n";
  message += "getCycleCount: " + String(ESP.getCycleCount()) + " Cycles\n";
  message += "Milliseconds.: " + String(millis()) + " Milliseconds\n";
  server.send(404, "text/plain", message);
}


bool loadFromFlash(String path) {
  if(path.endsWith("/")) path += "index.html";

  int NumFiles = sizeof(files)/sizeof(struct t_websitefiles);

  for(int i=0; i<NumFiles; i++) {
    if(path.endsWith(String(files[i].filename))) {
      _FLASH_ARRAY<uint8_t>* filecontent;
      String dataType = "text/plain";
      unsigned int len = 0;

      dataType = files[i].mime;
      len = files[i].len;

      server.sendHeader("Content-Encoding", "gzip");
      server.setContentLength(len);
      server.send(200, files[i].mime, "");

      filecontent = (_FLASH_ARRAY<uint8_t>*)files[i].content;

      filecontent->open();

      WiFiClient client = server.client();
      client.write(*filecontent, 100);

      return true;
    }
  }

  return false;
}