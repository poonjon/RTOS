#include "unity.h"
#include "Led2.h"
#include "Blinky.h"
#include "mock_Clock.h"
#include "Tasking.h"
#include "p18f4520.h"
void setUp(void){}
void tearDown(void){}

void test_testingSM(void){
	Led2Data led2Data = {.state = 0, .ledStatus = 1};
  printf("1)\n");
  testingLed2SM(&led2Data);
  printf("2)\n");
  testingLed2SM(&led2Data);
  printf("3)\n");
}

void xtest_led2sm_should_turn_on_led(){
  Led2Data led2Data = {.ledStatus = LED_UNKNOWNSTATE, .currentClock = 0};
  getClock_ExpectAndReturn(489);
  getClock_ExpectAndReturn(489);
  getClock_ExpectAndReturn(500);
  getClock_ExpectAndReturn(1000);
  getClock_ExpectAndReturn(1000);
  initTasking(&led2Data);
  
  led2SM(&led2Data);
  TEST_ASSERT_EQUAL(LED_ON, led2Data.ledStatus);
  
  led2SM(&led2Data);
  TEST_ASSERT_EQUAL(LED_OFF, led2Data.ledStatus);
}
