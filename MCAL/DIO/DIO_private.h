/**
 * @file DIO_private.h
 * @brief Memory-mapped register definitions for ATmega32 Digital Input/Output (DIO).
 * @details Direct address casting for Data Direction Registers (DDRx), 
 *          Output Port Registers (PORTx), and Input Pins Registers (PINx) 
 *          across Ports A, B, C, and D.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_DIO_DIO_PRIVATE_H_
#define MCAL_DIO_DIO_PRIVATE_H_

/**
 * @name Port Data Direction Registers (DDRx)
 * @{
 */
#define DDRA    *((volatile u8 *)(0x3A))  /**< Port A Data Direction Register */
#define DDRB    *((volatile u8 *)(0x37))  /**< Port B Data Direction Register */
#define DDRC    *((volatile u8 *)(0x34))  /**< Port C Data Direction Register */
#define DDRD    *((volatile u8 *)(0x31))  /**< Port D Data Direction Register */
/** @} */

/**
 * @name Port Output Registers (PORTx)
 * @{
 */
#define PORTA   *((volatile u8 *)(0x3B))  /**< Port A Data Register */
#define PORTB   *((volatile u8 *)(0x38))  /**< Port B Data Register */
#define PORTC   *((volatile u8 *)(0x35))  /**< Port C Data Register */
#define PORTD   *((volatile u8 *)(0x32))  /**< Port D Data Register */
/** @} */

/**
 * @name Port Input Pins Registers (PINx)
 * @{
 */
#define PINA    *((volatile u8 *)(0x39))  /**< Port A Input Pins Address */
#define PINB    *((volatile u8 *)(0x36))  /**< Port B Input Pins Address */
#define PINC    *((volatile u8 *)(0x33))  /**< Port C Input Pins Address */
#define PIND    *((volatile u8 *)(0x30))  /**< Port D Input Pins Address */
/** @} */

#endif /* MCAL_DIO_DIO_PRIVATE_H_ */