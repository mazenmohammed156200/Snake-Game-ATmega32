/**
 * @file DIO_interface.h
 * @brief Public APIs and definitions for ATmega32 Digital Input/Output (DIO) driver.
 * @details Provides macros for Ports, Pins, Directions, and Logic Levels alongside 
 *          prototypes for pin-level and port-level control operations.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_

/**
 * @name DIO Port ID Definitions
 * @{
 */
#define DIO_PORTA         0   /**< General Purpose I/O Port A */
#define DIO_PORTB         1   /**< General Purpose I/O Port B */
#define DIO_PORTC         2   /**< General Purpose I/O Port C */
#define DIO_PORTD         3   /**< General Purpose I/O Port D */
/** @} */

/**
 * @name DIO Pin Index Definitions
 * @{
 */
#define DIO_PIN0          0   /**< Pin 0 */
#define DIO_PIN1          1   /**< Pin 1 */
#define DIO_PIN2          2   /**< Pin 2 */
#define DIO_PIN3          3   /**< Pin 3 */
#define DIO_PIN4          4   /**< Pin 4 */
#define DIO_PIN5          5   /**< Pin 5 */
#define DIO_PIN6          6   /**< Pin 6 */
#define DIO_PIN7          7   /**< Pin 7 */
/** @} */

/**
 * @name DIO Logic Level Definitions
 * @{
 */
#define DIO_LOW           0   /**< Logic Level Low (0V) */
#define DIO_HIGH          1   /**< Logic Level High (5V) */
/** @} */

/**
 * @name DIO Pin Direction Definitions
 * @{
 */
#define DIO_INPUT         0   /**< Input Direction (High Impedance / Floating) */
#define DIO_OUTPUT        1   /**< Output Direction */
#define DIO_PULLUP        2   /**< Input Direction with Internal Pull-Up Resistor Enabled */
/** @} */

/**
 * @name DIO Port Direction Configurations
 * @{
 */
#define DIO_INPUT_PORT    0x00  /**< Configure all 8 pins of a port as Input */
#define DIO_OUTPUT_PORT   0xFF  /**< Configure all 8 pins of a port as Output */
/** @} */

/**
 * @brief Sets the data direction for a specific pin on a selected port.
 * @param[in] u8_port Target port index (DIO_PORTA to DIO_PORTD).
 * @param[in] pin Target pin index (DIO_PIN0 to DIO_PIN7).
 * @param[in] direction Desired direction mode (DIO_INPUT, DIO_OUTPUT, or DIO_PULLUP).
 * @return void
 */
void DIO_SetPinDirection(u8 u8_port, u8 pin, u8 direction);

/**
 * @brief Sets the logical output level (HIGH/LOW) for a specific pin.
 * @param[in] u8_port Target port index (DIO_PORTA to DIO_PORTD).
 * @param[in] pin Target pin index (DIO_PIN0 to DIO_PIN7).
 * @param[in] value Desired output level (DIO_HIGH or DIO_LOW).
 * @return void
 */
void DIO_SetPinValue(u8 u8_port, u8 pin, u8 value);

/**
 * @brief Reads the logical state of a specific input pin.
 * @param[in] u8_port Target port index (DIO_PORTA to DIO_PORTD).
 * @param[in] u8_pin Target pin index (DIO_PIN0 to DIO_PIN7).
 * @return u8 Pin logical state (DIO_HIGH or DIO_LOW).
 */
u8 DIO_GetPinValue(u8 u8_port, u8 u8_pin);

/**
 * @brief Sets the data direction for an entire 8-bit port.
 * @param[in] u8_port Target port index (DIO_PORTA to DIO_PORTD).
 * @param[in] direction 8-bit direction mask (e.g., DIO_INPUT_PORT or DIO_OUTPUT_PORT).
 * @return void
 */
void DIO_SetPortDirection(u8 u8_port, u8 direction);

/**
 * @brief Writes an 8-bit byte value to an entire port.
 * @param[in] u8_port Target port index (DIO_PORTA to DIO_PORTD).
 * @param[in] value 8-bit binary value to write to output register.
 * @return void
 */
void DIO_SetPortValue(u8 u8_port, u8 value);

/**
 * @brief Reads the logical state of an entire 8-bit input port.
 * @param[in] u8_port Target port index (DIO_PORTA to DIO_PORTD).
 * @return u8 8-bit digital values read from port input register.
 */
u8 DIO_GetPortValue(u8 u8_port);

/**
 * @brief Toggles (flips) the logical state of a specific pin.
 * @param[in] port Target port index (DIO_PORTA to DIO_PORTD).
 * @param[in] pin Target pin index (DIO_PIN0 to DIO_PIN7).
 * @return void
 */
void DIO_TogglePin(u8 port, u8 pin);

/**
 * @brief Toggles (flips) the logical state of all pins on a port.
 * @param[in] port Target port index (DIO_PORTA to DIO_PORTD).
 * @return void
 */
void DIO_TogglePORT(u8 port);

#endif /* MCAL_DIO_DIO_INTERFACE_H_ */