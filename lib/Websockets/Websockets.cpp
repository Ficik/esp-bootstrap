#include "Websockets.h"

void setup() {
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop() {
     webSocket.loop();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                webSocket.sendTXT(num, "Connected");
            }
            break;
        case WStype_TEXT:
            webSocket.broadcastTXT("message here");
            break;
        case WStype_BIN:
            break;
    }

}