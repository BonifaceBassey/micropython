/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/include/driverlib.h"	/* DriverLib Includes */
#include "include/msp432p401r_uart.h"

/********************************************************************/
//UART
#define MSP432_UART	(1)

#if MSP432_UART
/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 9600 baud rate, 12MHz clock. These
 * values were calculated using the online calculator that TI provides
 * at:
 * http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 */
const eUSCI_UART_Config uartConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
    78,                                      // BRDIV = 78 (clock prescaler)
    2,                                       // UCxBRF = 2 (firstModReg)
    0,                                       // UCxBRS = 0 (secondModReg)
    EUSCI_A_UART_NO_PARITY,                  // No Parity
    EUSCI_A_UART_LSB_FIRST,                  // MSB First
    EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
    EUSCI_A_UART_MODE,                       // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

//Receive byte via USCIA0 interrupt handler.
void EUSCIA0_IRQHandler(void)
{

} 

// init
void uart_init(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    /* Configure pins P1.2 and P1.3 in UART mode.
     * Doesn't matter if they are set to inputs or outputs
     */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO (clock) to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    /* Configuring UART Module */
    UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    UART_enableModule(EUSCI_A0_BASE);

    /*Enabling UART interrupts */
    //UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    //Interrupt_enableInterrupt(INT_EUSCIA0);
    //Interrupt_enableSleepOnIsrExit();
    Interrupt_enableMaster();
}

// Send string of given length
void uart_tx_char(int chr)
{
    // wait for TXE --> handled by UART_transmitData(EUSCI_A0_BASE, transmitData) function
    UART_transmitData(EUSCI_A0_BASE, chr);
}


// Receive data
int uart_rx_data(void)
{	
	int chr = 0xFF;
	if(UCA0IFG & UCRXIFG0 ){
		chr = UCA0RXBUF;	
	}
	return chr;	
}

#endif
