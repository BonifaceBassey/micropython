/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#include "drivers/inc/msp.h"
#include "drivers/driverlib/MSP432P4xx/driverlib.h"	/* DriverLib Includes */
#include "board.h"
#include "py/mpconfig.h"

/********************************************************************/

//UART

#if MICROPY_MIN_USE_MSP432_MCU
unsigned char receiveData = 0;

const eUSCI_UART_Config uartConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
    78,                                      // BRDIV = 78
    2,                                       // UCxBRF = 2
    0,                                       // UCxBRS = 0
    EUSCI_A_UART_NO_PARITY,                  // No Parity
    EUSCI_A_UART_LSB_FIRST,                  // MSB First
    EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
    EUSCI_A_UART_MODE,                       // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

//Receive byte via USCIA0 interrupt handler.
void EUSCIA0_IRQHandler(void)
{
    //while(!(UCA0IFG & UCTXIFG));		 handled by UART_transmitData()
    if (UCA0RXBUF != '\n'){	
        receiveData = UART_receiveData(EUSCI_A0_BASE);
	//receiveByte = UCA0RXBUF;
    }
}

// init
void uart_init(void)
{
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

    /*Enable UART interrupt */
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA0);
	Interrupt_enableMaster();
}

// Send string of given length
void uart_tx_char(int chr)
{
    //while(!(IFG2 & UCA0TXIFG)); 	// Wait until TXREG is empty, handled by UART_transmitData()
    UART_transmitData(EUSCI_A0_BASE, chr);
}


// Receive data
int uart_rx_data(void)
{
    return(receiveData); 
}

/*
// character
int uart_rx_char(void)
{
// interrupt flag IFG2[UCA0RXIFG] checks if a char is recieved, then reads char from UCA0RXBUF
    int chr = -1;
 
    //if (IFG2 & UCA0RXIFG) {
        chr = UCA0RXBUF;
    //}
 
    return chr;
}
*/
#endif
