/**
 * @file TIMER0_config.h
 * @brief Static configuration parameters for ATmega32 Timer/Counter0 driver.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#ifndef MCAL_TIMER_0_TIMER0_CONFIG_H_
#define MCAL_TIMER_0_TIMER0_CONFIG_H_

/** 
 * @brief Select Timer0 Operating Mode.
 * Options: TIMER0_NORMAL, TIMER0_CTC, TIMER0_FAST_PWM, TIMER0_PHASE_PWM 
 */
#define Timer0_Mode             TIMER0_CTC

/** 
 * @brief Select Output Compare Pin (OC0) Behavior.
 * Options: Timer0_OC_Normal, Timer0_OC_TOG, Timer0_OC_CLR, Timer0_OC_SET 
 */
#define Timer0_OC_Mode          Timer0_OC_Normal

/** 
 * @brief Select Clock Prescaler Value.
 * Options: TIMER0_NO_CLOCK, TIMER0_PRESCALER_1, TIMER0_PRESCALER_8, 
 *          TIMER0_PRESCALER_64, TIMER0_PRESCALER_256, TIMER0_PRESCALER_1024,
 *          TIMER0_EXT_CLOCK_FALLING, TIMER0_EXT_CLOCK_RISING
 */
#define TIMER0_PRESCALER_VALUE  TIMER0_PRESCALER_64

#endif /* MCAL_TIMER_0_TIMER0_CONFIG_H_ */