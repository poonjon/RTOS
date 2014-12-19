#include "unity.h"
#include "p18f4520.h"
#include "mock_spi.h"
#include "sevenSegment.h"
#include "mock_Clock.h"
void setUp(){}
void tearDown(){}

void test_startSPI(){
  SPIData data = {.state = WAIT};

  startSPI(&data);
  TEST_ASSERT_EQUAL(0, SPI_START);
}

void test_sevenSegmentSM_init_will_change_state_to_wait(){
  SPIData data = {.state = SPI_START, .sevenData = 0xee, .currentClock = 0};
  getClock_ExpectAndReturn(0);
  WriteSPI_ExpectAndReturn(data.sevenData, 0x82);
  sevenSegmentFSM(&data);
  TEST_ASSERT_EQUAL(WAIT, data.state);
  TEST_ASSERT_EQUAL(0, data.sevenData);
}

void test_sevenSegmentSM_clock_did_not_overflow_stay_in_wait(){
  SPIData data = {.state = WAIT, .sevenData = 0, .currentClock = 10};
  getClock_ExpectAndReturn(50);
  sevenSegmentFSM(&data);
  TEST_ASSERT_EQUAL(WAIT, data.state);
  TEST_ASSERT_EQUAL(0, data.sevenData);
  TEST_ASSERT_EQUAL(10, data.currentClock);
}


