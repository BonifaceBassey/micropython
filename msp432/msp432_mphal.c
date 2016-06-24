#include <string.h>
#include <unistd.h>
#include "py/mphal.h"
#include "board.h"


int mp_hal_stdin_rx_chr(void) {
	uint8_t c = 0;
	do{
		c = uart_rx_data();	
	}while(c == 0xFF);
    return c;
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, size_t len) {
    while (len--) {
        uart_tx_char(*str++);
    }
}


// Send "cooked" string of given length, where every occurance of
// LF character is replaced with CR LF.
void mp_hal_stdout_tx_strn_cooked(const char *str, size_t len) {
    for (; len > 0; --len) {
        if (*str == '\n') {
            uart_tx_char('\r');
        }
        uart_tx_char(*str++);
    }
}

// Send zero-terminated string
void mp_hal_stdout_tx_str(const char *str) {
    mp_hal_stdout_tx_strn(str, strlen(str));
}


void mp_hal_delay_ms(mp_uint_t ms){
//__delay_cycles(ms);
}

