/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#define timeSeconds 10
#include <FastLED.h>

#define DATA_PIN     4
#define NUM_LEDS    7
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
int MyArray[7] = {0,1,2,3,4,5,6}
CRGB leds[NUM_LEDS];
// Set GPIOs for LED and PIR Motion Sensor

const int motionSensor = 19;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;

// Checks if motion was detected, sets LED HIGH and starts a timer
void IRAM_ATTR detectsMovement() {
  leds[7] = CRGB(0, 255, 0)
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(motionSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // Set LED to LOW
  pinMode(leds, OUTPUT);
  digitalWrite(leds, LOW);
  
}

void loop() {
  // Current time
  now = millis();
  if((digitalRead(leds) == HIGH) && (motion == false)) {
    Serial.println("MOTION DETECTED!!!");
    motion = true;
  }
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("Motion stopped...");
    digitalWrite(leds, LOW);
    startTimer = false;
    motion = false;
  }
}