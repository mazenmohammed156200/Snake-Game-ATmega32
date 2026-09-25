/**
 * @file GIE_program.c
 * @brief Implementation of ATmega32 Global Interrupt Enable (GIE) driver.
 * @details Controls the execution of hardware interrupts system-wide via the SREG I-bit.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#include "../BIT_MATH.h"
#include "../STD.h"
#include "../../DIO/DIO_interface.h"
#include "GIE_private.h"
#include "GIE_config.h"
#include "GIE_interface.h"

/**
 * @brief Sets the Global Interrupt Enable (I) bit in SREG.
 * @details Allows the processor to respond to enabled maskable interrupts.
 * @return void
 */
void GIE_Enable(void) {
    SET_BIT(SREG, I);
}

/**
 * @brief Clears the Global Interrupt Enable (I) bit in SREG.
 * @details Blocks all maskable interrupts regardless of individual peripheral interrupt settings.
 * @return void
 */
void GIE_Disable(void) {
    CLR_BIT(SREG, I);
}