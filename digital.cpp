// 
// 
// 

#include "digital.h"

#define DIG_CTRL_BTN_TEMP_SET_PIN 2
#define DIG_CTRL_ENC_TEMP_SEL_A_PIN 18
#define DIG_CTRL_ENC_TEMP_SEL_B_PIN 19

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

/* row is old state, column new state */
static const int encoder_lut[4][4] = {
	{ 0,-1, 1, 0},
	{ 1, 0, 0,-1},
	{-1, 0, 0, 1},
	{ 0, 1,-1, 0}
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
	btn->state = (bool)digitalRead(btn->pin);
	return (int)btn->state;
}

/* returns either 1 or -1 to indicate clockwise or counter-clockwise direction, respectivevly */
int read_encoder(encoder_t *enc)
{
	uint8_t new_state = 0;
	new_state |= digitalRead(enc->dig_a.pin) << 1;
	new_state |= digitalRead(enc->dig_b.pin);

	int tmp = encoder_lut[enc->old_state][new_state];
	enc->old_state = new_state;
	return tmp;
}

void isr_btn_temp_set(void)
{
	digital_temp_set = digital_temp_sel;
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
	digital_temp_sel = 350;
	digital_temp_set = 0;

	pinMode(DIG_CTRL_BTN_TEMP_SET_PIN, INPUT_PULLUP);
	read_button((button_t*)&btn_temp_set);
	attachInterrupt(digitalPinToInterrupt(DIG_CTRL_BTN_TEMP_SET_PIN), isr_btn_temp_set, CHANGE);

	pinMode(DIG_CTRL_ENC_TEMP_SEL_A_PIN, INPUT_PULLUP);
	pinMode(DIG_CTRL_ENC_TEMP_SEL_B_PIN, INPUT_PULLUP);
	read_encoder((encoder_t*)&enc_temp_sel);
	attachInterrupt(digitalPinToInterrupt(DIG_CTRL_ENC_TEMP_SEL_A_PIN), isr_enc_temp_sel, CHANGE);
	attachInterrupt(digitalPinToInterrupt(DIG_CTRL_ENC_TEMP_SEL_B_PIN), isr_enc_temp_sel, CHANGE);
}
