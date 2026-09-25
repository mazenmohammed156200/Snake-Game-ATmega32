/*
 * DIO_interface.h
 *
 *  Created on: Aug 25, 2026
 *      Author: ot
 */

#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_

#define DIO_PORTA     0
#define DIO_PORTB     1
#define DIO_PORTC     2
#define DIO_PORTD     3

#define DIO_PIN0     0
#define DIO_PIN1     1
#define DIO_PIN2     2
#define DIO_PIN3     3
#define DIO_PIN4     4
#define DIO_PIN5     5
#define DIO_PIN6     6
#define DIO_PIN7     7

#define DIO_LOW      0
#define DIO_HIGH     1

#define DIO_INPUT    0
#define DIO_OUTPUT   1
#define DIO_PULLUP   2

#define DIO_INPUT_PORT   0x00
#define DIO_OUTPUT_PORT   0xFF


void DIO_SetPinDirection(u8 u8_port, u8 pin, u8 direction);

void DIO_SetPinValue(u8 u8_port,u8 pin, u8 value);

u8 DIO_GetPinValue(u8 u8_port,u8 u8_pin);

void DIO_SetPortDirection(u8 u8_port,u8 direction);

void DIO_SetPortValue(u8 u8_port, u8 value);

u8 DIO_GetPortValue(u8 u8_port);

void DIO_TogglePin(u8 port, u8 pin);

void DIO_TogglePORT(u8 port);

#endif /* MCAL_DIO_DIO_INTERFACE_H_ */
