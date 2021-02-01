#include "main.h"

static volatile char RXs[RX_BUF_SIZE];
static volatile uint8_t RXc;
static volatile uint8_t RXi = 0; 

static volatile uint8_t note_on = 0;
static volatile uint8_t note_off = 0;
static volatile uint8_t midi_recv_state = 0;
/*
MRS = 1 -> NOTE ON, receiving pitch
MRS = 2 -> NOTE OFF, receiving pitch
MRS = 3 -> PITCH set, cvstate composed(ignore velocity)
*/

static volatile uint8_t state = 0;
static volatile uint8_t state_prev = 0;


uint8_t midi_channel = 0;


cvstate notestate;

void send_to_uart(uint8_t data){
 while(!(USART1->SR & USART_SR_TC)){}
	 
 USART1->DR = data;
}

void clear_RXBuffer(void) {
    for (RXi=0; RXi<RX_BUF_SIZE; RXi++)
        RXs[RXi] = '\0';
    RXi = 0;
}

void send_str(char * string) {
 uint8_t i=0;
 while(string[i]) {
  send_to_uart(string[i]);
	
  i++;
 }
 send_to_uart('\r');
 send_to_uart('\n');
}


void init_uart(void){
	
	//1.ENABLE CLOCK FOR USART1 AND GPIOA
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN);

	//2.ENABLE UART NVIC
	USART1->CR1 |= (USART_CR1_RXNEIE);
	
	//3.SET PINS PA9(ALT 50Hz PUSH-PULL) & PA10(FLOATING INPUT)
	
	 GPIOA->CRH |= GPIO_CRH_MODE9_1;
	 GPIOA->CRH |= GPIO_CRH_CNF9_1;
	 GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
	
	 GPIOA->CRH &= ~GPIO_CRH_MODE10;
	 GPIOA->CRH |= GPIO_CRH_CNF10_0;
	 GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
 	 	
		
	
	//4.SET UART REGISTERS 8bit, NO PARITY 1STOP 19200BR(BRR = EA6)
	USART1->BRR = 0xEA6; //19200
	
	USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	
	//5. CONFIG LED PIN

	
	NVIC_EnableIRQ(USART1_IRQn);
}

//DBG
cvstate usart_main_loop_routine(void){
	
	return notestate;
}

void upd_midi_channel(void){
	uint8_t tmp = (TIM3->CNT) / 10;
	if(tmp!=midi_channel){
		
	}
}



void USART1_IRQHandler(void){
		if((USART1->SR & USART_SR_RXNE) != (u16)RESET){
		RXc = (char)USART1->DR;
		/*
			MRS = 1 -> NOTE ON, receiving pitch
			MRS = 2 -> NOTE OFF, receiving pitch
			MRS = 3 -> PITCH set, cvstate composed(ignore velocity)
		*/
		switch(midi_recv_state){
			case 1:
				notestate.pitch = RXc;
				midi_recv_state = 3;
				break;
			case 2:
				notestate.pitch = RXc;
				midi_recv_state = 3;
				break;
			case 3:
				exec_cv(notestate);
				midi_recv_state = 0;
				break;
			default:
				break;
		}
		switch(RXc - midi_channel){
			case 0x90:
				notestate.gate = 1;
				midi_recv_state = 1;
				break;
			case 0x80:
				notestate.gate = 0;
				midi_recv_state = 2;
				break;
			default:
				break;
		}
	}
}
