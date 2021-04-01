#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "utils.h"


struct utils_print_config print_config;


static int strlen_or_err(char *message, uint16_t max_len);

/* Public Api */
void utils_print_init(UART_HandleTypeDef *uart, uint16_t timeout)
{
    print_config.uart = uart;
    print_config.timeout = timeout;
    memset(print_config.uart_buffer, 0, sizeof(print_config.uart_buffer));
}



/* Private functions */
void utils_print_private(char *message)
{
    int message_len = strlen_or_err(message, sizeof(print_config.uart_buffer));

    if (message_len > 0) {
        HAL_UART_Transmit(print_config.uart, (uint8_t*)message,
                          message_len, print_config.timeout);
    }
}

/**
 *  Returns negative number when message length exceeds max_len.
 *  Otherwise returns the len of message
 */
int strlen_or_err(char *message, uint16_t max_len)
{
    int len = 0;
    char *cptr = message;
    int ret = -1;
    /* validate max_len */
    max_len = max_len < 0 ? -max_len : max_len;

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