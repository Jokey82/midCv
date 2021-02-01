#include "stm32f10x.h"
#include "stdio.h"
//#include "common.h"

#define RX_BUF_SIZE 80

#define BASE_NOTE_V 83-17 //minus voltage offset occurs in 5V PWM converter
#define BASE_NOTE_MIDI 36
#define TOP_NOTE_MIDI 96
#define HALFSTEP_V 83
#define OCTAVE 12

#define PIN_V_MAX 5000 //PULSE PEAK VOLTAGE; NORMAL 5000; 
#define V_MAX 6000

typedef struct {
	uint8_t gate;
	uint16_t pitch;
	uint8_t retrig;
	uint8_t velocity;
}cvstate;


//DWT 

uint32_t DWT_Delay_Init(void);
void delayMS_DWT(uint32_t ms);
void delayUS_DWT(uint32_t us);

//UART
extern void send_to_uart(uint8_t data);
extern void send_str(char * string);
extern void init_uart(void);
extern cvstate usart_main_loop_routine(void);
extern void clear_RXBuffer(void);

//ENCODER
void init_encoder(void);

//PWM
extern void init_pwm(void);
extern void pwm_set_volt(uint16_t v);

//CV 
extern void exec_cv(cvstate notestate);

//MAX72
void init_max72(void);
void send_max_byte(uint8_t byte);
void send_max_data(uint8_t address, uint8_t data);
void max_display_digit(uint8_t addr, uint8_t digit);
void max_display_number(uint8_t number);
