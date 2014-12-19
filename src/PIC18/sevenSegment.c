#include "sevenSegment.h"
#include "../18c.h"
#include "Clock.h"


#if !(defined(__XC) || defined(__18CXX))
  #include "spi.h"
#else
    #include <spi.h>
#endif // __18CXX

char number[]= {
    0xee,
    0x82,
    0xdc,
    0xd6,
    0xb2,
    0x76,
    0x7e,
    0xc2,
    0xfe,
    0xf2,
    0xfa,
    0x3e,
    0x6c,
    0x9e,
    0x7c,
    0x78,
    0xee
};

void startSPI(SPIData *data){
  TRISCbits.TRISC2 = 0;
  PORTCbits.RC2 = 1;
  data->state = SPI_START;
}

void closeSPI(){
    PORTCbits.RC2 = 0;
}

void sevenSegmentSM(SPIData *data){
    int i=0;
    switch(data->state){
    case SPI_START:
      data->currentClock = getClock();
      data->sevenData = 0;
      data->state = WAIT;
      WriteSPI(number[data->sevenData]);
      break;

    case WAIT:  
      if(getClock() - data->currentClock >= 488){
        data->currentClock = getClock();
        data->sevenData++;

        WriteSPI(number[data->sevenData]);
        if(data->sevenData == 16){
          data->sevenData = 0;
        }
      }
      
      data->state = WAIT;
      break;
      
    default:
      data->state = SPI_START;
      break;
  }

}


