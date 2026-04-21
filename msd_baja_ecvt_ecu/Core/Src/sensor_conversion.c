/*
 * sensor_conversion.c
 *
 *  Created on: Apr 9, 2026
 *      Author: jells
 */
#include "sensor_conversion.h"

float pickup_dt_to_rad_per_sec(const uint32_t pickup_dt){
	if (pickup_dt == 0) return 0.0f;
	return MEGA_RADS_PER_PICKUP / (float)pickup_dt;
}

float adc12b_to_rad(const uint16_t adc_angle){
	return ((float)(adc_angle - MIN_ADC_READING))*ADC_CONV_SCALE_FACTOR;
}
