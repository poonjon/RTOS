#ifndef LEDFSM_H
#define LEDFSM_H

typedef enum{
	LED_START,
  LED_OFF,
	LED_ON
}LEDState;

typedef struct LEDData LEDData;
struct LEDData{
  LEDState state;
  unsigned long currentClock;
};

void LEDFSM(LEDData *data);
void LEDInit(LEDData *data);
#endif // LEDFSM_H
