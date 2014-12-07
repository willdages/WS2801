Adafruit_WS2801
======

A WS2801 Library for the Spark Core (Originally written by Adafruit)

## History

This library originated from Adafruit as a [WS2801 Arduino Library](https://github.com/adafruit/Adafruit-WS2801-Library) with a BSD license. It was then ported over to the Spark Core by "Technobly / Bdub" according to the note at the top of the library. It exists in a few forms and I wasn't able to track down the original source of the port. The original version may be here [in this gist](https://gist.github.com/technobly/8339548) but it wasn't the version I started with.

I took [this version](https://github.com/kwyjibo089/SparkWeatherMoodlight/blob/master/Arduino/moodlight.ino) from Roman Mueller's [Weather Moodlight tutorial](http://blog.roman-mueller.ch/index.php/2014/03/13/a-weather-moodlight/) and split it out into this file structure so it could be included as a library in the Spark IDE.

I wrote very little of this code (barely touched the WS2801.h and WS2801.cpp files), and modified Roman's application to work for my application (mainly this means stripping out a bunch of functions I didn't have any use for).

## License

I'm a little confused actually. The original work created by Adafruit mentions the BSD license in their README, but doesn't include a license file. It does however mention needing to include a block of copy in any redistributions, so I have included those in all 3 code files in `/firmware`. In the WS2801.cpp file, it mentions the MIT license. Per [this article](http://en.wikipedia.org/wiki/BSD_licenses), there are 6 different BSD licenses, so I went with the MIT license for this project because there's only one. If anyone would like to clarify how I should be handling the license for this, I will be receptive and responsive to make appropriate changes.
