#include "stm32hal.h"

extern "C"
{
// Helper functions
void delay(int t);
void circle();
void circleT(int T);
void circleTC(int T, int C, GPIO* port = GPIOE);
void circleTC_BSRR(int T, int C);
void flashT(int T);
bool isB1Clicked(void);
void invalidInstr(){asm volatile (".word 0xf7f0a000\n");}

// Interrupt handlers
void HardFault_Handler(void);

void initGPIO(void);
}

#define PINS_MODER 0x55550000

int main(void)
{
	initGPIO();
	
	unsigned cnt = 0;

	GPIOE->ODR = (cnt << 8) & 0x0000ff00;
	while(1)
	{
		if(isB1Clicked())
		{
			cnt++;
			GPIOE->ODR = (cnt << 8) & 0x0000ff00;
			while(isB1Clicked()); // Wait for release
		}
	}
}

void circleT(int T)
{
	// Used for turning on leds
	unsigned leds = 0x00000100;

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

void circleTC(int T, int C, GPIO* port)
{
	// Used for turning on leds
	unsigned leds = 0x00000100;

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

void circleTC_BSRR(int T, int C)
{
	// Used for turning on leds
	unsigned leds = 0x00000100;

	for(int _c=0; _c<C; _c++)
	{
		delay(T);
		// Sets leds on
		// 0x0000XX00 --> XX is 8 bit long and describes states
		// if 8 leds on board. 1 - set, 0 - reset
		GPIOE->BSRR = leds | 0xffff0000;

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

void initGPIO(void)
{
	// Enables GPIOE
	RCC->AHBENR = (1<<21);
	RCC->AHBENR |= (1<<17);

	// Sets E port pins to output mode
	GPIOE->MODER = 0x55550000;

	// Sets A port pins to input mode
	GPIOA->MODER = 0xA8000000;

	// nopull mode ( reset value )
	GPIOA->PUPDR = 0x64000000;
}

bool isB1Clicked(void)
{
	return GPIOA->IDR & 0x00000001;
}
