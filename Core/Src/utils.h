#pragma once

#define UTILS_LOG_LEVEL_DEBUG (1)   /* The most verbose logging level */
#define UTILS_LOG_LEVEL_INFO  (0)   /* The most modest logging level */
#define UTILS_PRINT_BUFFER_SIZE 128



#ifndef UTILS_LOG_LEVEL
#define UTILS_LOG_LEVEL       (UTILS_LOG_LEVEL_DEBUG)
#endif


struct utils_print_config {
    UART_HandleTypeDef *uart;
    char uart_buffer[UTILS_PRINT_BUFFER_SIZE];
    uint16_t timeout;
};

extern struct utils_print_config print_config;



void utils_print_init(UART_HandleTypeDef *uart_handle, uint16_t timeout);

#if (UTILS_LOG_LEVEL >= UTILS_LOG_LEVEL_INFO)
#define UTILS_PRINT_INFO(args...) \
    do { sprintf(print_config.uart_buffer, args); \
         utils_print_private(args); } while(0);
#else
#endif

#if (UTILS_LOG_LEVEL >= UTILS_LOG_LEVEL_DEBUG)
#define UTILS_PRINT_DEBUG(args...) \
    do { sprintf(print_config.uart_buffer, args); \
         utils_print_private(args); } while(0);
#else
#endif

void utils_print_private(char *message);
