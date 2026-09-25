/*
 * ADC_private.h
 *
 *  Created on: Sep 1, 2026
 *      Author: ot
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define SFIOR		(*(u8 *)(0x50))
#define ADCSRA		(*(u8 *)(0x26))
#define ADMUX		(*(u8 *)(0x27))
#define ADCH		(*(u8 *)(0x25))
#define ADCL		(*(u8 *)(0x24))
#define SREG		(*(u8 *)(0x5F))
//ADCMUX
#define REFS1		7
#define REFS0		6
#define ADLAR		5
#define MUX4		4
#define MUX3		3
#define MUX2 		2
#define MUX1		1
#define MUX0		0
//ADCSRA
#define	ADEN 		7
#define ADSC		6
#define ADATE		5
#define ADIF		4 //polling
#define ADIE		3 //interrupt
#define ADPS2		2
#define ADPS1		1
#define ADPS0		0

#define CH_select	0xC0
#define ADC_64_PRE	0X06

//#define ADC_PORT	DIO_PORTA
#define ADC_PIN0 	DIO_PIN0
#define ADC_PIN1 	DIO_PIN1
#define ADC_PIN2 	DIO_PIN2
#define ADC_PIN3 	DIO_PIN3
#define ADC_PIN4 	DIO_PIN4
#define ADC_PIN5 	DIO_PIN5
#define ADC_PIN6 	DIO_PIN6
#define ADC_PIN7 	DIO_PIN7

#define SREG_E		DIO_PIN7

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
