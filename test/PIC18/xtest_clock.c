#include "unity.h"
#include "mock_timers.h"
#include "p18f4520.h"
#include "Clock.h"

void setUp(void){}
void tearDown(void){}

void test_hasTimer0Overflowed_given_not_yet_overflwed_should_return_0(){
  INTCONbits.TMR0IF = 0;
  TEST_ASSERT_FALSE(hasTimer0Overflowed());
}

void test_hasTimer0Overflowed_given_has_overflowed_should_return_1(){
  INTCONbits.TMR0IF = 1;
  TEST_ASSERT_TRUE(hasTimer0Overflowed());
}
