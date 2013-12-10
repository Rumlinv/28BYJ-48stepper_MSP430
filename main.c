#include "msp430g2553.h" 


	unsigned int crt_step = 0;
	unsigned int step[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09}; // Step sequence 
void main(void) {

	
	// Setup the PWM, etc.
	BCSCTL1 =CALBC1_1MHZ;							//set range 1MHZ 8MHZ 16MHZ
	DCOCTL = CALDCO_1MHZ;							//set DCO step+ modulation
	BCSCTL3 |= LFXT1S_2;							//LFXT1 = VLO 
	IFG1 &= ~OFIFG;									//clear OSCFault flag
	BCSCTL2 |= SELM_0 +DIVM_3 +DIVS_3;				//MCLK = DCO/8, SMCLK = DCO/8
	
	WDTCTL = WDTPW + WDTHOLD; // Kill watchdog timer
	TACCTL1 = OUTMOD_7; // TACCR1 reset/set
	TACTL = TASSEL_2 + MC_1; // SMCLK, upmode




	P1DIR = 0x0F; // Allow P1 pins 0 to 3 to output
	P1OUT = 0; // Disable everything.
	
	
	
	//for bipolar motor to go forewards
	
	 // Current step index;
	for(;;) {
		P1OUT = step[crt_step++];
		if(crt_step == 8) crt_step = 0;
		__delay_cycles(290);//99Hz for 28BYJ-48
	 }
}
