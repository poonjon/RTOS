#include "unity.h"
#include "LEDFSM.h"
#include "mock_Clock.h"
#include "Blinky.h"
#include "p18f4520.h"

void setUp(void){}
void tearDown(void){}

void test_LED_START_should_set_state_to_led_to_OFF(void){
  LEDData data = {.state = LED_START, .currentClock = 0};
  
  LEDFSM(&data);
  
  TEST_ASSERT_EQUAL(LED_OFF, data.state);
}

void test_LED_OFF_should_stay_in_off_state(void){
  LEDData data = {.state = LED_OFF, .currentClock = 0};
	getClock_ExpectAndReturn(0);
  
  LEDFSM(&data);
  TEST_ASSERT_EQUAL(LED_OFF, data.state);
}

void test_LED_OFF_should_stay_in_on_state(void){
	LEDData data = {.state = LED_OFF, .currentClock = 0};
	getClock_ExpectAndReturn(489);
  getClock_ExpectAndReturn(489);
  
  LEDFSM(&data);
  TEST_ASSERT_EQUAL(LED_ON, data.state);
}

void test_LED_ON_should_stay_in_on_state(void){
	LEDData data = {.state = LED_ON, .currentClock = 0};
	getClock_ExpectAndReturn(0);
  
  LEDFSM(&data);
  TEST_ASSERT_EQUAL(LED_ON, data.state);
}

void test_LED_ON_should_transit_to_off_state(void){
	LEDData data = {.state = LED_ON, .currentClock = 0};
	getClock_ExpectAndReturn(489);
	getClock_ExpectAndReturn(489);
  
  LEDFSM(&data);
  TEST_ASSERT_EQUAL(LED_OFF, data.state);
}
