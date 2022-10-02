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
#define LED_COUNT 30

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 255  // Set BRIGHTNESS to about 1/5 (max = 255)

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

float noise = 500;            // var for storing output of microphone
float threshold = 50;        // loudness mic must pass before lights turn on
float sensitivity = 1;        // a multiplier for threshold which will on the fly modify its value
float background = 1024 / 2;  // dead mic signal is vsource/2 analog val max is 1024
float activity = 0;
long randomColor = 0;

void setup() {

  strip.begin();                    // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();                     // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);  //0 - 255?
  Serial.begin(9600);
}

void loop() {

  // for adafruit microphone the value of a quite room is 510 noise = analogRead(micPin);  // 0-1023 range of values on arduino 0-4096 for pi pico
  noise = analogRead(micPin);
  activity = abs(noise-background);
while (activity > threshold)               // while the mic is picking up the drum
{
  //strip.setBrightness(abs(noise - background) * 255);
  //strip.rainbow(0, 1, 255, 150, true);
  randomColor = random(0,65535);
  for(int i =0; i<LED_COUNT ;i++)
  { 
  strip.setPixelColor(i,strip.ColorHSV(randomColor,255,255));

  }
  
  strip.show();
  
  Serial.print("\threshold\t");
  Serial.print(threshold);
  Serial.print("\tabs noise - background\t ");
  Serial.println( activity);
  noise = analogRead(micPin);
  activity = abs(noise-background);
  delay(1000);
}
// Serial.print("noise\t");
//   Serial.print(noise);
//   Serial.print("\tabs noise - background\t ");
//   Serial.println( abs(noise-background));
 
  Serial.print("\threshold\t");
  Serial.print(threshold);
  Serial.print("\tabs noise - background\t ");
  Serial.println( abs(noise-background));
strip.fill(0, 0, 0);
strip.show();
























  // //sensitivity = analogRead(sensitivityPin);
  // sensitivity = 600;
  // int length = LED_COUNT*((noise-500)/1024)+3;
  // strip.updateLength(length);

  // if (noise > background + threshold || noise <background - threshold) {

  //   strip.setBrightness((noise/4096*255)-noise);//for pi pico
  //   strip.rainbow(0, 1, 255, 150, true);
  //   strip.show();



  //   delay(200);
  //   strip.updateLength(LED_COUNT);
  //   strip.fill(0, 0, 0);  // turn the strip off for next go thru of loop
  //   strip.show();
  // }
  // else {
  //   strip.updateLength(LED_COUNT);
  //   strip.fill(0, 0, 0);  // turn the strip off for next go thru of loop
  //   strip.show();
  // }
  // //if below threshold do not light up

  // Serial.print("noise\t");
  // Serial.print(noise);
  // Serial.print("\tsensitivity\t");
  // Serial.print(sensitivity);
  // Serial.print("\t number of leds\t");
  // Serial.println(length);
}
// the end