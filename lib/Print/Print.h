#include <Arduino.h>

void printToSerial(char* message);
void printToWebsocket(char* message);

void printToSerial(String message);
void printToWebsocket(String message);


void print(char* message);
void print(String message);