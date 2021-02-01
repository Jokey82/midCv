#include "main.h"


uint8_t DIGITS[10] = {0b01111110, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b};


void init_max72(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	//PA5 = clk PA7 = SDATA PA3 = load
	GPIOA->CRL |= GPIO_CRL_MODE3_1 | GPIO_CRL_MODE5_1 | GPIO_CRL_MODE7_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF3;
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
	GPIOA->CRL &= ~GPIO_CRL_CNF7;
	
	GPIOA->BSRR |= GPIO_BSRR_BS5;
	GPIOA->BSRR |= GPIO_BSRR_BS3;
}

void send_max_byte(uint8_t byte){
	/*
	*PULL THE CLOCK LOW
	*WRITE MSB TO SDATA PIN(byte&0b1000 0000)
	*SHIFT DATA 1BIT LEFT
	*PULL CLK HIGH
	*/
	for(uint8_t i=0;i<8;i++){
		delayMS_DWT(2);
		GPIOA->BSRR |= GPIO_BSRR_BR5;
		//delayMS_DWT(5);
		
		if((byte&0x80) == 0x80){
			GPIOA->BSRR |= GPIO_BSRR_BS7;
		}
		else{
			GPIOA->BSRR |= GPIO_BSRR_BR7;
		}
		byte = byte<<1;
		delayMS_DWT(2);
 		GPIOA->BSRR |= GPIO_BSRR_BS5;
		
	}
}

void send_max_data(uint8_t address, uint8_t data){
	GPIOA->BSRR |= GPIO_BSRR_BR3;
	send_max_byte(address);
	send_max_byte(data);
	GPIOA->BSRR |= GPIO_BSRR_BS3;
}

void max_display_digit(uint8_t addr, uint8_t digit){
	digit = digit>9?9:digit;
	send_max_data(addr, DIGITS[digit]);
}

void max_display_number(uint8_t number){
	for(uint8_t i=0;i<2;i++){
		max_display_digit(0x1+i, number%10);
		number/=10;
	}
}
