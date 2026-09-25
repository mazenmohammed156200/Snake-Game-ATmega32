/**
 * @file TIMER0_interface.h
 * @brief Interface header for ATmega32 Timer0 module.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#ifndef MCAL_TIMER_0_TIMER0_INTERFACE_H_
#define MCAL_TIMER_0_TIMER0_INTERFACE_H_

/** @defgroup Timer0_ClockSelect Clock Source / Prescaler Configurations */
/**@{*/
#define TIMER0_NO_CLOCK               0  /**< No clock source (Timer/Counter stopped) */
#define TIMER0_PRESCALER_1            1  /**< clkI/O / 1 (No prescaling) */
#define TIMER0_PRESCALER_8            2  /**< clkI/O / 8 */
#define TIMER0_PRESCALER_64           3  /**< clkI/O / 64 */
#define TIMER0_PRESCALER_256          4  /**< clkI/O / 256 */
#define TIMER0_PRESCALER_1024         5  /**< clkI/O / 1024 */
#define TIMER0_EXT_CLOCK_FALLING      6  /**< External clock source on T0 pin (Clock on falling edge) */
#define TIMER0_EXT_CLOCK_RISING       7  /**< External clock source on T0 pin (Clock on rising edge) */
/**@}*/

/**
 * @brief Initializes Timer0 hardware peripheral according to static configurations.
 * @return void
 */
void TIMER0_Init(void);

/**
 * @brief Sets the clock prescaler dynamically.
 * @param[in] prescaler Desired clock source or prescaler selection bitmask.
 * @return void
 */
void Timer0_SetPrescaler(u8 prescaler);

/**
 * @brief Enables or disables Timer0 Overflow Interrupt.
 * @param[in] enable Pass 1 to enable interrupt, 0 to disable.
 * @return void
 */
void Timer0_OVF0_Interrupt_Enable(u8 enable);

/**
 * @brief Enables or disables Timer0 Compare Match Interrupt.
 * @param[in] enable Pass 1 to enable interrupt, 0 to disable.
 * @return void
 */
void Timer0_COMP0_Interrupt_Enable(u8 enable);

/**
 * @brief Sets initial value directly into Timer/Counter Register (TCNT0).
 * @param[in] value 8-bit counter value (0-255).
 * @return void
 */
void Timer0_SetTimerValue(u8 value);

/**
 * @brief Sets compare match value into Output Compare Register (OCR0).
 * @param[in] value 8-bit compare value (0-255).
 * @return void
 */
void Timer0_SetCompareValue(u8 value);

/**
 * @brief Reads current count value from TCNT0 register.
 * @return u8 Current counter value (0-255).
 */
u8 Timer0_GetTimerValue(void);

/**
 * @brief Reads compare threshold stored in OCR0 register.
 * @return u8 Current compare value (0-255).
 */
u8 Timer0_GetCompareValue(void);

/**
 * @brief Computes required tick counts and overflow counts for desired time in milliseconds.
 * @param[in] ms Target time duration in milliseconds.
 * @param[out] ticks Calculated residual ticks for preload.
 * @param[out] overflow Calculated number of required overflows.
 * @return void
 */
void Timer0_GetCom(f32 ms, f32 *ticks, f32 *overflow);

/**
 * @brief Registers user callback function for Overflow ISR.
 * @param[in] ptr Pointer to function executed upon Timer0 overflow.
 * @return void
 */
void Set_Call_Back_OVF(void (*ptr)(void));

/**
 * @brief Registers user callback function for Compare Match ISR.
 * @param[in] ptr Pointer to function executed upon Compare Match.
 * @return void
 */
void Set_Call_Back_CTC(void (*ptr)(void));

#endif /* MCAL_TIMER_0_TIMER0_INTERFACE_H_ */