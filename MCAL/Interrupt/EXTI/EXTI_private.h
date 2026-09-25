/*
 * EXTI_private.h
 *
 *  Created on: Aug 31, 2026
 *      Author: ot
 */

#ifndef EXTI_EXTI_PRIVATE_H_
#define EXTI_EXTI_PRIVATE_H_


#define GICR		(*(u8 *)(0x5B))
#define MCUCR		(*(u8 *)(0x55))
#define MCUCSR		(*(u8 *)(0x54))
#define GIFR		(*(u8 *)(0x5A))


#define INTF1	7
#define INTF0	6
#define INTF2	5


#define ISC11	3
#define ISC10	2
#define ISC01	1
#define ISC00	0
#define ISC2	6


#endif /* EXTI_EXTI_PRIVATE_H_ */
