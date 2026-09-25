/*
 * TIMER_private.h
 *
 *  Created on: Sep 2, 2026
 *      Author: ot
 */

#ifndef MCAL_TIMER_0_TIMER0_PRIVATE_H_
#define MCAL_TIMER_0_TIMER0_PRIVATE_H_

#define TIMER0_NORMAL		0
#define TIMER0_CTC			1
#define TIMER0_FAST_PWM		2
#define TIMER0_PHASE_PWM	3

#define TCCR0		(*(volatile u8 *)(0x53))
#define TCNT0		(*(volatile u8 *)(0x52))
#define OCR0		(*(volatile u8 *)(0x5C))
#define TIMSK		(*(volatile u8 *)(0x59))
#define TIFR		(*(volatile u8 *)(0x58))
#define NULL 		((void*)0)


#define 	FOC0	7
#define 	WGM00	6
#define		COM01	5
#define	 	COM00	4
#define 	WGM01	3
#define 	CS02	2
#define 	CS01	1
#define 	CS00	0

#define		OCIE0	1
#define 	TOIE0	0

#define		OCF0 	1
#define		TOV0	0

#define Timer0_OC_Normal		0
#define Timer0_OC_TOG			1
#define Timer0_OC_CLR			2
#define Timer0_OC_SET			3


#endif /* MCAL_TIMER_0_TIMER0_PRIVATE_H_ */
