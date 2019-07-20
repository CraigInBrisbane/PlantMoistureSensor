#include "ArduinoDeviceLibraries/SoilSensor.h"

int PIN_Sensor =      A0;
int PIN_Power =       7;
int PIN_WarnLED =     3;
int readValue =       0;

SoilSensor sensor;

void setup() {
  
  Serial.begin(9600);
  
  // Setup PIN Modes.

  sensor.Init(PIN_Sensor, PIN_Power, 1000);
  sensor.SetDebugMode(true);
  pinMode(PIN_Sensor, INPUT);
  pinMode(PIN_Power, OUTPUT);
  pinMode(PIN_WarnLED, OUTPUT);

  // Packet Soil was 355
  // Jeremy was 570 to 590, with nearly enough water.
 
}

void loop() {
  // put your main code here, to run repeatedly:
  int newVal = sensor.Update();
  Serial.print("*");
  if(newVal != readValue) {
    readValue = newVal;
    Serial.println("");
    Serial.println(readValue);  
  }
  
}
