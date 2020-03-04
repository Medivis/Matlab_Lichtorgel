/*
Board: NodeMCU 1.0 (ESP-12F Module)
CPU Frequency: 80MHz
Flash: 4MB (3M SPIFFS)

Author: Niklas Schulz
*/

#include <Adafruit_NeoPixel.h>
#define PIN       D6
#define NUMPIXELS 60
#define BAUDRATE  921600

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin();
  pixels.clear();
  pixels.show();
  Serial.begin(BAUDRATE);
  Serial.println("Ready");
}

int RGBcounter = 0;
int LEDcounter = 0;
byte RGBbuffer[] = {0, 0, 0};
 
void loop() {
  if(Serial.available() > 0){
    // read data if available an write in buffer
    RGBbuffer[RGBcounter] = Serial.read();
    RGBcounter++;
    
    // flush if RGBbuffer ist full
    if(RGBcounter >=3){
      pixels.setPixelColor(LEDcounter, pixels.Color(RGBbuffer[0],RGBbuffer[1],RGBbuffer[2]));
      RGBcounter = 0;
      LEDcounter++;
    }

    // Show LED matrix if complete
    if(LEDcounter >=NUMPIXELS){
      LEDcounter = 0;
      pixels.show();
    }
    
  }
}
