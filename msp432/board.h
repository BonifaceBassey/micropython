

#ifndef __MICROPY_INCLUDED_MSP432P401R_BOARD_H__
#define __MICROPY_INCLUDED_MSP432P401R_BOARD_H__

void uart_init(void);
void uart_tx(int chr);
int uart_rx_data(void);
//int uart_rx_char(void);





#endif // __MICROPY_INCLUDED_MSP432P401R_BOARD_H__
