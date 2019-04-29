#ifndef __MICROPY_INCLUDED_MSP432P401R_UART_H__
#define __MICROPY_INCLUDED_MSP432P401R_UART_H__

void uart_init(void);
void uart_tx_char(int chr);
int uart_rx_data(void);

#endif // __MICROPY_INCLUDED_MSP432P401R_UART_H__
