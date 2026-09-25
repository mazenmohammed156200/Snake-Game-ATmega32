/**
 * @file SNAKE_private.h
 * @brief Private helper macros and internal function prototypes for the Snake Game.
 * @details Contains internal functions used exclusively by the game's implementation logic 
 *          such as display rendering, wall/self collision checks, and movement routines.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef APP_SNAKE_GAME_PRIVATE_H_
#define APP_SNAKE_GAME_PRIVATE_H_

#include "SNAKE_interface.h"

/**
 * @brief Maximum timeout waiting iteration counter.
 */
#define MAX_TIME_WAIT    500

/**
 * @brief Map the current snake body segments and food coordinates to the Dot Matrix buffer.
 * @param[in] S Pointer to the Snake instance.
 * @return void
 */
void Snake_Draw(Snake *S);

/**
 * @brief Evaluates whether the snake's head will cross matrix border limits.
 * @param[in] S Pointer to the Snake instance.
 * @param[in] Direction Intended direction of movement.
 * @return u8 Returns 1 if wall collision is detected, 0 otherwise.
 */
u8 Snake_CheckWallCollision(Snake *S, u8 Direction);

/**
 * @brief Evaluates whether the snake's head will collide with its own body.
 * @param[in] S Pointer to the Snake instance.
 * @param[in] Direction Intended direction of movement.
 * @return u8 Returns 1 if self collision is detected, 0 otherwise.
 */
u8 Snake_CheckSelfCollision(Snake *S, u8 Direction);

/**
 * @brief Internal logic routine to update snake body coordinates for a step forward.
 * @param[in,out] S Pointer to the Snake instance.
 * @param[in] Direction Target direction.
 * @return void
 */
void Snake_Move(Snake *S, u8 Direction);

/**
 * @brief Checks if a specific matrix coordinate is currently occupied by any snake segment.
 * @param[in] S Pointer to the Snake instance.
 * @param[in] Row Matrix row index.
 * @param[in] Col Matrix column index.
 * @return u8 Returns 1 if position is occupied, 0 if free.
 */
u8 SNAKE_IsPositionOccupied(Snake *S, u8 Row, u8 Col);

#endif /* APP_SNAKE_GAME_PRIVATE_H_ */