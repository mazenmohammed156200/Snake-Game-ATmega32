/**
 * @file USART_interface.h
 * @brief Public function declarations for ATmega32 USART driver.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_USART_INTERFACE_H_
#define MCAL_USART_INTERFACE_H_

/**
 * @brief Initializes the USART hardware with specific frame settings.
 * @param[in] synch Synchronous or Asynchronous mode selector.
 * @param[in] SB Number of Stop Bits (1 or 2).
 * @param[in] parity Parity checking configuration (Disabled, Even, Odd).
 * @param[in] data_Mode Frame data size (5 to 9 bits).
 */
void USART_Init(u8 synch, u8 SB, u8 parity, u8 data_Mode);

/**
 * @brief Sends a single byte synchronously via USART.
 * @param[in] data The byte to transmit.
 */
void USART_SendChar(u8 data);

/**
 * @brief Receives a single byte synchronously via USART (blocking call).
 * @return u8 The byte received from UDR.
 */
u8 USART_ReceiveChar(void);

/**
 * @brief Transmits a null-terminated string over USART.
 * @param[in] data Pointer to the string/buffer to be sent.
 */
void USART_SendString(u8 *data);

/**
 * @brief Non-blocking check for received unread data.
 * @return u8 Returns 1 if data is available in RX buffer, 0 otherwise.
 */
u8 USART_Is_Read(void);

#endif /* MCAL_USART_INTERFACE_H_ */