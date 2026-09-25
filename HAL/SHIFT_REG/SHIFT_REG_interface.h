/**
 * @file Shift_REG_interface.h
 * @brief Public APIs and structures for 74LS595 Shift Register HAL driver.
 * @details Declarations for initialization, pulse generation, and data shifting 
 *          (8-bit and cascaded 16-bit) using software bit-banging.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef HAL_SHIFT_REG_SHIFT_REG_INTERFACE_H_
#define HAL_SHIFT_REG_SHIFT_REG_INTERFACE_H_

/**
 * @struct Shift_REG
 * @brief Configuration structure holding GPIO pins connected to 74HC595/74LS595 Shift Register.
 */
typedef struct {
    u8 Port;      /**< DIO Port associated with the Shift Register pins */
    u8 DataPin;   /**< Serial Data Input pin (DS / SER) */
    u8 ClockPin;  /**< Shift Register Clock pin (SH_CP / SRCLK) */
    u8 LatchPin;  /**< Storage Register Clock / Latch pin (ST_CP / RCLK) */
} Shift_REG;

/**
 * @brief Initializes the DIO pins connected to the Shift Register as Output.
 * @param[in] ptr Pointer to the Shift_REG configuration structure.
 * @return void
 */
void Shift_REG_Init(Shift_REG* ptr);

/**
 * @brief Generates a single high-to-low pulse on the Shift Register Clock (SRCLK) pin.
 * @param[in] ptr Pointer to the Shift_REG configuration structure.
 * @return void
 */
void Shift_REG_ClockPulse(Shift_REG* ptr);

/**
 * @brief Generates a single high-to-low pulse on the Storage Register Clock (RCLK) pin to latch data.
 * @param[in] ptr Pointer to the Shift_REG configuration structure.
 * @return void
 */
void Shift_REG_LatchPulse(Shift_REG* ptr);

/**
 * @brief Shifts out an 8-bit byte serially (MSB First) into a single 74HC595/74LS595.
 * @param[in] ptr Pointer to the Shift_REG configuration structure.
 * @param[in] value 8-bit data payload to be transmitted.
 * @return void
 */
void Shift_REG_SendByte(Shift_REG* ptr, u8 value);

/**
 * @brief Shifts out a 16-bit integer serially (MSB First) into cascaded 74HC595/74LS595 registers.
 * @param[in] ptr Pointer to the Shift_REG configuration structure.
 * @param[in] value 16-bit data payload to be transmitted.
 * @return void
 */
void Shift_REG_SendTwoByte(Shift_REG* ptr, u16 value);

#endif /* HAL_SHIFT_REG_SHIFT_REG_INTERFACE_H_ */