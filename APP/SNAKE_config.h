/**
 * @file SNAKE_config.h
 * @brief Configuration file for the Snake Game application.
 * @details Contains configurable macros for matrix dimensions, maximum snake length, 
 *          and hardware pin configurations for control buttons.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef APP_SNAKE_GAME_CONFIG_H_
#define APP_SNAKE_GAME_CONFIG_H_

/**
 * @brief Defines the maximum allowable length (number of segments) for the snake.
 */
#define MAX_SNAKE_LENGTH    256

/**
 * @name Matrix Display Dimensions
 * @{
 */
#define MATRIX_ROWS         16  /**< Number of rows in the LED Dot Matrix display */
#define MATRIX_COLS         16  /**< Number of columns in the LED Dot Matrix display */
/** @} */

/**
 * @name Button Hardware Port & Pin Configuration
 * @{
 */
#define BUTTONS_PORT        DIO_PORTB   /**< Microcontroller DIO Port assigned for directional buttons */

#define BUTTON_UP           DIO_PIN0    /**< DIO Pin mapping for UP direction button */
#define BUTTON_DOWN         DIO_PIN1    /**< DIO Pin mapping for DOWN direction button */
#define BUTTON_RIGHT        DIO_PIN2    /**< DIO Pin mapping for RIGHT direction button */
#define BUTTON_LEFT         DIO_PIN3    /**< DIO Pin mapping for LEFT direction button */
/** @} */

#endif /* APP_SNAKE_GAME_CONFIG_H_ */