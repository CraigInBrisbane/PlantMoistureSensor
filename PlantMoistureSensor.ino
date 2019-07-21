#include "ArduinoDeviceLibraries/SoilSensor.h"
#include "ArduinoDeviceLibraries/FlashingLed.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH  128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)

// Create the display object.
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Configurable settings.
int   PIN_Sensor =        A0;     // PIN to which the Sensor Signal wire is connected.
int   PIN_Power =         6;      // PIN which we will power the sensor from. Not using 5V, to lessen corrosion and allow for power saving (Switch off and on)
int   PIN_WarnLED =       3;      // PIN to which the LED Indicator will connect. This will flash when the sensor is below a definded value.
bool  DebugMode =         false;   // If Debug is enabled, we will be logging data to the serial port.
int   PollingInterval =   5000;   // Time in milliseconds when the sensor will be polled for a reading.
int   LowLevelReading =   600;    // The low value which will enable the warning LED. i.e. The low value for "Plant needs water!"

// Define the Soil Sensor and variable for the last value.
SoilSensor                sensor;
FlashingLed               led;
int SensorValue =         0;
bool IsWarningState =     false;


void setup() {

  if(DebugMode)
    Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }  
  display.clearDisplay();

  for(int i=0; i< 64; i++) {
    display.clearDisplay();
    display.drawPixel(64-i, 16, WHITE);
    display.drawPixel(64+i, 16, WHITE);
    display.display();
  }

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 5);
  display.println("Sensor:");
  display.setCursor(10, 20);
  display.println("Power: ");
  display.setCursor(85, 5);
  display.println("LED: ");

  display.setCursor(55, 5);
  display.println(PIN_Sensor);
  display.setCursor(55, 20);
  display.println(PIN_Power);
  display.setCursor(115, 5);
  display.println(PIN_WarnLED);

  
  display.display();  
  delay(500); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  led.Init(PIN_WarnLED, 100, 5000);
  sensor.Init(PIN_Sensor, PIN_Power, PollingInterval);
  sensor.SetDebugMode(DebugMode);
  
  // Setup the indicator LED.
  pinMode(PIN_WarnLED, OUTPUT);

  // Packet Soil was 355
  // Jeremy was 570 to 590, with nearly enough water.
 
}

void loop() {

  led.Update();
  // Check the sensor value.
  int newVal = sensor.Update();
  
  if(newVal != -1) { // Sensor returns -1 if it thinks it doesn't need to read yet, or isn't setup.
    if(DebugMode) {
      Serial.print("Recieved value from sensor: ");
      Serial.println(newVal);
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(48, 15);
    // Display static text
    display.println(newVal);
    
    display.setTextSize(1);
    display.setCursor(105,1);
    display.println(LowLevelReading);

    if(newVal != SensorValue) {
      SensorValue = newVal;
    
      // Are we entering a warning state?    
      if(SensorValue <= LowLevelReading && IsWarningState == false) {
        if(DebugMode) {
          Serial.println("Low level detected. Enabling Warning LED");
        }
        IsWarningState = true;
        led.On();
      }
    
      // Are we exiting a warning state?    
      if(SensorValue > LowLevelReading && IsWarningState) {    
        if(DebugMode) { 
          Serial.println("Low level no longer detected. Disabling Warning LED");
        }
        IsWarningState=false;
        led.Off();
      }   
    }
    
    if(IsWarningState) {  
      display.setTextSize(1);
      display.setCursor(1,1);
      display.println("Warning!");   
    }
    led.Update();
    display.display(); 
  }
}
