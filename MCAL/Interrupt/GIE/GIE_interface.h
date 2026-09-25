/**
 * @file GIE_interface.h
 * @brief Interface header for ATmega32 Global Interrupt Enable (GIE) driver.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#ifndef GIE_GIE_INTERFACE_H_
#define GIE_GIE_INTERFACE_H_

/**
 * @brief Enables global interrupts by setting the I-bit in Status Register (SREG).
 * @return void
 */
void GIE_Enable(void);

/**
 * @brief Disables global interrupts by clearing the I-bit in Status Register (SREG).
 * @return void
 */
void GIE_Disable(void);

#endif /* GIE_GIE_INTERFACE_H_ */