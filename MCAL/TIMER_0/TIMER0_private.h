/**
 * @file TIMER0_private.h
 * @brief Private definitions and register mappings for Timer0.
 *
 * This file contains the private macros used internally by the
 * Timer0 driver, including Timer0 modes, register addresses,
 * bit positions, and Output Compare configurations.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#ifndef MCAL_TIMER_0_TIMER0_PRIVATE_H_
#define MCAL_TIMER_0_TIMER0_PRIVATE_H_


/**
 * @brief Timer0 operating modes.
 */
#define TIMER0_NORMAL        0
#define TIMER0_CTC           1
#define TIMER0_FAST_PWM      2
#define TIMER0_PHASE_PWM     3


/**
 * @brief Timer0 register memory addresses.
 */
#define TCCR0   (*(volatile u8 *)(0x53))
#define TCNT0   (*(volatile u8 *)(0x52))
#define OCR0    (*(volatile u8 *)(0x5C))
#define TIMSK   (*(volatile u8 *)(0x59))
#define TIFR    (*(volatile u8 *)(0x58))


/**
 * @brief NULL pointer definition.
 */
#define NULL    ((void*)0)


/**
 * @brief TCCR0 register bit positions.
 *
 * TCCR0 (Timer/Counter Control Register) controls the
 * operating mode, Output Compare behavior, and clock source.
 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0


/**
 * @brief TIMSK register bit positions for Timer0 interrupts.
 */
#define OCIE0   1
#define TOIE0   0


/**
 * @brief TIFR register bit positions for Timer0 interrupt flags.
 */
#define OCF0    1
#define TOV0    0


/**
 * @brief Timer0 Output Compare behavior modes.
 *
 * These values define the behavior of the OC0 pin
 * when a Compare Match occurs.
 */
#define Timer0_OC_Normal      0
#define Timer0_OC_TOG         1
#define Timer0_OC_CLR         2
#define Timer0_OC_SET         3


#endif /* MCAL_TIMER_0_TIMER0_PRIVATE_H_ */