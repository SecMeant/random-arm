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

#endif //STM32HAL_H
