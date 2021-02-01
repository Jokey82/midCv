#include "main.h"


int main(void){
	
	DWT_Delay_Init();
	init_uart();
	init_pwm();
	init_encoder();
	//init_max72();
	
	
	/*
	send_max_data(0x09, 0x00);
	send_max_data(0x0a, 0x03);
	send_max_data(0x0b, 0x02);
	send_max_data(0x0c, 0x01);
	send_max_data(0x0f, 0x00);
	*/
	
	for(;;){		
		//send_to_uart((uint8_t)TIM3->CNT);
		delayUS_DWT(100000);
	}	
}
 