/*
 * USART_program.c
 *
 *  Created on: Sep 6, 2026
 *      Author: ot
 */

#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"

#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"

void USART_Init(u8 synch,u8 SB,u8 parity,u8 Data_Mode)
{
	  u8 UCSRC_Value = (1 << URSEL);

	  // Baud Rate  9600
	  // F_CPU    8MHZ
	  // UBRR      51.083

	  UBRRH = 0;
	  UBRRL = 51;

	  switch(synch)
	  {
	  case Asynch_Mode: CLR_BIT(UCSRC_Value, UMSEL); break;

	  case synch_Mode: SET_BIT(UCSRC_Value, UMSEL); break;
	  }

	  switch(SB)
	  {
	  case One_SB:CLR_BIT(UCSRC_Value, USBS); break;

	  case Two_SB:SET_BIT(UCSRC_Value, USBS); break;
	  }

	  switch(parity)
	  {
	  case Disable_Parity: CLR_BIT(UCSRC_Value, UPM0); CLR_BIT(UCSRC_Value, UPM1); break;

	  case Even_Parity: CLR_BIT(UCSRC_Value, UPM0); SET_BIT(UCSRC_Value, UPM1); break;

	  case Odd_Parity: SET_BIT(UCSRC_Value, UPM0); SET_BIT(UCSRC_Value, UPM1); break;
	  }

	  switch(Data_Mode)
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

	  UCSRC = UCSRC_Value;

	  // Enable transmitter and receiver interrupt

	  SET_BIT(UCSRB, TXEN);
	  SET_BIT(UCSRB, RXEN);

	}
void USART_SendChar(u8 data){
	while(GET_BIT(UCSRA,UDRE)==0);
	UDR=data;


}

u8 USART_ReceiveChar(){
	while(GET_BIT(UCSRA,RXC)==0);
	return UDR;
}

void USART_SendString(u8 *data){
	u8 Iterator=0;
	while(data[Iterator]!='\0'){
		 USART_SendChar(data[Iterator]);
		 Iterator++;
	}

}

u8 USART_Is_Read()
{
	return GET_BIT(UCSRA, RXC);
}
