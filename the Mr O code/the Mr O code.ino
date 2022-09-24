// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN 6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 8

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50  // Set BRIGHTNESS to about 1/5 (max = 255)

#define micPin A0          // pin the mic is on
#define sensitivityPin A1  // pot knob pin

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

float noise = 500;         // var for storing output of microphone
float threshold = 400;    // loudness mic must pass before lights turn on
float sensitivity = 1;  // a multiplier for threshold which will on the fly modify its value

void setup() {

  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();   // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
}

void loop() {


  noise = analogRead(micPin);  // 0-1023 range of values
  sensitivity = analogRead(sensitivityPin);
  
  if (noise > sensitivity ) {
    strip.rainbow(0, 1, 255, 150, true);
    strip.show();
 


    //delay(200);
  } 
  else {
    strip.fill(0, 0, 0);  // turn the strip off if its not loud enought
    strip.show();         // apply changes
  }
  //if below threshold do not light up

  Serial.print("noise\t");
  Serial.print(noise);
  Serial.print("\tsensitivity\t");
  Serial.println(sensitivity);
 

}
// the end