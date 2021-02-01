#include "main.h"

/* MODULE TO MANAGE CV OUTPUTS
*	 void exec_cv(cvstate notestate) -- sets pitch voltage and gate output to notestate values
*  Voltage per halfstep = 0.083
*  V(n) = V(base) + n * V(hs)
*	 V(base) = V(hs) = 0.083
*	 n = notestate.pitch - 36
*/

void exec_cv(cvstate notestate){
	uint8_t n = (notestate.pitch - BASE_NOTE_MIDI)>=0?notestate.pitch - BASE_NOTE_MIDI:0;
	
	uint16_t tmp = (n%OCTAVE) * HALFSTEP_V;
	tmp+=(n/OCTAVE) * 1000;
	tmp+=BASE_NOTE_V;
	
	//tmp+=n;
	
	pwm_set_volt(tmp);
	
	if(notestate.gate == 1){
	//DBG
	GPIOA->BSRR |= GPIO_BSRR_BS5;
	return;
	}
	GPIOA->BSRR |= GPIO_BSRR_BR5;
}
