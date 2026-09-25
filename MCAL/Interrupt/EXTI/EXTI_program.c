/**
 * @file EXTI_program.c
 * @brief Implementation of the ATmega32 External Interrupts (EXTI) driver.
 * @details Handles external hardware interrupts (INT0, INT1, INT2) configuration, 
 *          sense control, enabling/disabling, and ISR callbacks.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#include "../BIT_MATH.h"
#include "../STD.h"
#include "../../DIO/DIO_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"

/** @brief Array of function pointers to hold callback functions for INT0, INT1, and INT2. */
static void (*ptr[3])(void) = {0, 0, 0};

/**
 * @brief Registers a callback function for a specific EXTI line.
 * @param[in] EXTI_id Target interrupt channel (INT0, INT1, or INT2).
 * @param[in] func Pointer to the function to be invoked by the ISR.
 * @return void
 */
void EXTI_SetCallBack(u8 EXTI_id, void (*func)(void)) {
    if (func != 0) {
        switch (EXTI_id) {
            case INT0: ptr[0] = func; break;
            case INT1: ptr[1] = func; break;
            case INT2: ptr[2] = func; break;
            default:   break;
        }
    }
}

/**
 * @brief ISR for External Interrupt Request 0 (INT0 / Vector 1).
 */
void __vector_1(void) __attribute__((signal, used));
void __vector_1(void) {
    if (ptr[0] != 0) {
        ptr[0]();
    }
}

/**
 * @brief ISR for External Interrupt Request 1 (INT1 / Vector 2).
 */
void __vector_2(void) __attribute__((signal, used));
void __vector_2(void) {
    if (ptr[1] != 0) {
        ptr[1]();
    }
}

/**
 * @brief ISR for External Interrupt Request 2 (INT2 / Vector 3).
 */
void __vector_3(void) __attribute__((signal, used));
void __vector_3(void) {
    if (ptr[2] != 0) {
        ptr[2]();
    }
}

/**
 * @brief Enables a specific External Interrupt channel via General Interrupt Control Register (GICR).
 * @param[in] EXTI_id Target interrupt channel (INT0, INT1, or INT2).
 * @return void
 */
void EXTI_Enable(u8 EXTI_id) {
    if (EXTI_id >= INT2 && EXTI_id <= INT1) {
        SET_BIT(GICR, EXTI_id);
    }
}

/**
 * @brief Disables a specific External Interrupt channel via General Interrupt Control Register (GICR).
 * @param[in] EXTI_id Target interrupt channel (INT0, INT1, or INT2).
 * @return void
 */
void EXTI_Disable(u8 EXTI_id) {
    if (EXTI_id >= INT2 && EXTI_id <= INT1) {
        CLR_BIT(GICR, EXTI_id);
    }
}

/**
 * @brief Configures trigger sense condition (Low Level, Any Change, Falling Edge, or Rising Edge).
 * @param[in] EXTI_id Target interrupt channel (INT0, INT1, or INT2).
 * @param[in] sense Desired trigger condition.
 * @return void
 */
void EXTI_SenseControl(u8 EXTI_id, u8 sense) {
    switch (EXTI_id) {
        case INT0:
            switch (sense) {
                case EXTI_LOW_LOGIC:
                    CLR_BIT(MCUCR, ISC01);
                    CLR_BIT(MCUCR, ISC00);
                    break;
                case EXTI_ANY_LOGIC:
                    CLR_BIT(MCUCR, ISC01);
                    SET_BIT(MCUCR, ISC00);
                    break;
                case EXTI_RISING:
                    SET_BIT(MCUCR, ISC01);
                    SET_BIT(MCUCR, ISC00);
                    break;
                case EXTI_FALLING:
                    SET_BIT(MCUCR, ISC01);
                    CLR_BIT(MCUCR, ISC00);
                    break;
            }
            break;

        case INT1:
            switch (sense) {
                case EXTI_LOW_LOGIC:
                    CLR_BIT(MCUCR, ISC11);
                    CLR_BIT(MCUCR, ISC10);
                    break;
                case EXTI_ANY_LOGIC:
                    CLR_BIT(MCUCR, ISC11);
                    SET_BIT(MCUCR, ISC10); 
                    break;
                case EXTI_RISING:
                    SET_BIT(MCUCR, ISC11);
                    SET_BIT(MCUCR, ISC10);
                    break;
                case EXTI_FALLING:
                    SET_BIT(MCUCR, ISC11); 
                    CLR_BIT(MCUCR, ISC10);
                    break;
            }
            break;

        case INT2:
            switch (sense) {
                case EXTI_RISING:
                    SET_BIT(MCUCSR, ISC2);
                    break;
                case EXTI_FALLING:
                    CLR_BIT(MCUCSR, ISC2);
                    break;
            }
            break;
    }
}