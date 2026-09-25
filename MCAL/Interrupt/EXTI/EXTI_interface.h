/**
 * @file EXTI_interface.h
 * @brief Interface header for ATmega32 External Interrupts (EXTI) driver.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#ifndef EXTI_EXTI_INTERFACE_H_
#define EXTI_EXTI_INTERFACE_H_

/** @defgroup EXTI_Channels External Interrupt Channel IDs */
/**@{*/
#define INT1    7  /**< External Interrupt Request 1 (PD3) */
#define INT0    6  /**< External Interrupt Request 0 (PD2) */
#define INT2    5  /**< External Interrupt Request 2 (PB2) */
/**@}*/

/** @defgroup EXTI_SenseModes Interrupt Sense Control Modes */
/**@{*/
#define EXTI_LOW_LOGIC  0  /**< Low Level generates an interrupt request */
#define EXTI_ANY_LOGIC  1  /**< Any logical change generates an interrupt request */
#define EXTI_FALLING    2  /**< Falling edge generates an interrupt request */
#define EXTI_RISING     3  /**< Rising edge generates an interrupt request */
/**@}*/

/**
 * @brief Enables a specific External Interrupt channel.
 * @param[in] EXTI_id The interrupt channel to enable (INT0, INT1, or INT2).
 * @return void
 */
void EXTI_Enable(u8 EXTI_id);

/**
 * @brief Disables a specific External Interrupt channel.
 * @param[in] EXTI_id The interrupt channel to disable (INT0, INT1, or INT2).
 * @return void
 */
void EXTI_Disable(u8 EXTI_id);

/**
 * @brief Configures the trigger sense control for a specific External Interrupt.
 * @param[in] EXTI_id Target interrupt channel (INT0, INT1, or INT2).
 * @param[in] sense Trigger condition (EXTI_LOW_LOGIC, EXTI_ANY_LOGIC, EXTI_FALLING, or EXTI_RISING).
 * @return void
 */
void EXTI_SenseControl(u8 EXTI_id, u8 sense);

/**
 * @brief Registers a user-defined callback function to be executed inside the ISR.
 * @param[in] EXTI_id Target interrupt channel (INT0, INT1, or INT2).
 * @param[in] func Pointer to the function to execute upon interrupt firing.
 * @return void
 */
void EXTI_SetCallBack(u8 EXTI_id, void (*func)(void));

#endif /* EXTI_EXTI_INTERFACE_H_ */