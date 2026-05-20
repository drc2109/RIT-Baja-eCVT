/*
 * sensor_filter.h
 *
 *  Created on: Mar 31, 2026
 *      Author: jells
 */

#ifndef INC_SENSOR_FILTER_H_
#define INC_SENSOR_FILTER_H_
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32h7xx_hal.h"


#define DMA_FIFO_BUF_SIZE 4
#define MA_FILT_SIZE 50


typedef struct {
	uint32_t  buf[DMA_FIFO_BUF_SIZE];
    uint16_t read_head;
    uint16_t buf_size;
} SPEED_FIFO;

typedef struct {
	uint16_t  buf[DMA_FIFO_BUF_SIZE];
    uint16_t read_head;
    uint16_t buf_size;
} ANG_FIFO;

void dma_speed_fifo_init(SPEED_FIFO *fifo);

void dma_ang_fifo_init(ANG_FIFO *fifo);


// Pass in your DMA handle to get current write position
uint16_t dma_speed_fifo_tail(SPEED_FIFO *fifo, DMA_HandleTypeDef *hdma);

uint16_t dma_speed_fifo_available(SPEED_FIFO *fifo, DMA_HandleTypeDef *hdma);

uint32_t dma_speed_fifo_read_single(SPEED_FIFO *fifo);

bool dma_speed_fifo_read(SPEED_FIFO *fifo, DMA_HandleTypeDef *hdma, uint32_t *out, uint16_t n);

// Pass in your DMA handle to get current write position
uint16_t dma_ang_fifo_tail(ANG_FIFO *fifo, DMA_HandleTypeDef *hdma);

uint16_t dma_ang_fifo_available(ANG_FIFO *fifo, DMA_HandleTypeDef *hdma);

uint8_t dma_ang_fifo_read_single(ANG_FIFO *fifo);

bool dma_ang_fifo_read(ANG_FIFO *fifo, DMA_HandleTypeDef *hdma, uint16_t *out, uint16_t n);

uint16_t moving_average_filter_helix(uint16_t new_sample);

uint16_t moving_average_filter_throttle(uint16_t new_sample);

uint32_t moving_average_filter_prim_speed(uint16_t new_sample);

uint32_t moving_average_filter_sec_speed(uint16_t new_sample);

float moving_average_filter_curr(float new_sample);

#endif /* INC_SENSOR_FILTER_H_ */
