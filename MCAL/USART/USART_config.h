/**
 * @file USART_config.h
 * @brief Configuration constants for ATmega32 USART driver.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_USART_CONFIG_H_
#define MCAL_USART_CONFIG_H_

/* Synchronization Modes */
#define Asynch_Mode        0
#define synch_Mode         1

/* Stop Bit Options */
#define One_SB             0
#define Two_SB             1

/* Parity Bit Options */
#define Disable_Parity     0
#define Even_Parity        1
#define Odd_Parity         2

/* Data Frame Size Options */
#define Data_Mode_5        0
#define Data_Mode_6        1
#define Data_Mode_7        2
#define Data_Mode_8        3
#define Data_Mode_9        4

#endif /* MCAL_USART_CONFIG_H_ */