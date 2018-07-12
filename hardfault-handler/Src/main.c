#include "stm32f3xx_hal.h"

// Helper functions
void delay(int t);
void circle();
void circleT(int T);
void circleTC(int T, int C);
void flashT(int T);
void invalidInstr(){asm volatile (".word 0xf7f0a000\n");}

// Interrupt handlers
void HardFault_Handler(void);

int main(void)
{
	circleTC(75000, 32);

	// Causes hardfault handler to be invoked
	invalidInstr();
}

void circleT(int T)
{
	// Used for turning on leds
	unsigned leds = 0x00000100;

	// Enables GPIOE ??
	RCC->AHBENR |= (1<<21);

	// ????
	GPIOE->MODER |= 0x55550000;

	for(;;)
	{
		delay(T);
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

void circleTC(int T, int C)
{
	// Used for turning on leds
	unsigned leds = 0x00000100;

	// Enables GPIOE ??
	RCC->AHBENR |= (1<<21);

	// ????
	GPIOE->MODER |= 0x55550000;

	for(int _c=0; _c<C; _c++)
	{
		delay(T);
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

void circle()
{
	circleT(75000);
}

void flashT(int T)
{
	// Used for turning on leds
	unsigned leds = 0x0000ff00;

	// Enables GPIOE ??
	RCC->AHBENR |= (1<<21);

	// ????
	GPIOE->MODER |= 0x55550000;

	for(;;)
	{
		delay(T);
		GPIOE->ODR = leds;
		delay(T);
		GPIOE->ODR = 0;
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

void HardFault_Handler(void)
{
  while (1)
  {
		flashT(200000);
  }
}
