/**
 * @file ADC_config.h
 * @brief Configuration header file for ATmega32 Analog-to-Digital Converter (ADC).
 * @details Defines reference voltage levels and system conversion parameters 
 *          used across ADC operations.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

/**
 * @name ADC Voltage Reference Configuration
 * @{
 */
#define VREF        5     /**< Analog reference voltage in Volts (V) */
#define VREF_mV     5000  /**< Analog reference voltage in Millivolts (mV) */
/** @} */

#endif /* MCAL_ADC_ADC_CONFIG_H_ */