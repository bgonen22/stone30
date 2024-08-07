/*
    Fades a line down the channels, with max value and duration based on
    the voltage of analog pin 0.
    Try grounding analog 0: everything should turn off.
    Try putting +5V into analog 0: everything should turn on.

    See the BasicUse example for hardware setup.

    Alex Leone <acleone ~AT~ gmail.com>, 2009-02-03 */

#include "SparkFun_Tlc5940.h"
#include "tlc_fades.h"
#define BRIGHTNESS_PIN 0 
#define SPEED_PIN 1
TLC_CHANNEL_TYPE channel;
int channels[] = {
    2, 3, 4, 5, 6, 7,       // 2 to 7
    12, 13, 14, 15,         // 12 to 15
    31, 30, 29, 28,         // 31 to 28 (reverse order)
    24, 23, 22, 21, 20, 19, 18 // 24 to 18 (reverse order)
};
int index;
void setup()
{
  Tlc.init();
 
}

void loop()
{
  if (tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH - 2) {
    if (!tlc_isFading(channel)) {
      uint16_t duration = analogRead(SPEED_PIN) * 2;
      int maxValue = analogRead(BRIGHTNESS_PIN) * 2;
      uint32_t startMillis = millis() + 50;
      uint32_t endMillis = startMillis + duration;
      tlc_addFade(channel, 0, maxValue, startMillis, endMillis);
      tlc_addFade(channel, maxValue, 0, endMillis, endMillis + duration);
    }
    int arraySize = sizeof(channels) / sizeof(channels[0]);
    if (index++ == arraySize) { 
      index = 0;
    }
    channel = channels[index];
  }
  tlc_updateFades();
}