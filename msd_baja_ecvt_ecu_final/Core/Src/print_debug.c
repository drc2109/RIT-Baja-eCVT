/*
 * print_debug.c
 *
 *  Created on: Mar 18, 2026
 *      Author: jells
 */
#include "print_debug.h"
#include <stdio.h>
#include <stdint.h>

void print_debug_sensor_vals(float prim_rpm, float sec_rpm, float throttle_angle, float helix_angle){
	printf(
			"Primary RPM: %6.3f\n\r"
			"Secondary RPM: %6.3f\n\r"
			"Throttle Angle: %2.3f\n\r"
			"Helix Angle: %2.3f\n\r"
			"\x1B[1;1H", prim_rpm, sec_rpm, throttle_angle, helix_angle);
}
