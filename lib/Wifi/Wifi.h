#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include "../../config.h"


void printStatus(int status);
void connectToWifi();
void wifiSetup();
void wifiLoop();