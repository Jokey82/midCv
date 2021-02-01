#include "main.h"

/*add second pwm for velocity output*/


void init_pwm(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	GPIOB->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9);
	GPIOB->CRH &= ~GPIO_CRH_CNF9_0;
	
	TIM4->CCER |= TIM_CCER_CC4E;
	TIM4->CR1 |= TIM_CR1_ARPE;
	
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;
	
	TIM4->PSC = 7;
	TIM4->ARR = 10000;
	TIM4->CCR4 = 5000;
	
	TIM4->EGR |= TIM_EGR_UG;
	TIM4->CR1 |= TIM_CR1_CEN;
	
	
	//DBG
	
	//GPIOB->CRL |= GPIO_CRL_MODE5;	
	
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
	GPIOA->CRL |= GPIO_CRL_MODE5;
	
}


//v = v_out * 100 
void pwm_set_volt(uint16_t v){
	v = v>PIN_V_MAX?PIN_V_MAX:v;
	
	TIM4->CCR4 = (float)TIM4->ARR * ((float)v/(float)PIN_V_MAX);
	//GPIOB->BSRR |= GPIO_BSRR_BR5;
}

