/**
 * @file SHIFT_REG_config.h
 * @brief Configuration header file for the 74HC595/74LS595 Shift Register HAL driver.
 * @details Defines bit width constants and system-level parameters for shift register operations.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef HAL_SHIFT_REG_SHIFT_REG_CONFIG_H_
#define HAL_SHIFT_REG_SHIFT_REG_CONFIG_H_

/**
 * @name Shift Register Data Width Definitions
 * @{
 */
#define _8_BITS                     8   /**< Standard 8-bit shift register configuration (Single IC) */
#define _16_BITS                    16  /**< Cascaded 16-bit shift register configuration (Dual ICs) */
/** @} */

#endif /* HAL_SHIFT_REG_SHIFT_REG_CONFIG_H_ */