#include <util/delay.h>
#include "STD.h"
#include "BIT_MATH.h"
#include "DIO_config.h"
#include "DIO_private.h"
#include "DIO_interface.h"



void DIO_SetPinDirection(u8 u8_port, u8 pin, u8 direction){
  switch(direction){
    case DIO_INPUT:
      switch(u8_port){
        case DIO_PORTA:
          CLR_BIT(DDRA, pin);
          break;

        case DIO_PORTB:
          CLR_BIT(DDRB, pin);
          break;

        case DIO_PORTC:
          CLR_BIT(DDRC, pin);
          break;

        case DIO_PORTD:
          CLR_BIT(DDRD, pin);
          break;
		default :
			break;
      }
      break;

    case DIO_OUTPUT:
      switch(u8_port){
        case DIO_PORTA:
          SET_BIT(DDRA, pin);
          break;

        case DIO_PORTB:
          SET_BIT(DDRB, pin);
          break;

        case DIO_PORTC:
          SET_BIT(DDRC, pin);
          break;

        case DIO_PORTD:
          SET_BIT(DDRD, pin);
          break;
		default :
			break;
      }
      break;

    case DIO_PULLUP:
      switch(u8_port){
        case DIO_PORTA:
          CLR_BIT(DDRA, pin);
          SET_BIT(PORTA, pin);
          break;

        case DIO_PORTB:
          CLR_BIT(DDRB, pin);
          SET_BIT(PORTB, pin);
          break;

        case DIO_PORTC:
          CLR_BIT(DDRC, pin);
          SET_BIT(PORTC, pin);
          break;

        case DIO_PORTD:
          CLR_BIT(DDRD, pin);
          SET_BIT(PORTD, pin);
          break;
		default :
			break;
      }
      break;
  }
}

void DIO_SetPinValue(u8 u8_port,u8 pin, u8 value){

	switch (value){
	case DIO_HIGH :
		switch(u8_port){
			case DIO_PORTA:
				SET_BIT(PORTA,pin);
				break;
			case DIO_PORTB:
				SET_BIT(PORTB,pin);
				break;
			case DIO_PORTC:
				SET_BIT(PORTC,pin);
				break;
			case DIO_PORTD:
				SET_BIT(PORTD,pin);
				break;
			default :
				break;
		}
		break;
	case DIO_LOW :
		switch(u8_port){
			case DIO_PORTA:
				CLR_BIT(PORTA,pin);
				break;
			case DIO_PORTB:
				CLR_BIT(PORTB,pin);
				break;
			case DIO_PORTC:
				CLR_BIT(PORTC,pin);
				break;
			case DIO_PORTD:
				CLR_BIT(PORTD,pin);
				break;
			default :
				break;
		}
		break;
	}

}

u8 DIO_GetPinValue(u8 u8_port,u8 u8_pin){
	switch(u8_port){
		case DIO_PORTA:
			return GET_BIT(PINA,u8_pin);
		case DIO_PORTB:
			return GET_BIT(PINB,u8_pin);
		case DIO_PORTC:
			return GET_BIT(PINC,u8_pin);
		case DIO_PORTD:
			return GET_BIT(PIND,u8_pin);
		default :
			break;
	}
}

void DIO_SetPortDirection(u8 u8_port,u8 direction){
  switch(direction){
    case DIO_INPUT:
      switch(u8_port){
        case DIO_PORTA:
        	DDRA=DIO_INPUT_PORT;
        	break;

        case DIO_PORTB:
        	DDRB=DIO_INPUT_PORT;
          break;

        case DIO_PORTC:
        	DDRC=DIO_INPUT_PORT;
          break;

        case DIO_PORTD:
        	DDRD=DIO_INPUT_PORT;
          break;
		default :
			break;
      }
      break;

    case DIO_OUTPUT:
      switch(u8_port){
        case DIO_PORTA:
          DDRA=DIO_OUTPUT_PORT;
          break;

        case DIO_PORTB:
            DDRB=DIO_OUTPUT_PORT;
          break;

        case DIO_PORTC:
            DDRC=DIO_OUTPUT_PORT;
          break;

        case DIO_PORTD:
            DDRD=DIO_OUTPUT_PORT;
          break;
		default :
			break;
      }
      break;

    case DIO_PULLUP:
      switch(u8_port){
        case DIO_PORTA:
          DDRA=DIO_INPUT_PORT;
          PORTA=DIO_OUTPUT_PORT;
          break;

        case DIO_PORTB:
            DDRB=DIO_INPUT_PORT;
            PORTB=DIO_OUTPUT_PORT;
          break;

        case DIO_PORTC:
            DDRC=DIO_INPUT_PORT;
            PORTC=DIO_OUTPUT_PORT;
          break;

        case DIO_PORTD:
            DDRD=DIO_INPUT_PORT;
            PORTD=DIO_OUTPUT_PORT;
          break;
		default :
			break;
      }
      break;
  }
}

void DIO_SetPortValue(u8 u8_port, u8 value){

	switch (u8_port){
	case DIO_PORTA :
		PORTA=value;
		break;
	case DIO_PORTB :
			PORTB=value;
			break;
	case DIO_PORTC :
			PORTC=value;
			break;
	case DIO_PORTD :
			PORTD=value;
			break;
			default :
				break;

		break;
	}
}

u8 DIO_GetPortValue(u8 u8_port){
  switch(u8_port){
    case DIO_PORTA:
      return PINA;

    case DIO_PORTB:
      return PINB;

    case DIO_PORTC:
      return PINC;

    case DIO_PORTD:
      return PIND;

    default:
      return 0;
  }
}

void DIO_TogglePin(u8 port, u8 pin){
	switch (port){
		case DIO_PORTA:
			TOG_BIT(PORTA,pin);
			break;
		case DIO_PORTB:
			TOG_BIT(PORTB,pin);
			break;
		case DIO_PORTC:
			TOG_BIT(PORTC,pin);
			break;
		case DIO_PORTD:
			TOG_BIT(PORTD,pin);
			break;

	}
}

void DIO_TogglePORT(u8 port){
	switch(port){
	case DIO_PORTA:
		PORTA=~PORTA;
		break;
	case DIO_PORTB:
		PORTB=~PORTB;
		break;
	case DIO_PORTC:
		PORTC=~PORTC;
		break;
	case DIO_PORTD:
		PORTD=~PORTD;
		break;

	}
}
