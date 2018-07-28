#ifndef STM32HAL_H
#define STM32HAL_H

struct GPIO
{
	unsigned MODER;
	unsigned OTYPER;
	unsigned OSPEEDR;
	unsigned PUPDR;
	unsigned IDR;
	unsigned ODR;
	unsigned BSRR;
	unsigned LCKR;
	unsigned AFLR;
	unsigned AFRH;
	unsigned BRR;
};

GPIO *GPIOA = (GPIO*)(0x48000000);
GPIO *GPIOB = (GPIO*)(0x48000400);
GPIO *GPIOC = (GPIO*)(0x48000800);
GPIO *GPIOD = (GPIO*)(0x48000C00);
GPIO *GPIOE = (GPIO*)(0x48001000);
GPIO *GPIOF = (GPIO*)(0x48001400);

struct RCC_
{
	unsigned CR;
	unsigned CFGR;
	unsigned CIR;
	unsigned APB2RSTR;
	unsigned APB1RSTR;
	unsigned AHBENR;
	unsigned APB2ENR;
	unsigned APB1ENR;
	unsigned BDCR;
	unsigned CSR;
	unsigned AHBRSTR;
	unsigned CFGR2;
	unsigned CFGR3;
}*RCC = (RCC_*)(0x40021000);

struct ADTIM
{
	unsigned CR1;
	unsigned CR2;
	unsigned SMCR;
	unsigned DIER;
	unsigned SR;
	unsigned EGR;
	unsigned CCMR1;
	unsigned CCMR2;
	unsigned CCER;
	unsigned CNT;
	unsigned PSC;
	unsigned ARR;
	unsigned RCR;
	unsigned CCR1;
	unsigned CCR2;
	unsigned CCR3;
	unsigned CCR4;
	unsigned BDTR;
	unsigned DCR;
	unsigned DMAR;
	unsigned OR;
	unsigned CCMR3;
	unsigned CCR5;
	unsigned CCR6;
}*TIM1 = (ADTIM*)0x40012C00, *TIM8 = (ADTIM*)0x40013400, *TIM20 = (ADTIM*)0x40015000;

struct BCTIM
{
	unsigned CR1;
	unsigned CR2;
	unsigned RESERVED1;
	unsigned DIER;
	unsigned SR;
	unsigned EGR;
	unsigned RESERVED2;
	unsigned RESERVED3;
	unsigned RESERVED4;
	unsigned CNT;
	unsigned PSC;
	unsigned ARR;

	void init(void);

	void reset(void);
}*TIM6 = (BCTIM*)0x40001000, *TIM7 = (BCTIM*)0x40001400;


void BCTIM::init(void)
{
	this->CR1 = 0;
	this->CR2 = 0;
	this->DIER = 0;
	this->SR = 0;
	this->EGR = 0;
	this->CNT = 0;
	this->PSC = 0;
	this->ARR = 0xFFFF;
}

void BCTIM::reset(void)
{	
	// stop
	this->CR1 &= ~1;

	// reset counting
	this->CNT = 0;

	// start
	this->CR1 |= 1;
}

#endif //STM32HAL_H
