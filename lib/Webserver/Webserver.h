#include <ESP8266WebServer.h>


void webserverSetup();
void webserverLoop();
bool loadFromFlash(String path);
void handleNotFound();
void handleInfo();