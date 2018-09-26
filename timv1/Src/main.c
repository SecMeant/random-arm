#include "stm32hal.h"

extern "C"
{
// Helper functions
void delay(int t);
void circle();
void circleT(int T);
void circleTC(int T, int C, volatile GPIO* port = GPIOE);
void circleTC_BSRR(int T, int C);
void flashT(int T);
bool isB1Clicked(void);
bool isC0ON(void);
void invalidInstr(){asm volatile (".word 0xf7f0a000\n");}

// Interrupt handlers
void HardFault_Handler(void);
void TIM7_IRQHandler(void);

void initClock(void);
void initGPIO(void);
void initADTIM(void);
void initBCTIM(void);
int getCounter(BCTIM *tim);
}

#define PINS_MODER 0x55550000

int main(void)
{
	initClock();
	initGPIO();
	initBCTIM();
	TIM7->init();

	// enable tim7 iterrupt
	NVIC->ISER1 |= 1<<23;
	TIM7->DIER = 1;

	// CNT is clocked with 8MHz so with this config
	// Clock is flashing about every 2 secs
	TIM7->PSC = 0xffff;
	TIM7->ARR = 0x1fe0;
	TIM7->reset();	

	while(1)
	{
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
		port->ODR = leds;

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

	delay(T);
	GPIOE->ODR = leds;
	delay(T);
	GPIOE->ODR = 0;
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

void TIM7_IRQHandler(void)
{
	flashT(200000);

	// CNT is clocked with 8MHz so with this config
	// Clock is flashing about every 2 secs
	TIM7->PSC = 0xffff;
	TIM7->ARR = 0x00ff;
	TIM7->reset();

	return;
}

void initClock(void)
{
	RCC->CR = 0x00000083 | // Reset state
	          0x00010000 | // Enable HSE
	          0x00000001;  // Enable HSI

	// Wait for hse ready
	while(not(RCC->CR & 0x00020000));

	// Wait for hsi ready
	while(not(RCC->CR & 0x00000002));

	// disable pll
	RCC->CFGR &= 0xfeffffff;

	// Wait for pll stop
	while((RCC->CR & 0x02000000));

	//RCC->CFGR = 0x00090000 // PLL * 4
	//RCC->CFGR = 0x000d0000 // PLL * 5
	//RCC->CFGR = 0x00110000 // PLL * 6
	
	constexpr unsigned clkmul = 0x11;

  RCC->CFGR = clkmul | // PLL multiplied by 6 ( for some reason crashing when higher ;/ )
              0x00800000 | // I2S is clocked by external clock
              0x00400000 | // USB not prescaled
              0x00002c00 | // APB1 and APB2 bus clk is divided by 2
              0x00000002;  // PLL clk for sysclk
 
	// enable pll
	RCC->CR |= 0x01000000;

	// Wait for pll ready
	while(not(RCC->CR & 0x02000000));
}

void initGPIO(void)
{
	// Enables clock for GPIOE, GPIOC and GPIOA
	RCC->AHBENR  = (1<<21);
	RCC->AHBENR |= (1<<19);
	RCC->AHBENR |= (1<<17);

	// Sets E port pins to output mode
	GPIOE->MODER = 0x55550000;

	// Sets C port pins to input mode
	GPIOC->MODER = 0x00000000;

	// Sets A port pins to input mode ( reset value)
	GPIOA->MODER = 0xA8000000;

	// nopull mode ( reset value )
	GPIOA->PUPDR = 0x64000000;

	// pull-down mode
	GPIOC->PUPDR = 0xAAAAAAAA;
}

void IM(void)
{
	// enable TIM1
	RCC->APB2ENR |= (1<<11);
}

void startTIM1(void)
{
	TIM1->CR1 |= 1;
}

void initBCTIM(void)
{
	// TIM7 enable
	RCC->APB1ENR |= (1<<5);

	TIM7->init();

	TIM7->EGR &= ~1;
	TIM7->DIER = 1; // Enable interrupt generation
	TIM7->PSC = 0xffff;
	TIM7->ARR = 0x1f00;
}

void startTIM7(void)
{
	TIM7->CR1 |= 1;
}

int getCounter(BCTIM *tim)
{
	return tim->CNT & 0x0000ffff;
}

bool isB1Clicked(void)
{
	return GPIOA->IDR & 0x00000001;
}

bool isC0ON(void)
{
	return GPIOC->IDR & 0x00000001;
}
