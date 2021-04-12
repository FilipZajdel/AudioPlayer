#pragma once

#include "config.h"

/** Setup printing utility in blocking mode.
 *  Args:
 *  uart_handle - The handle to uart/usart
 *  timeout     - The timeout of blocking logger
 */
void utils_print_init(UTILS_UART_USART_HANDLE_TYPE *uart_handle,
                      uint16_t                      timeout);



#define UTILS_LOG_LEVEL_DEBUG 1u
#define UTILS_LOG_LEVEL_INFO  0u

#ifndef UTILS_LOG_LEVEL
#define UTILS_LOG_LEVEL       (UTILS_LOG_LEVEL_DEBUG)
#pragma message("UTILS_LOG_LEVEL is not defined. Using UTILS_LOG_LEVEL_DEBUG.")
#endif

#define STRINGIFY(arg) #arg
#define TO_STR(arg) STRINGIFY(arg)


#define UTILS_PRINT(args...) \
    do { sprintf(utils_get_buf_private(), args); \
         utils_print_private(); } while(0);

#if (UTILS_LOG_LEVEL >= UTILS_LOG_LEVEL_INFO)
#define UTILS_PRINT_INFO(args...) \
    UTILS_PRINT("<info> " args)
#else
#define UTILS_PRINT_INFO(args...)
#endif

#if (UTILS_LOG_LEVEL >= UTILS_LOG_LEVEL_DEBUG)
#define UTILS_PRINT_DEBUG(args...) \
    UTILS_PRINT("<dbg> " __FILE__ ":" TO_STR(__LINE__) " " args)
#else
#define UTILS_PRINT_DEBUG(args...)
#endif

void utils_print_private(void);
char *utils_get_buf_private(void);
