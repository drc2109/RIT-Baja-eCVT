/*
 * sensor_conversion.h
 *
 *  Created on: Apr 9, 2026
 *      Author: jells
 */

#ifndef INC_SENSOR_CONVERSION_H_
#define INC_SENSOR_CONVERSION_H_

#include <stdint.h>
#include <math.h>

#define PICKUPS 9
#define RADS_PER_PICKUP (2.0f * (float)M_PI / (float)PICKUPS)
#define TIMCLKSPD 1000000.0f
#define MEGA_RADS_PER_PICKUP (TIMCLKSPD * RADS_PER_PICKUP)

#define MAX_ADC_READING 3000.0f
#define MIN_ADC_READING 300.0f
#define MAX_ANGLE (float)(M_PI * 2.0f)
#define ADC_CONV_SCALE_FACTOR (MAX_ANGLE / (MAX_ADC_READING-MIN_ADC_READING))

float pickup_dt_to_rad_per_sec(const uint32_t pickup_dt);

float adc12b_to_rad(const uint16_t adc_angle);

#endif /* INC_SENSOR_CONVERSION_H_ */
