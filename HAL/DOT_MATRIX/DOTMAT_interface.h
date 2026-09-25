/**
 * @file DOTMAT_interface.h
 * @brief Public APIs and prototypes for the LED Dot Matrix HAL driver.
 * @details Provides functions to initialize, clear, set pixels, and refresh 
 *          the LED Dot Matrix display using hardware shift registers.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef HAL_DOT_MATRIX_DOTMAT_INTERFACE_H_
#define HAL_DOT_MATRIX_DOTMAT_INTERFACE_H_

/**
 * @brief Initializes hardware pins and shift registers associated with the Dot Matrix.
 * @return void
 */
void DOTMAT_Init(void);

/**
 * @brief Sets or clears a specific pixel (LED) coordinate in the display buffer.
 * @param[in] x Column coordinate (0 to DOTMATRIX_COLUMNS - 1).
 * @param[in] y Row coordinate (0 to DOTMATRIX_ROWS - 1).
 * @param[in] state Pixel state (1 to turn ON, 0 to turn OFF).
 * @return void
 */
void DOTMAT_SetPixel(u8 x, u8 y, u8 state);

/**
 * @brief Clears the internal frame buffer (turns off all LEDs).
 * @return void
 */
void DOTMAT_Clear(void);

/**
 * @brief Refreshes the physical display by shifting out the frame buffer data.
 * @note Must be called periodically (e.g., via scheduler task) to maintain flicker-free display.
 * @return void
 */
void DOTMAT_Refresh(void);

#endif /* HAL_DOT_MATRIX_DOTMAT_INTERFACE_H_ */