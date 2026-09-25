/**
 * @file ADC_interface.h
 * @brief Public APIs and prototypes for the ATmega32 ADC peripheral driver.
 * @details Provides functions for initializing the Analog-to-Digital Converter 
 *          and executing synchronous or asynchronous analog conversions.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

/**
 * @brief Initializes the ADC hardware (Voltage Reference, Prescaler, Enable).
 * @return void
 */
void ADC_Init(void);

/**
 * @brief Reads an analog channel synchronously (blocking mode until conversion completes).
 * @param[in] channel ADC input channel selection (ADC0 to ADC7).
 * @return u16 Digital conversion output (10-bit resolution value, 0 to 1023).
 */
u16 ADC_ReadSynch(u8 channel);

/**
 * @brief Initiates an asynchronous analog conversion on a selected channel.
 * @param[in] channel ADC input channel selection (ADC0 to ADC7).
 * @return u16 Digital conversion result or status.
 */
u16 ADC_ReadASynch(u8 channel);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */