/*
 * motor_control.h
 *
 *  Created on: Mar 23, 2026
 *      Author: jells
 */

#ifndef INC_MOTOR_CONTROL_H_
#define INC_MOTOR_CONTROL_H_

#include <stdint.h>

//#define NEUTRAL_SPEED 19199  11999
//modify to work with PW -> y=neutral +4000*(x/12)
#define NEUTRAL_SPEED 11999
#define MAX_FORWARD	15999
#define MAX_REVERSE 7999
#define PWM_RANGE 8000
#define POS_NEG_RANGE_DELTA 4000

#define MAX_TEST_SPEED_FWD 13500
#define MAX_TEST_SPEED_REV 10479
#define MAX_ANGLE_VAL 2046
#define MIN_ANGLE_VAL 1023
#define TRAN_TIME 3000
#define MC_OS_DELAY 1

#define DELTA_ANGLE ((MAX_ANGLE_VAL - MIN_ANGLE_VAL) / (TRAN_TIME / MC_OS_DELAY))

#define MAX_COMMAND_VOLTAGE 12.0f
#define MOTOR_VOLTAGE_SCALE_FACTOR ((float)POS_NEG_RANGE_DELTA / MAX_COMMAND_VOLTAGE)

typedef struct {
    float gr_high_setpoint;
    float gr_high_kp;
    float gr_high_ki;
    float gr_high_kd;

    float gr_low_setpoint;
    float gr_low_kp;
    float gr_low_ki;
    float gr_low_kd;

    float rpm_high_setpoint;
    float rpm_high_kp;
    float rpm_high_ki;
    float rpm_high_kd;

    float rpm_low_setpoint;
    float rpm_low_kp;
    float rpm_low_ki;
    float rpm_low_kd;
} PIDConfig;

uint16_t update_setpoint(uint16_t pos_setpoint, uint16_t curr_pos);

uint16_t pid_loop(uint16_t pos_setpoint, uint16_t curr_position);

uint16_t scale_command(const float motor_voltage_command);

void init_pidconfig(PIDConfig* pidconfig);
void update_pidconfig(PIDConfig* pidconfig);

#endif /* INC_MOTOR_CONTROL_H_ */
