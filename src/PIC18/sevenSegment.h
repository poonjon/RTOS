#ifndef SevenSeg_H
#define SevenSeg_H

typedef enum{
	SPI_START,
	WAIT
} sevenSeg;

typedef struct SPIData SPIData;
struct SPIData{
	sevenSeg state;
	int sevenData;
	unsigned long currentClock;
};

void startSPI(SPIData *data);
void closeSPI();
void sevenSegmentSM(SPIData *data);

#endif // SevenSeg_H

