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

float pickup_dt_to_rad_per_sec_gb(const uint32_t pickup_dt){
	if (pickup_dt == 0) return 0.0f;
	return GB_TO_SEC_CONV_FACTOR * MEGA_RADS_PER_PICKUP_GB / (float)pickup_dt;
}

float adc12b_to_rad(const uint16_t adc_angle){
	float converted_value = ((float)(adc_angle - MIN_ADC_READING))*ADC_CONV_SCALE_FACTOR;
	return converted_value;

}


float adc12b_to_motor_curr(const uint16_t adc_motor_curr){
	const float adc_ref_v = 3.3f;
	const float v_offset = 2.5642f;
	static float transimpedance = 0.066;

	float vin = (((float)adc_motor_curr)/4095.0f)*adc_ref_v;
	float vin_no_offset = vin-v_offset;
	return (vin_no_offset)/transimpedance;
}
