/**
 * @file USART_program.c
 * @brief Function implementations for ATmega32 USART driver.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"

#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"

/**
 * @brief Initializes USART registers with custom frame and baud rate parameters.
 */
void USART_Init(u8 synch, u8 SB, u8 parity, u8 Data_Mode)
{
    /* URSEL bit must be 1 when writing to UCSRC */
    u8 UCSRC_Value = (1 << URSEL);

    /* Baud Rate configuration: 9600 Baud @ F_CPU = 8MHz -> UBRR = 51 */
    UBRRH = 0;
    UBRRL = 51;

    /* Select Synchronous / Asynchronous Mode */
    switch (synch)
    {
    case Asynch_Mode:
        CLR_BIT(UCSRC_Value, UMSEL);
        break;
    case synch_Mode:
        SET_BIT(UCSRC_Value, UMSEL);
        break;
    }

    /* Select Stop Bits */
    switch (SB)
    {
    case One_SB:
        CLR_BIT(UCSRC_Value, USBS);
        break;
    case Two_SB:
        SET_BIT(UCSRC_Value, USBS);
        break;
    }

    /* Select Parity Option */
    switch (parity)
    {
    case Disable_Parity:
        CLR_BIT(UCSRC_Value, UPM0);
        CLR_BIT(UCSRC_Value, UPM1);
        break;
    case Even_Parity:
        CLR_BIT(UCSRC_Value, UPM0);
        SET_BIT(UCSRC_Value, UPM1);
        break;
    case Odd_Parity:
        SET_BIT(UCSRC_Value, UPM0);
        SET_BIT(UCSRC_Value, UPM1);
        break;
    }

    /* Select Frame Character Size */
    switch (Data_Mode)
    {
    case Data_Mode_5:
        CLR_BIT(UCSRC_Value, UCSZ0);
        CLR_BIT(UCSRC_Value, UCSZ1);
        CLR_BIT(UCSRB, UCSZ2);
        break;

    case Data_Mode_6:
        SET_BIT(UCSRC_Value, UCSZ0);
        CLR_BIT(UCSRC_Value, UCSZ1);
        CLR_BIT(UCSRB, UCSZ2);
        break;

    case Data_Mode_7:
        CLR_BIT(UCSRC_Value, UCSZ0);
        SET_BIT(UCSRC_Value, UCSZ1);
        CLR_BIT(UCSRB, UCSZ2);
        break;

    case Data_Mode_8:
        SET_BIT(UCSRC_Value, UCSZ0);
        SET_BIT(UCSRC_Value, UCSZ1);
        CLR_BIT(UCSRB, UCSZ2);
        break;

    case Data_Mode_9:
        SET_BIT(UCSRC_Value, UCSZ0);
        SET_BIT(UCSRC_Value, UCSZ1);
        SET_BIT(UCSRB, UCSZ2);
        break;
    }

    /* Write final configuration to UCSRC */
    UCSRC = UCSRC_Value;

    /* Enable Receiver and Transmitter Hardware */
    SET_BIT(UCSRB, TXEN);
    SET_BIT(UCSRB, RXEN);
}

/**
 * @brief Sends a single byte over USART synchronously.
 */
void USART_SendChar(u8 data)
{
    /* Wait for Transmit Data Register Empty flag */
    while (GET_BIT(UCSRA, UDRE) == 0);
    UDR = data;
}

/**
 * @brief Receives a single byte over USART synchronously.
 */
u8 USART_ReceiveChar(void)
{
    /* Wait for Receive Complete flag */
    while (GET_BIT(UCSRA, RXC) == 0);
    return UDR;
}

/**
 * @brief Transmits a null-terminated string over USART.
 */
void USART_SendString(u8 *data)
{
    u8 Iterator = 0;
    while (data[Iterator] != '\0')
    {
        USART_SendChar(data[Iterator]);
        Iterator++;
    }
}

/**
 * @brief Checks if there is any unread byte in the RX buffer.
 */
u8 USART_Is_Read(void)
{
    return GET_BIT(UCSRA, RXC);
}