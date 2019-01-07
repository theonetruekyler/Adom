// 
// 
// 

#include "temperature_control.h"
#include "scheduler.h"
#include "PID_v1.h"
#include "max6675.h"

#define FET_PIN 7

#define THERMOCOUPLE_DO_PIN 7
#define THERMOCOUPLE_CS_PIN 5
#define THERMOCOUPLE_CLK_PIN 6

#define TEMP_CTRL_KP 76
#define TEMP_CTRL_KI 30
#define TEMP_CTRL_KD 6

/************************************************************************/
/* VARIABLE DEFINITIONS (GLOBAL)                                        */
/************************************************************************/

double set_point;



/************************************************************************/
/* VARIABLE DEFINITIONS (LOCAL)                                         */
/************************************************************************/

static double input;
static double output;

MAX6675 thermocouple(THERMOCOUPLE_CLK_PIN, THERMOCOUPLE_CS_PIN, THERMOCOUPLE_DO_PIN);

PID temp_ctrl(&input, &output, &set_point, TEMP_CTRL_KP, TEMP_CTRL_KI, TEMP_CTRL_KD, DIRECT);



/************************************************************************/
/* FUNCTION DEFINITIONS (GLOBAL)                                        */
/************************************************************************/

void temp_ctrl_init(void)
{
	/// TODO: remove this return once implemented
	return;

	/* set transistor pin direction */
	pinMode(FET_PIN, OUTPUT);

	/* enable controller */
	set_point = 350;
	temp_ctrl.SetMode(AUTOMATIC);

	scheduler_add_task_freq(temp_ctrl_update, 2);
}

void temp_ctrl_update(void)
{
	input = thermocouple.readFahrenheit();

	temp_ctrl.Compute();

	/// TODO: display controller output
}


