#include "stm32f3xx_hal.h"

void delay(int t);

int main(void)
{
	// Used for turning on leds
	unsigned leds = 0x00000100;

	// Enables GPIOE ??
	RCC->AHBENR |= (1<<21);

	// ????
	GPIOE->MODER |= 0x55550000;

	for(;;)
	{
		delay(75000);
		// Sets leds on
		// 0x0000XX00 --> XX is 8 bit long and describes states
		// if 8 leds on board. 1 - set, 0 - reset
		GPIOE->ODR = leds;

		leds <<= 1;

		if((leds>>16) != 0)
		{
			leds &= 0x0000ff00;
			leds |= 0x00000100;
		}
	}
}

void delay(int t)
{
	volatile int i,j;

	for(i=0; i < t; i++)
	{
		j++;
	}
}
