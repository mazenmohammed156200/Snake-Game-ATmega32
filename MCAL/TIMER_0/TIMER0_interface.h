/*
 * TIMER_interface.h
 *
 *  Created on: Sep 2, 2026
 *      Author: ot
 */

#ifndef MCAL_TIMER_0_TIMER0_INTERFACE_H_
#define MCAL_TIMER_0_TIMER0_INTERFACE_H_

#define TIMER0_NO_CLOCK						0
#define TIMER0_PRESCALER_1					1
#define TIMER0_PRESCALER_8					2
#define TIMER0_PRESCALER_64					3
#define TIMER0_PRESCALER_256				4
#define TIMER0_PRESCALER_1024				5
#define TIMER0_EXT_CLOCK_FALLING			6
#define TIMER0_EXT_CLOCK_RISING				7


void TIMER0_Init();
void Timer0_SetPrescaler(u8 prescaler);
void Timer0_OVF0_Interrupt_Enable(u8 enable);
void Timer0_COMP0_Interrupt_Enable(u8 enable);
void Timer0_SetTimerValue(u8 value);
void Timer0_SetCompareValue(u8 value);
u8 Timer0_GetTimerValue();
u8 Timer0_GetCompareValue();
void Timer0_GetCom(f32 ms,f32 *ticks,f32 *overflow);
void Set_Call_Back_OVF(void (*ptr)());
void Set_Call_Back_CTC(void (*ptr)());

#endif /* MCAL_TIMER_0_TIMER0_INTERFACE_H_ */
