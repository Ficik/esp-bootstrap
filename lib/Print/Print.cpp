#include "Print.h"

void printToSerial(char* message){
    Serial.print(message);
}
void printToWebsocket(char* message);

void printToSerial(String message){
    Serial.print(message);
}
void printToWebsocket(String message);


void print(char* message);
void print(String message);