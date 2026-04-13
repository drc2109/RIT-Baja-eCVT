/*
 * motor_control.c
 *
 *  Created on: Mar 23, 2026
 *      Author: jells
 */

#include <stdbool.h>
#include "motor_control.h"
#include "Controller_P7.h"

float KP = 11;
float KI = 4;
float KD = 0;

extern P_Controller_P7_T Controller_P7_P;

uint16_t update_setpoint(uint16_t pos_setpoint, uint16_t curr_pos){
	static bool inc_direction = true;
	static uint16_t soften_factor = 301;
	if (soften_factor){
		soften_factor--;
	}
	if (pos_setpoint < MIN_ANGLE_VAL){
		pos_setpoint = MIN_ANGLE_VAL;
	}
	if (pos_setpoint >= MAX_ANGLE_VAL){
		inc_direction = false;
	}
	else if (pos_setpoint <= MIN_ANGLE_VAL){
		inc_direction = true;
	}

	pos_setpoint = inc_direction ? pos_setpoint + DELTA_ANGLE : pos_setpoint - DELTA_ANGLE;
	return (pos_setpoint + soften_factor * curr_pos)/(soften_factor + 1);
}

uint16_t pid_loop(uint16_t pos_setpoint, uint16_t curr_position){
	static float err_int = 0;
	static float prev_error = 0;
	const float DT = MC_OS_DELAY/1000.0;
	float err_deriv = 0;

	float error = (float)(pos_setpoint - curr_position);
	if (error < 2 && error > -2){
		error = 0;
	}
	err_int += error*DT;

	err_deriv = (error - prev_error) / DT;
	prev_error = error;
	if (err_int > 100)
		err_int = 100;
	else if (err_int < -100)
		err_int = -100;
	uint16_t output_speed = (uint16_t)(KP*error + KI*err_int + KD*err_deriv + NEUTRAL_SPEED);
	if (output_speed > MAX_TEST_SPEED_FWD){
		output_speed = MAX_TEST_SPEED_FWD;
	}
	else if (output_speed < MAX_TEST_SPEED_REV){
		output_speed = MAX_TEST_SPEED_REV;
	}
	return output_speed;

}


uint16_t scale_command(const float motor_voltage_command){
	return NEUTRAL_SPEED + (uint16_t)(MOTOR_VOLTAGE_SCALE_FACTOR*motor_voltage_command);
}

//TODO update this bs
void init_pidconfig(PIDConfig* pidconfig){
//	pidconfig->gr_high_setpoint = Controller_P7_P.;
	pidconfig->gr_high_kp = Controller_P7_P.Prop_GR_High;
	pidconfig->gr_high_ki = Controller_P7_P.Int_GR_High;
	pidconfig->gr_high_kd = Controller_P7_P.Der_GR_High;
//	pidconfig->gr_low_setpoint = Controller_P7_P.;
	pidconfig->gr_low_kp = Controller_P7_P.Prop_GR_Low;
	pidconfig->gr_low_ki = Controller_P7_P.Int_GR_Low;
	pidconfig->gr_low_kd = Controller_P7_P.Der_GR_Low;
//	pidconfig->rpm_high_setpoint = Controller_P7_P.;
	pidconfig->rpm_high_kp = Controller_P7_P.Prop_RPM_High;
	pidconfig->rpm_high_ki = Controller_P7_P.Int_RPM_High;
	pidconfig->rpm_high_kd = Controller_P7_P.Der_RPM_High;
//	pidconfig->rpm_low_setpoint = Controller_P7_P.;
	pidconfig->rpm_low_kp = Controller_P7_P.Prop_RPM_Low;
	pidconfig->rpm_low_ki = Controller_P7_P.Int_RPM_Low;
	pidconfig->rpm_low_kd = Controller_P7_P.Der_RPM_Low;
}

//TODO update this bs
void update_pidconfig(PIDConfig* pidconfig){
//	pidconfig->gr_high_setpoint = Controller_P7_P.;
	Controller_P7_P.Prop_GR_High = pidconfig->gr_high_kp;
	Controller_P7_P.Int_GR_High = pidconfig->gr_high_ki;
	Controller_P7_P.Der_GR_High = pidconfig->gr_high_kd;
//	pidconfig->gr_low_setpoint = Controller_P7_P.;
	Controller_P7_P.Prop_GR_Low = pidconfig->gr_low_kp;
	Controller_P7_P.Int_GR_Low = pidconfig->gr_low_ki;
	Controller_P7_P.Der_GR_Low = pidconfig->gr_low_kd;
//	pidconfig->rpm_high_setpoint = Controller_P7_P.;
	Controller_P7_P.Prop_RPM_High = pidconfig->rpm_high_kp;
	Controller_P7_P.Int_RPM_High = pidconfig->rpm_high_ki;
	Controller_P7_P.Der_RPM_High = pidconfig->rpm_high_kd;
//	pidconfig->rpm_low_setpoint = Controller_P7_P.;
	Controller_P7_P.Prop_RPM_Low = pidconfig->rpm_low_kp;
	Controller_P7_P.Int_RPM_Low = pidconfig->rpm_low_ki;
	Controller_P7_P.Der_RPM_Low = pidconfig->rpm_low_kd;
}
