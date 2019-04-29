#ifndef __MICROPY_INCLUDED_MSP432P401R_MPHALPORT_H__
#define __MICROPY_INCLUDED_MSP432P401R_MPHALPORT_H__

int mp_hal_stdin_rx_chr(void);
void mp_hal_stdout_tx_strn(const char *str, size_t len);
void mp_hal_stdout_tx_strn_cooked(const char *str, size_t len);
void mp_hal_stdout_tx_str(const char *str);
void mp_hal_delay_ms(mp_uint_t ms);

#endif	// __MICROPY_INCLUDED_MSP432P401R_MPHALPORT_H__
