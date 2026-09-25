/*
 * ADC_program.c
 *
 *  Created on: Sep 1, 2026
 *      Author: ot
 */

#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"
#include"../DIO/DIO_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"

u16 int_reading;
void ADC_Init(){


	CLR_BIT(SREG,SREG_E);

	SET_BIT(ADCSRA,ADIE);
	CLR_BIT(ADCSRA,ADEN);
	//ref
	ADMUX=CH_select;
	//prescaler
	ADCSRA |= ADC_64_PRE;
	//enable
	SET_BIT(ADCSRA,ADEN);


}
u16 ADC_ReadSynch(u8 channel){
	u16 reading=0;
	ADMUX &= 0xE0;
	ADMUX |= channel;

	SET_BIT(ADCSRA,ADSC);

	while(GET_BIT(ADCSRA,ADIF)!=1);
	SET_BIT(ADCSRA,ADIF);
	reading=ADCL;
	reading |=((u16)ADCH<<8);

	return reading;
}

u16 ADC_ReadAsynch(u8 channel){
	ADMUX &= 0xE0;
	ADMUX |= channel;
	SET_BIT(SREG,SREG_E);

	SET_BIT(ADCSRA,ADIE);

	SET_BIT(ADCSRA,ADSC);
}


void __vector_16() __attribute__((signal,used));
void __vector_16(){
	int_reading=ADCL;
	int_reading|=((u16)ADCH<<8);
}
