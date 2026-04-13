/*
 * sensor_filter.c
 *
 *  Created on: Mar 31, 2026
 *      Author: jells
 */



#include "sensor_filter.h"


// Initialize
void dma_speed_fifo_init(SPEED_FIFO *fifo) {
    memset(fifo->buf, 0, sizeof(fifo->buf));
    fifo->read_head = 0;
    fifo->buf_size  = DMA_FIFO_BUF_SIZE;
}

void dma_ang_fifo_init(ANG_FIFO *fifo) {
    memset(fifo->buf, 0, sizeof(fifo->buf));
    fifo->read_head = 0;
    fifo->buf_size  = DMA_FIFO_BUF_SIZE;
}


// Pass in your DMA handle to get current write position
uint16_t dma_speed_fifo_tail(SPEED_FIFO *fifo, DMA_HandleTypeDef *hdma) {
    return fifo->buf_size - __HAL_DMA_GET_COUNTER(hdma);
}

uint16_t dma_speed_fifo_available(SPEED_FIFO *fifo, DMA_HandleTypeDef *hdma) {
    uint16_t tail = dma_speed_fifo_tail(fifo, hdma);
    if (tail >= fifo->read_head)
        return tail - fifo->read_head;
    else
        return fifo->buf_size - fifo->read_head + tail;
}

uint32_t dma_speed_fifo_read_single(SPEED_FIFO *fifo) {
    uint32_t byte   = fifo->buf[fifo->read_head];
    fifo->read_head = (fifo->read_head + 1) % fifo->buf_size;
    return byte;
}

bool dma_speed_fifo_read(SPEED_FIFO *fifo, DMA_HandleTypeDef *hdma, uint32_t *out, uint16_t n) {
    if (dma_speed_fifo_available(fifo, hdma) < n) return false;
    for (uint16_t i = 0; i < n; i++)
        out[i] = dma_speed_fifo_read_single(fifo);
    return true;
}

// Pass in your DMA handle to get current write position
uint16_t dma_ang_fifo_tail(ANG_FIFO *fifo, DMA_HandleTypeDef *hdma) {
    return fifo->buf_size - __HAL_DMA_GET_COUNTER(hdma);
}

uint16_t dma_ang_fifo_available(ANG_FIFO *fifo, DMA_HandleTypeDef *hdma) {
    uint16_t tail = dma_ang_fifo_tail(fifo, hdma);
    if (tail >= fifo->read_head)
        return tail - fifo->read_head;
    else
        return fifo->buf_size - fifo->read_head + tail;
}

uint8_t dma_ang_fifo_read_single(ANG_FIFO *fifo) {
    uint8_t byte   = fifo->buf[fifo->read_head];
    fifo->read_head = (fifo->read_head + 1) % fifo->buf_size;
    return byte;
}

bool dma_ang_fifo_read(ANG_FIFO *fifo, DMA_HandleTypeDef *hdma, uint16_t *out, uint16_t n) {
    if (dma_ang_fifo_available(fifo, hdma) < n) return false;
    for (uint16_t i = 0; i < n; i++)
        out[i] = dma_ang_fifo_read_single(fifo);
    return true;
}

uint16_t moving_average_filter_helix(uint16_t new_sample) {
    static uint16_t buffer[MA_FILT_SIZE] = {0};
    static size_t index = 0;
    static uint16_t sum = 0;

    // Subtract the oldest sample, add the new one
    sum -= buffer[index];
    buffer[index] = new_sample;
    sum += new_sample;

    // Advance circular index
    index = (index + 1) % MA_FILT_SIZE;

    return sum / MA_FILT_SIZE;
}

uint16_t moving_average_filter_throttle(uint16_t new_sample) {
    static uint16_t buffer[MA_FILT_SIZE] = {0};
    static size_t index = 0;
    static uint16_t sum = 0;

    // Subtract the oldest sample, add the new one
    sum -= buffer[index];
    buffer[index] = new_sample;
    sum += new_sample;

    // Advance circular index
    index = (index + 1) % MA_FILT_SIZE;

    return sum / MA_FILT_SIZE;
}

uint32_t moving_average_filter_prim_speed(uint16_t new_sample) {
    static uint32_t buffer[MA_FILT_SIZE] = {0};
    static size_t index = 0;
    static uint32_t sum = 0;

    // Subtract the oldest sample, add the new one
    sum -= buffer[index];
    buffer[index] = new_sample;
    sum += new_sample;

    // Advance circular index
    index = (index + 1) % MA_FILT_SIZE;

    return sum / MA_FILT_SIZE;
}

uint32_t moving_average_filter_sec_speed(uint16_t new_sample) {
    static uint32_t buffer[MA_FILT_SIZE] = {0};
    static size_t index = 0;
    static uint32_t sum = 0;

    // Subtract the oldest sample, add the new one
    sum -= buffer[index];
    buffer[index] = new_sample;
    sum += new_sample;

    // Advance circular index
    index = (index + 1) % MA_FILT_SIZE;

    return sum / MA_FILT_SIZE;
}
