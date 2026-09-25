/**
 * @file SNAKE_interface.h
 * @brief Public interface definitions and function prototypes for the Snake Game.
 * @details Contains directional enumerations, game coordinate structures, 
 *          Snake object structures, and core game control API prototypes.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef APP_SNAKE_GAME_INTERFACE_H_
#define APP_SNAKE_GAME_INTERFACE_H_

/**
 * @brief Enumeration for snake movement directions.
 */
typedef enum{
    UP,     /**< Upward movement */
    DOWN,   /**< Downward movement */
    RIGHT,  /**< Rightward movement */
    LEFT    /**< Leftward movement */
} Direction;

/**
 * @brief Represents a 2D coordinate on the matrix grid.
 */
typedef struct{
    u8 Row; /**< Row position (0 to MATRIX_ROWS-1) */
    u8 Col; /**< Column position (0 to MATRIX_COLS-1) */
} Point;

/**
 * @brief Main Snake entity data structure.
 */
typedef struct
{
    Point Body[MAX_SNAKE_LENGTH]; /**< Array storing snake body segment coordinates */
    u8 Length;                    /**< Current snake length (number of segments) */
    Point Food;                   /**< Current food position coordinates on the matrix */
} Snake;

/* ========================================================================= */
/* =-------------------- Function Prototypes / APIs -----------------------= */
/* ========================================================================= */

/**
 * @brief Initializes the snake position, length, and spawns initial food.
 * @param[in,out] S Pointer to the Snake instance to initialize.
 * @return void
 */
void Snake_Init(Snake *S);

/**
 * @brief Configures DIO pin modes and pull-up resistors for direction control buttons.
 * @return void
 */
void Bottons_Init(void);

/**
 * @brief Polls physical push buttons and updates direction while preventing 180-degree self-turns.
 * @param[in,out] CurrentDirection Pointer to current direction variable to update.
 * @return u8 The newly determined direction value.
 */
u8 Snake_GetDirection(u8 *CurrentDirection);

/**
 * @brief Advances the snake position forward according to the given direction.
 * @param[in,out] S Pointer to the Snake instance.
 * @param[in] Direction Direction enum value indicating movement direction.
 * @return void
 */
void Snake_Update(Snake *S, u8 Direction);

/**
 * @brief Checks if the upcoming tile will trigger a wall or self-collision.
 * @param[in] S Pointer to the Snake instance.
 * @param[in] Direction Direction value to evaluate.
 * @return u8 Returns 1 if collision will occur (Game Over), 0 otherwise.
 */
u8 SNAKE_CheckNextPosition(Snake *S, u8 Direction);

/**
 * @brief Checks if the snake's head coordinate overlaps with the food position.
 * @param[in] S Pointer to the Snake instance.
 * @param[in] Direction Next movement direction.
 * @return u8 Returns 1 if food collision is detected, 0 otherwise.
 */
u8 SNAKE_CheckFoodCollision(Snake *S);

/**
 * @brief Generates an 8-bit pseudo-random number using the hardware ADC driver.
 * @return u8 8-bit random numeric value.
 */
u8 SNAKE_GetRandom8Bit(void);

/**
 * @brief Generates a new random food coordinate that does not overlap with the snake body.
 * @param[in,out] S Pointer to the Snake instance.
 * @return void
 */
void SNAKE_GenerateFood(Snake *S);

/**
 * @brief Increments snake length and attaches a new segment at the tail.
 * @param[in,out] S Pointer to the Snake instance.
 * @return void
 */
void SNAKE_Grow(Snake *S);

/**
 * @brief Reads serial commands via USART ('w', 'a', 's', 'd') and updates direction.
 * @param[in,out] CurrentDirection Pointer to current direction variable.
 * @return u8 Updated direction value.
 */
u8 Get_Direction_USART(u8 *CurrentDirection);

#endif /* APP_SNAKE_GAME_INTERFACE_H_ */