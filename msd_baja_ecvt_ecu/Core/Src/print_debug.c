/*
 * print_debug.c
 *
 *  Created on: Mar 18, 2026
 *      Author: jells
 */
#include "print_debug.h"
#include <stdio.h>
#include <stdint.h>

void print_debug_sensor_vals(uint32_t prim_rpm, uint32_t sec_rpm, uint16_t throttle_angle, uint16_t helix_angle){
	printf(
			"Primary RPM: %10u\n\r"
			"Secondary RPM: %10u\n\r"
			"Throttle Angle: %4u\n\r"
			"Helix Angle: %4u\n\r"
			"\x1B[1;1H", prim_rpm, sec_rpm, throttle_angle, helix_angle);
}
