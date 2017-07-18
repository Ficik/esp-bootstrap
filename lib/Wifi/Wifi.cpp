#include "Wifi.h"

void printStatus() {
    switch (WiFi.status()) {
        case WL_CONNECTED:
            Serial.println("Connected");
            break;
        case WL_NO_SHIELD:
            Serial.println("No Shield");
            break;
        case WL_IDLE_STATUS:
            Serial.println("Idle");
            break;
        case WL_NO_SSID_AVAIL:
            Serial.println("No ssid avail");
            break;
        case WL_SCAN_COMPLETED:
            Serial.println("Scan completed");
            break;
        case WL_CONNECT_FAILED:
            Serial.println("Connect failed");
            break;
        case WL_CONNECTION_LOST:
            Serial.println("Connection lost");
            break;
        case WL_DISCONNECTED:
            Serial.println("Disconected");
            break;
        default:
            Serial.println("Unknown");
    }
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.println(" dBm");
  }
}

void connectToWifi() {
    listNetworks();
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("Connecting to ");
        Serial.print(WIFI_SSID);
        Serial.print(" : ");
        Serial.println(WIFI_PASS);
        printStatus();
    }

    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    MDNS.begin(HOSTNAME);
    Serial.print("Hostname: ");
    Serial.println(HOSTNAME);
}

void wifiSetup() {
    connectToWifi();
}

void wifiLoop() {
    while (WiFi.status() != WL_CONNECTED) {
        connectToWifi();
    }
}