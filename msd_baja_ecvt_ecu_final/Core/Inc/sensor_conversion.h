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
#define PICKUPS_GB 6

#define RADS_PER_PICKUP (2.0f * (float)M_PI / (float)PICKUPS)
#define RADS_PER_PICKUP_GB (2.0f * (float)M_PI / (float)PICKUPS_GB)

#define TIMCLKSPD 1000000.0f
#define MEGA_RADS_PER_PICKUP (TIMCLKSPD * RADS_PER_PICKUP)
#define MEGA_RADS_PER_PICKUP_GB (TIMCLKSPD * RADS_PER_PICKUP_GB)

#define GB_TO_SEC_CONV_FACTOR 5.9

#define MAX_ADC_READING 4095.0f
#define MIN_ADC_READING 620.0f
#define MAX_ANGLE (float)(M_PI * 2.0f)

#define ADC_CONV_SCALE_FACTOR (MAX_ANGLE / (MAX_ADC_READING-MIN_ADC_READING))
//#define ADC_CONV_SCALE_FACTOR_gearbox (MAX_ANGLE / (MAX_ADC_READING-MIN_ADC_READING))

float pickup_dt_to_rad_per_sec(const uint32_t pickup_dt);

float pickup_dt_to_rad_per_sec_gb(const uint32_t pickup_dt);

float adc12b_to_rad(const uint16_t adc_angle);

float adc12b_to_motor_curr(const uint16_t adc_motor_curr);

typedef struct {
    float helix_angle;
    float throttle_angle;
    float prim_rpm;
    float sec_rpm;
    float motor_curr;
} sensor_data_t;

#endif /* INC_SENSOR_CONVERSION_H_ */
