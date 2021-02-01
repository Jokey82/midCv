#include "main.h"


//Set TIM3 to external clock

void init_encoder(void){
 RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPBEN;
 RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; 
	
	AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_1;
	
	/*
	GPIOB->CRL &= ~GPIO_CRL_CNF5;
	GPIOB->CRL &= ~GPIO_CRL_CNF4;

	GPIOB->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1;
	
	//GPIOB->ODR |= GPIO_ODR_ODR0 | GPIO_ODR_ODR1;
	
	GPIOB->CRL &= ~GPIO_CRL_MODE0;
	GPIOB->CRL &= ~GPIO_CRL_MODE1;
		*/
	
 //GPIO must be input floating which is default so no code to write for that
	
	
 TIM3->ARR = 0xA0;

 //per datasheet instructions
 TIM3->CCMR1 |= (TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 );  //step 1 and 2
 TIM3->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);  // step 3 and 4
 TIM3->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;   //step 5
 TIM3->CR1 |= TIM_CR1_CEN ;     //step 6
}

