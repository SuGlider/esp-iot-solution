// Copyright 2015-2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef _IOT_SPI_BUS_H_
#define _IOT_SPI_BUS_H_

#include "driver/spi_master.h"
#include "driver/gpio.h"

#define NULL_SPI_CS_PIN -1
typedef void *spi_bus_handle_t;
typedef void *spi_bus_device_handle_t;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Create and initialize a spi bus and return the spi bus handle
 *
 * @param host_id SPI peripheral that controls this bus, SPI2_HOST or SPI3_HOST
 * @param miso_io_num GPIO pin for Master In Slave Out (=spi_q) signal, or -1 if not used.
 * @param mosi_io_num GPIO pin for Master Out Slave In (=spi_d) signal, or -1 if not used.
 * @param sclk_io_num GPIO pin for Spi CLocK signal, or -1 if not used.
 * @return spi_bus_handle_t handle for spi bus operation.
 */
spi_bus_handle_t spi_bus_create(spi_host_device_t host_id, gpio_num_t miso_io_num, gpio_num_t mosi_io_num, gpio_num_t sclk_io_num);

/**
 * @brief Deinitialize and delete the spi bus
 *
 * @param bus_handle pointer to spi bus handle, if delete succeed handle will set to NULL.
 * @return esp_err_t
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t spi_bus_delete(spi_bus_handle_t *bus_handle);

/**
 * @brief Create and add a device on the spi bus.
 *
 * @param bus_handle handle for spi bus operation.
 * @param cs_io_num GPIO pin to select this device (CS), or -1 if not used
 * @param mode spi mode, modes (0,1,2,3) that correspond to the four possible clocking configurations
 * @param clock_speed_hz spi clock speed, divisors of 80MHz, in Hz. See ``SPI_MASTER_FREQ_*``.
 * @return spi_bus_device_handle_t handle for device operation. eg, using for transfer.
 */
spi_bus_device_handle_t spi_bus_device_create(spi_bus_handle_t bus_handle, gpio_num_t cs_io_num, uint8_t mode, int clock_speed_hz);

/**
 * @brief Deinitialize and remove the device from spi bus.
 *
 * @param device_handle pointer to device handle, if delete succeed handle will set to NULL.
 * @return esp_err_t
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t spi_bus_device_delete(spi_bus_device_handle_t *device_handle);

/**
 * @brief Transfer one byte with the device.
 *
 * @param device_handle handle for device operation.
 * @param data_out data will send to device.
 * @param data_in pointer to receive buffer, set NULL to skip receive phase.
 * @return esp_err_t
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t spi_bus_transfer_byte(spi_bus_device_handle_t device_handle, uint8_t data_out, uint8_t *data_in);

/**
 * @brief Transfer multi-bytes with the device.
 *
 * @param device_handle handle for device operation.
 * @param data_out pointer to sent buffer, set NULL to skip sent phase.
 * @param data_in pointer to receive buffer, set NULL to skip receive phase.
 * @param data_len number of bytes will transfer.
 * @return esp_err_t
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t spi_bus_transfer_bytes(spi_bus_device_handle_t device_handle, const uint8_t *data_out, uint8_t *data_in, uint32_t data_len);

/**
 * @brief Transfer one 16-bit value with the device. using msb by default.
 * For example 0x1234, 0x12 will send first then 0x34.
 *
 * @param device_handle handle for device operation.
 * @param data_out data will send to device.
 * @param data_in pointer to receive buffer, set NULL to skip receive phase.
 * @return esp_err_t
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t spi_bus_transfer_reg16(spi_bus_device_handle_t device_handle, uint16_t data_out, uint16_t *data_in);

/**
 * @brief Transfer one 32-bit value with the device. using msb by default.
 * For example 0x12345678, 0x12 will send first, 0x78 will send in the end.
 *
 * @param device_handle handle for device operation.
 * @param data_out data will send to device.
 * @param data_in pointer to receive buffer, set NULL to skip receive phase.
 * @return esp_err_t
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t spi_bus_transfer_reg32(spi_bus_device_handle_t device_handle, uint32_t data_out, uint32_t *data_in);

#ifdef __cplusplus
}
#endif

#endif

