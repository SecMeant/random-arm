#ifndef STM32HAL_H
#define STM32HAL_H

#include <stdint.h>

struct GPIO
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFLR;
	uint32_t AFRH;
	uint32_t BRR;
};

volatile GPIO *GPIOA = (GPIO*)(0x48000000);
volatile GPIO *GPIOB = (GPIO*)(0x48000400);
volatile GPIO *GPIOC = (GPIO*)(0x48000800);
volatile GPIO *GPIOD = (GPIO*)(0x48000C00);
volatile GPIO *GPIOE = (GPIO*)(0x48001000);
volatile GPIO *GPIOF = (GPIO*)(0x48001400);

struct RCC_
{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
	uint32_t AHBRSTR;
	uint32_t CFGR2;
	uint32_t CFGR3;
};

volatile RCC_ *RCC = (RCC_*)(0x40021000);

struct ADTIM
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t RCR;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t BDTR;
	uint32_t DCR;
	uint32_t DMAR;
	uint32_t OR;
	uint32_t CCMR3;
	uint32_t CCR5;
	uint32_t CCR6;
};

volatile ADTIM* TIM1 = (ADTIM*)0x40012C00;
volatile ADTIM* TIM8 = (ADTIM*)0x40013400;
volatile ADTIM* TIM20 = (ADTIM*)0x40015000;

struct BCTIM
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t RESERVED1;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t RESERVED2;
	uint32_t RESERVED3;
	uint32_t RESERVED4;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;

	void init(void) volatile;
	void reset(void) volatile;

};

volatile BCTIM* TIM6 = (BCTIM*)0x40001000;
volatile BCTIM* TIM7 = (BCTIM*)0x40001400;

struct _NVIC
{
	// Interrupt controller type register
	uint32_t ICTR;

	uint32_t RESERVED1[0x3e];
	
	// Interrupt set-enable register
	uint32_t ISER0;
	uint32_t ISER1;
	uint32_t ISER2;
	uint32_t ISER3;
	uint32_t ISER4;
	uint32_t ISER5;
	uint32_t ISER6;
	uint32_t ISER7;
	uint32_t ISER8;
	uint32_t ISER9;
	uint32_t ISER10;
	uint32_t ISER11;
	uint32_t ISER12;
	uint32_t ISER13;
	uint32_t ISER14;
	uint32_t ISER15;

	uint32_t RESERVED2[0x10];
	
	// Interrupt set-clear register
	uint32_t ICER0;
	uint32_t ICER1;
	uint32_t ICER2;
	uint32_t ICER3;
	uint32_t ICER4;
	uint32_t ICER5;
	uint32_t ICER6;
	uint32_t ICER7;
	uint32_t ICER8;
	uint32_t ICER9;
	uint32_t ICER10;
	uint32_t ICER11;
	uint32_t ICER12;
	uint32_t ICER13;
	uint32_t ICER14;
	uint32_t ICER15;

	uint32_t RESERVED3[0x10];
	
	// Interrupt set-pending register
	uint32_t ISPR0;
	uint32_t ISPR1;
	uint32_t ISPR2;
	uint32_t ISPR3;
	uint32_t ISPR4;
	uint32_t ISPR5;
	uint32_t ISPR6;
	uint32_t ISPR7;
	uint32_t ISPR8;
	uint32_t ISPR9;
	uint32_t ISPR10;
	uint32_t ISPR11;
	uint32_t ISPR12;
	uint32_t ISPR13;
	uint32_t ISPR14;
	uint32_t ISPR15;

	uint32_t RESERVED4[0x10];
	
	// Interrupt clear-pending register
	uint32_t ICPR0;
	uint32_t ICPR1;
	uint32_t ICPR2;
	uint32_t ICPR3;
	uint32_t ICPR4;
	uint32_t ICPR5;
	uint32_t ICPR6;
	uint32_t ICPR7;
	uint32_t ICPR8;
	uint32_t ICPR9;
	uint32_t ICPR10;
	uint32_t ICPR11;
	uint32_t ICPR12;
	uint32_t ICPR13;
	uint32_t ICPR14;
	uint32_t ICPR15;

	uint32_t RESERVED5[0x10];

	// Interrupt active bit register
	uint32_t IABR0;
	uint32_t IABR1;
	uint32_t IABR2;
	uint32_t IABR3;
	uint32_t IABR4;
	uint32_t IABR5;
	uint32_t IABR6;
	uint32_t IABR7;
	uint32_t IABR8;
	uint32_t IABR9;
	uint32_t IABR10;
	uint32_t IABR11;
	uint32_t IABR12;
	uint32_t IABR13;
	uint32_t IABR14;
	uint32_t IABR15;

	uint32_t RESERVED6[0x10];

	// By following convetion here should be clear bit active register
	// however such register doesnt make sense, it is reserved.
	uint32_t RESERVED7[0x10];

	// Even if section is reserved padding still applies ^^^
	uint32_t RESERVED8[0x10];

	// Interrupt priority register
	#include "nvic_priority_reg.h"

};

volatile _NVIC* NVIC=(_NVIC*)0xe000e004;

// 0x4000 6800 - 0x4000 63FF
struct _USB
{
	uint32_t EP0R;
	uint32_t EP1R;
	uint32_t EP2R;
	uint32_t EP3R;
	uint32_t EP4R;
	uint32_t EP5R;
	uint32_t EP6R;
	uint32_t EP7R;
	uint32_t RESERVED[8];
	uint32_t CNTR;
	uint32_t ISTR;
	uint32_t FNR;
	uint32_t DADDR;
	uint32_t BTABLE;
	uint32_t LPMCSR;
};

volatile _USB * USBFS = (volatile _USB*)(0x40005C00);

void BCTIM::init(void) volatile
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

void BCTIM::reset(void) volatile
{	
	// stop
	this->CR1 &= ~1;

	// clear update flag
	this->SR = 0;

	// reset counting
	this->CNT = 0;

	// start
	this->CR1 |= 1;
}

#endif //STM32HAL_H
