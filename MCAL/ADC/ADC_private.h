/**
 * @file ADC_private.h
 * @brief Memory-mapped register definitions and private constants for ATmega32 ADC.
 * @details Contains base addresses for ADC peripheral registers, register bit positions, 
 *          channel selection masks, and prescaler definitions.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

/**
 * @name Hardware Register Definitions
 * @{
 */
#define SFIOR       (*(volatile u8 *)(0x50))  /**< Special Function IO Register */
#define ADCSRA      (*(volatile u8 *)(0x26))  /**< ADC Control and Status Register A */
#define ADMUX       (*(volatile u8 *)(0x27))  /**< ADC Multiplexer Selection Register */
#define ADCH        (*(volatile u8 *)(0x25))  /**< ADC Data Register High Byte */
#define ADCL        (*(volatile u8 *)(0x24))  /**< ADC Data Register Low Byte */
#define SREG        (*(volatile u8 *)(0x5F))  /**< AVR Status Register */
/** @} */

/**
 * @name ADMUX Register Bit Positions
 * @{
 */
#define REFS1       7  /**< Reference Selection Bit 1 */
#define REFS0       6  /**< Reference Selection Bit 0 */
#define ADLAR       5  /**< ADC Left Adjust Result Bit */
#define MUX4        4  /**< Analog Channel Selection Bit 4 */
#define MUX3        3  /**< Analog Channel Selection Bit 3 */
#define MUX2        2  /**< Analog Channel Selection Bit 2 */
#define MUX1        1  /**< Analog Channel Selection Bit 1 */
#define MUX0        0  /**< Analog Channel Selection Bit 0 */
/** @} */

/**
 * @name ADCSRA Register Bit Positions
 * @{
 */
#define ADEN        7  /**< ADC Enable Bit */
#define ADSC        6  /**< ADC Start Conversion Bit */
#define ADATE       5  /**< ADC Auto Trigger Enable Bit */
#define ADIF        4  /**< ADC Interrupt Flag Bit (Polling Check) */
#define ADIE        3  /**< ADC Interrupt Enable Bit */
#define ADPS2       2  /**< ADC Prescaler Select Bit 2 */
#define ADPS1       1  /**< ADC Prescaler Select Bit 1 */
#define ADPS0       0  /**< ADC Prescaler Select Bit 0 */
/** @} */

/**
 * @name Helper Masks & Prescaler Values
 * @{
 */
#define CH_select   0xC0  /**< Bitmask to clear channel bits before updating MUX */
#define ADC_64_PRE  0x06  /**< Prescaler division factor select: 64 */
/** @} */

/**
 * @name ADC Analog Pin Mapping (PORTA)
 * @{
 */
#define ADC_PIN0    DIO_PIN0
#define ADC_PIN1    DIO_PIN1
#define ADC_PIN2    DIO_PIN2
#define ADC_PIN3    DIO_PIN3
#define ADC_PIN4    DIO_PIN4
#define ADC_PIN5    DIO_PIN5
#define ADC_PIN6    DIO_PIN6
#define ADC_PIN7    DIO_PIN7

#define SREG_E      DIO_PIN7  /**< Global Interrupt Enable Pin (Bit 7 of SREG) */
/** @} */

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */