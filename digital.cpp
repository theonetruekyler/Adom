// 
// 
// 

#include "digital.h"

#define DIG_CTRL_BTN_TEMP_SET_PIN 2
#define DIG_CTRL_ENC_TEMP_SEL_A_PIN 3
#define DIG_CTRL_ENC_TEMP_SEL_B_PIN 4

#define DIGITAL_DEBUG 0

/************************************************************************/
/* VARIABLE DEFINITIONS (LOCAL)                                         */
/************************************************************************/

volatile button_t btn_temp_set = {
	DIG_CTRL_BTN_TEMP_SET_PIN, 0
};

volatile encoder_t enc_temp_sel = {
	{DIG_CTRL_ENC_TEMP_SEL_A_PIN, 0},
	{DIG_CTRL_ENC_TEMP_SEL_B_PIN, 0},
	0
};



/************************************************************************/
/* VARIABLE DEFINITIONS (GLOBAL)                                        */
/************************************************************************/

volatile int digital_temp_sel;
volatile int digital_temp_set;



/************************************************************************/
/* FUNCTION DEFINITIONS (LOCAL)                                         */
/************************************************************************/

int read_button(button_t *btn)
{
	return digitalRead(btn->pin);
}

/* returns either 1 or -1 to indicate clockwise or counter-clockwise direction, respectivevly */
int read_encoder(encoder_t *enc)
{
	if (!(digitalRead(enc->dig_a.pin) ^ digitalRead(enc->dig_b.pin))) {
		return 1;
	}
	else {
		return -1;
	}
}

void isr_btn_temp_set(void)
{
	if (LOW == read_button((button_t*)&btn_temp_set)) {
		digital_temp_set = digital_temp_sel;
	}
}

void isr_enc_temp_sel(void)
{
	digital_temp_sel += read_encoder((encoder_t*)&enc_temp_sel);
}



/************************************************************************/
/* FUNCTION DEFINITIONS (GLOBAL)                                        */
/************************************************************************/

void digital_init(void)
{
	digital_temp_sel = 666;
	digital_temp_set = 0;

	pinMode(DIG_CTRL_BTN_TEMP_SET_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(DIG_CTRL_BTN_TEMP_SET_PIN), isr_btn_temp_set, CHANGE);

	pinMode(DIG_CTRL_ENC_TEMP_SEL_A_PIN, INPUT_PULLUP);
	pinMode(DIG_CTRL_ENC_TEMP_SEL_B_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(DIG_CTRL_ENC_TEMP_SEL_A_PIN), isr_enc_temp_sel, CHANGE);
}