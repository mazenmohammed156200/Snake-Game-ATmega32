/**
 * @file EXTI_private.h
 * @brief Private registers and bit definitions for ATmega32 External Interrupts.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#ifndef EXTI_EXTI_PRIVATE_H_
#define EXTI_EXTI_PRIVATE_H_

/* Hardware Register Definitions */
#define GICR        (*(volatile u8 *)(0x5B))  /**< General Interrupt Control Register */
#define MCUCR       (*(volatile u8 *)(0x55))  /**< MCU Control Register */
#define MCUCSR      (*(volatile u8 *)(0x54))  /**< MCU Control and Status Register */
#define GIFR        (*(volatile u8 *)(0x5A))  /**< General Interrupt Flag Register */

/* GICR and GIFR Bit Mapping */
#define INTF1       7  /**< External Interrupt Flag 1 */
#define INTF0       6  /**< External Interrupt Flag 0 */
#define INTF2       5  /**< External Interrupt Flag 2 */

/* MCUCR Bit Mapping (Sense Control for INT0 & INT1) */
#define ISC11       3  /**< Interrupt Sense Control 1 Bit 1 */
#define ISC10       2  /**< Interrupt Sense Control 1 Bit 0 */
#define ISC01       1  /**< Interrupt Sense Control 0 Bit 1 */
#define ISC00       0  /**< Interrupt Sense Control 0 Bit 0 */

/* MCUCSR Bit Mapping (Sense Control for INT2) */
#define ISC2        6  /**< Interrupt Sense Control 2 */

#endif /* EXTI_EXTI_PRIVATE_H_ */