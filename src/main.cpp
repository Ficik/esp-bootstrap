#include "../config.h"
#include <Wifi.h>
#include <Webserver.h>
#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    wifiSetup();
    webserverSetup();
}

void loop() {
    webserverLoop();
}

