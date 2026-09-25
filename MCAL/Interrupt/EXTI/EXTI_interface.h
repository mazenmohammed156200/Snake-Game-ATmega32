/*
 * EXTI_interface.h
 *
 *  Created on: Aug 31, 2026
 *      Author: ot
 */

#ifndef EXTI_EXTI_INTERFACE_H_
#define EXTI_EXTI_INTERFACE_H_


#define INT1	7
#define INT0	6
#define INT2	5

#define EXTI_LOW_LOGIC	0
#define EXTI_ANY_LOGIC	1
#define EXTI_RISING		2
#define EXTI_FALLING	3

void EXTI_Enable(u8 EXTI_id);
void EXTI_Disable(u8 EXTI_id);
void EXTI_SenseControl(u8 EXTI_id,u8 sense);
#endif /* EXTI_EXTI_INTERFACE_H_ */
