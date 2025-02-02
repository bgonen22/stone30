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
#define SPEED_FACTOR 4 // suppose to make the wave length
#define DELAY_BETWEEN_LEDS 0 // suppose to make the wave slower
#define TRACE_SIZE 3
#define TIME_ON_TOP 0.3 // the presentage time from 0.5 MAX till MAX
#define REVERSE 1 // define the direction of the trace
TLC_CHANNEL_TYPE channel;
int channels[] = {1, 2, 3, 4, 5, 6, 11, 12, 13, 14, 17, 18, 19, 20, 24, 25, 26, 27, 28, 29, 30};

int index;
void setup()
{
  Tlc.init();
 
}

void loop()
{
  if (tlc_fadeBufferSize < TRACE_SIZE /*TLC_FADE_BUFFER_LENGTH - 2*/) {
    if (!tlc_isFading(channel)) {
      uint16_t duration = analogRead(SPEED_PIN) * SPEED_FACTOR;
      int maxValue = analogRead(BRIGHTNESS_PIN) * 2;
      maxValue = map(maxValue, 0, 2046, 0, 4095);
      uint32_t startMillis = millis() + 50;
      uint32_t endMillis = startMillis + (1-TIME_ON_TOP)*duration;
      tlc_addFade(channel, 0, 0.5*maxValue, startMillis, endMillis );
      tlc_addFade(channel, 0.5*maxValue, maxValue, endMillis, endMillis +  TIME_ON_TOP*duration);
      tlc_addFade(channel, maxValue, 0.5*maxValue, endMillis + TIME_ON_TOP*duration, endMillis + 2*(TIME_ON_TOP*duration));
      tlc_addFade(channel, 0.5*maxValue, 0, endMillis + 2*(TIME_ON_TOP*duration), endMillis + (TIME_ON_TOP+1)*duration);
    }
    int arraySize = sizeof(channels) / sizeof(channels[0]);
    int maxi;
    int mini;
    if (REVERSE) {
      index --;
      maxi = -1;
      mini = arraySize;
    } else {
      index ++;
      maxi == arraySize;
      mini = 0;
    }
    if (index == maxi) { 
      index = mini;
    }
    channel = channels[index];
  }
  tlc_updateFades();
  delay(DELAY_BETWEEN_LEDS);
}
