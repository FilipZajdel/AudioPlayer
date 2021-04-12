#pragma once

#include "main.h" /* For access to hal functions */


/**
 * The project config file. Every configurable define should be here.
 *
 * This should be included where needed.
 *
 */

/** Application config **/

/* The number of audio samples sent in each I2S transaction */
#define APP_AUDIO_BUFFER_SIZE 2U
#define APP_UART_LOGGER_TIMEOUT_MS 50U

/** Utils config **/

/**
 *  Logging level. To be chosen one out of:
 *  - UTILS_LOG_LEVEL_DEBUB - The most verbose logging level
 *  - UTILS_LOG_LEVEL_INFO  - The most modest logging level
 */
#define UTILS_LOG_LEVEL (UTILS_LOG_LEVEL_DEBUG)

/* The size of buffer used to logging. Expressed in bytes. */
#define UTILS_PRINT_BUFFER_SIZE 128U

/* The hal typedef of uart/usart handle. */
#define UTILS_UART_USART_HANDLE_TYPE UART_HandleTypeDef

/* The hal function used to send data over uart/usart */
#define UTILS_UART_USART_TX_FUNC HAL_UART_Transmit
