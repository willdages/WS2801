/* ========================== Application.cpp =========================== */

#include "application.h"
#include "WS2801/WS2801.h"

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels on the Spark Core!
  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683
  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
*****************************************************************************/

// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!

// SPARK CORE SPI PINOUTS
// http://docs.spark.io/#/firmware/communication-spi
// A5 (MOSI) Yellow wire on Adafruit Pixels
// A3 (SCK) Green wire on Adafruit Pixels

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply$

const int numPixel = 25;

// Set the argument to the NUMBER of pixels.
Adafruit_WS2801 strip = Adafruit_WS2801(numPixel);

// For 36mm LED pixels: these pixels internally represent color in a
// different format.  Either of the above constructors can accept an
// optional extra parameter: WS2801_RGB is 'conventional' RGB order
// WS2801_GRB is the GRB order required by the 36mm pixels.  Other
// than this parameter, your code does not need to do anything different;
// the library will handle the format change.  Example:
//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);


String http_get(const char* hostname, String path);

int led = D7;
long previousMillis = 0;
long interval = 5*60*1000;

TCPClient client;
char buffer[512];

void setup() {

    Serial.begin(115200);

    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);

    Spark.function("color", setColor);
    Spark.function("pixel", setPixel);
    Spark.function("wipe", wipe);

    strip.begin();

    // Update LED contents, to start they are all 'off'
    strip.show();

}

void loop() {

}

int setColor(String command)
{
    // format is [RRR,GGG,BBB]
    // ie red is [255,000,000]
    int red = command.substring(1,4).toInt();
    int green = command.substring(5,8).toInt();
    int blue = command.substring(9,12).toInt();

    colorWipe(Color(red, green, blue), 50);

    return red+green+blue;
}

int setPixel(String command)
{
    // format is XX,[RRR,GGG,BBB]
    // ie 1st red is 00,[255,000,000]
    int pixel = command.substring(0,2).toInt();

    int red = command.substring(4,7).toInt();
    int green = command.substring(9,12).toInt();
    int blue = command.substring(14,17).toInt();

    strip.setPixelColor(pixel,red,green,blue);
    strip.show();

    return pixel+red+green+blue;
}

// fill the dots one after the other with said color
int wipe(String command) {
    // format is [RRR,GGG,BBB]
    // ie 1st red is [255,000,000]
    int red = command.substring(1,4).toInt();
    int green = command.substring(5,8).toInt();
    int blue = command.substring(9,12).toInt();
    int i;

    for (i=0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, red, green, blue);
        strip.show();
        delay(50);
    }
}


void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
