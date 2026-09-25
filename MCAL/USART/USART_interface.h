#ifndef MCAL_USART_INTERFACE_H_
#define MCAL_USART_INTERFACE_H_

void USART_Init(u8 synch,u8 SB,u8 parity,u8 data_Mode);

void USART_SendChar(u8 data);

u8 USART_ReceiveChar();

void USART_SendString(u8 *data);
u8 USART_Is_Read();
#endif
