#include <string.h>
#include <stdint.h>

#include "config.h"

#define USART_UART_TX UTILS_UART_USART_TX_FUNC

static struct utils_print_config {
    UTILS_UART_USART_HANDLE_TYPE *uart;
    char uart_buffer[UTILS_PRINT_BUFFER_SIZE];
    uint16_t timeout;
} print_config;


/* Public Api */

void utils_print_init(UTILS_UART_USART_HANDLE_TYPE *uart, uint16_t timeout)
{
    print_config.uart = uart;
    print_config.timeout = timeout;
    memset(print_config.uart_buffer, 0, sizeof(print_config.uart_buffer));
}



/* Private functions */

/**
 *  Returns the negative when message length exceeds max_len.
 *  Otherwise returns the len of message.
 */
int strlen_or_err(char *message, uint16_t max_len)
{
    int len = 0;
    char *cptr = message;
    int ret = -1;
    /* validate max_len */

    while ((len < max_len) && *cptr) {
        cptr++;
        len++;
    }

    /* max_len exceeded */
    if (*cptr && (len == max_len)) {
        ret = -1;
    } else if (!(*cptr) && (len < max_len)) {
        ret = len;
    } else {
        ret = -1;
    }

    return ret;
}

char *utils_get_buf_private(void)
{
    return print_config.uart_buffer;
}

void utils_print_private(void)
{
    int message_len = strlen_or_err(print_config.uart_buffer,
                                    sizeof(print_config.uart_buffer));

    if (message_len > 0) {
        USART_UART_TX(print_config.uart, (uint8_t*)print_config.uart_buffer,
                      message_len, print_config.timeout);
    }
}
