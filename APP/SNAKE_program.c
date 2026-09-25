/**
 * @file SNAKE_program.c
 * @brief Implementation of the Snake Game application logic and state machine.
 * @details Handles game initialization, movement logic, collision checking, 
 *          ADC-based random food generation, and input processing.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#include "../LIB/STD.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/DOT_MATRIX/DOTMAT_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/Scheduler/Scheduler_interface.h"
#include "../MCAL/USART/USART_interface.h"
#include "../MCAL/Interrupt/GIE/GIE_interface.h"
#include <util/delay.h>

#include "SNAKE_config.h"
#include "SNAKE_interface.h"
#include "SNAKE_private.h"

/**
 * @brief Current game step task periodicity in milliseconds.
 * @note Dynamically decremented when snake eats food to increase game speed.
 */
u32 g_Periodictey = 100;

/**
 * @brief Stores selected game mode.
 * @value 0 Closed Mode (hitting walls causes Game Over).
 * @value 1 Open Mode (walls wrap around to opposite side).
 */
u8 Game_Mode = 0;

/**
 * @brief Initializes snake state, prompts user via USART for game mode, and starts game.
 * @param[in,out] S Pointer to Snake structure instance.
 * @return void
 */
void Snake_Init(Snake *S)
{
    S->Length = 2;
    S->Body[0].Row = 5;
    S->Body[0].Col = 5;
    S->Body[1].Row = 5;
    S->Body[1].Col = 4;
    
    SNAKE_GenerateFood(S);
    g_Periodictey = 100;
    Scheduler_Update_Periodictey(2, g_Periodictey);
    
    USART_SendString("Enter e for open mode and q for close mode\r\n");
    
    u32 timer = 0;
    while(timer < MAX_TIME_WAIT)
    {
        if(USART_Is_Read())
        {
            u8 Key = USART_ReceiveChar();
            if(Key == 'q')
            {
                Game_Mode = 0; /* Close Mode */
                USART_SendString("Close Mode\r\n");
                return;
            }
            else if(Key == 'e')
            {
                Game_Mode = 1; /* Open Mode */
                USART_SendString("Open Mode\r\n");
                return;
            }
        }
        _delay_ms(10);
        timer++;
    }
    
    if(timer == MAX_TIME_WAIT)
    {
        Game_Mode = 0;
        USART_SendString("Default Mode (Close Mode)\r\n");
    }
}

/**
 * @brief Configures internal pull-up resistors on DIO pins assigned to push buttons.
 * @return void
 */
void Bottons_Init(void)
{
    DIO_SetPinDirection(BUTTONS_PORT, BUTTON_UP, DIO_PULLUP);
    DIO_SetPinDirection(BUTTONS_PORT, BUTTON_DOWN, DIO_PULLUP);
    DIO_SetPinDirection(BUTTONS_PORT, BUTTON_RIGHT, DIO_PULLUP);
    DIO_SetPinDirection(BUTTONS_PORT, BUTTON_LEFT, DIO_PULLUP);
}

/**
 * @brief Polls push button inputs and updates direction without illegal 180-degree turns.
 * @param[in,out] CurrentDirection Pointer to variable holding current movement direction.
 * @return u8 Updated direction value.
 */
u8 Snake_GetDirection(u8 *CurrentDirection)
{
    if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_UP) == DIO_LOW)
    {
        if(*CurrentDirection != DOWN)
        {
            *CurrentDirection = UP;
        }
    }
    else if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_DOWN) == DIO_LOW)
    {
        if(*CurrentDirection != UP)
        {
            *CurrentDirection = DOWN;
        }
    }
    else if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_RIGHT) == DIO_LOW)
    {
        if(*CurrentDirection != LEFT)
        {
            *CurrentDirection = RIGHT;
        }
    }
    else if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_LEFT) == DIO_LOW)
    {
        if(*CurrentDirection != RIGHT)
        {
            *CurrentDirection = LEFT;
        }
    }
    return *CurrentDirection;
}

/**
 * @brief Reads incoming USART characters and maps WASD controls to snake directions.
 * @param[in,out] CurrentDirection Pointer to current movement direction.
 * @return u8 Updated direction value.
 */
u8 Get_Direction_USART(u8 *CurrentDirection)
{
    if(USART_Is_Read())
    {
        u8 Key = USART_ReceiveChar();

        if(Key == 'w')
        {
            if(*CurrentDirection != DOWN)
                *CurrentDirection = UP;
        }
        else if(Key == 's')
        {
            if(*CurrentDirection != UP)
                *CurrentDirection = DOWN;
        }
        else if(Key == 'a')
        {
            if(*CurrentDirection != RIGHT)
                *CurrentDirection = LEFT;
        }
        else if(Key == 'd')
        {
            if(*CurrentDirection != LEFT)
                *CurrentDirection = RIGHT;
        }
    }
    return *CurrentDirection;
}

/**
 * @brief Clears display buffer and renders all snake body segments and food.
 * @param[in] S Pointer to Snake instance.
 * @return void
 */
void Snake_Draw(Snake *S)
{
    DOTMAT_Clear();
    for(u8 i = 0; i < S->Length; i++)
    {
        DOTMAT_SetPixel(S->Body[i].Col, S->Body[i].Row, 1);
    }

    DOTMAT_SetPixel(S->Food.Col, S->Food.Row, 1);
}

/**
 * @brief Checks if the head of the snake is at grid boundaries based on direction.
 * @param[in] S Pointer to Snake instance.
 * @param[in] Direction Target direction.
 * @return u8 Returns 1 if collision occurs, 0 otherwise.
 */
u8 Snake_CheckWallCollision(Snake *S, u8 Direction)
{
    switch(Direction)
    {
        case RIGHT:
            if(S->Body[0].Col == MATRIX_COLS - 1) return 1; 
            break;

        case LEFT:
            if(S->Body[0].Col == 0) return 1; 
            break;

        case UP:
            if(S->Body[0].Row == 0) return 1; 
            break;

        case DOWN:
            if(S->Body[0].Row == MATRIX_ROWS - 1) return 1; 
            break;
    }
    return 0;
}

/**
 * @brief Checks if the snake's head coordinate intersects with any body segment.
 * @param[in] S Pointer to Snake instance.
 * @param[in] Direction Target direction.
 * @return u8 Returns 1 if self collision occurs, 0 otherwise.
 */
u8 Snake_CheckSelfCollision(Snake *S, u8 Direction)
{
    for(u8 i = 1; i < S->Length; i++)
    {
        if(S->Body[i].Row == S->Body[0].Row && S->Body[i].Col == S->Body[0].Col) 
            return 1;
    }
    return 0;
}

/**
 * @brief Updates snake coordinates step-by-step and handles boundary wrapping for Open Mode.
 * @param[in,out] S Pointer to Snake instance.
 * @param[in] Direction Intended direction.
 * @return void
 */
void Snake_Move(Snake *S, u8 Direction)
{
    /* Shift body segments towards tail */
    for(s8 i = S->Length - 1; i > 0; i--)
    {
        S->Body[i] = S->Body[i - 1];
    }

    /* Advance snake head */
    switch(Direction)
    {
        case RIGHT:
            if(Game_Mode == 1 && S->Body[0].Col == MATRIX_COLS - 1)
                S->Body[0].Col = 0;
            else
                S->Body[0].Col++;
            break;

        case LEFT:
            if(Game_Mode == 1 && S->Body[0].Col == 0)
                S->Body[0].Col = MATRIX_COLS - 1;
            else
                S->Body[0].Col--;
            break;

        case UP:
            if(Game_Mode == 1 && S->Body[0].Row == 0)
                S->Body[0].Row = MATRIX_ROWS - 1;
            else
                S->Body[0].Row--;
            break;

        case DOWN:
            if(Game_Mode == 1 && S->Body[0].Row == MATRIX_ROWS - 1)
                S->Body[0].Row = 0;
            else
                S->Body[0].Row++;
            break;
    }
}

/**
 * @brief Expands snake length by appending a new segment at the tail.
 * @param[in,out] S Pointer to Snake instance.
 * @return void
 */
void SNAKE_Grow(Snake *S)
{
    if(S->Length < MAX_SNAKE_LENGTH)
    {
        S->Body[S->Length] = S->Body[S->Length - 1];
        S->Length++;
    }
}

/**
 * @brief Moves snake, evaluates food acquisition, updates speed, and redraws frame.
 * @param[in,out] S Pointer to Snake instance.
 * @param[in] Direction Active direction.
 * @return void
 */
void Snake_Update(Snake *S, u8 Direction)
{
    Snake_Move(S, Direction);
    
    if(SNAKE_CheckFoodCollision(S))
    {
        SNAKE_Grow(S);
        SNAKE_GenerateFood(S);
        
        /* Increase speed up to minimum tick bound */
        if(g_Periodictey > 40)
        {
            g_Periodictey -= 5;
            Scheduler_Update_Periodictey(2, g_Periodictey);
        }
    }
    
    Snake_Draw(S);
}

/**
 * @brief Validates if the upcoming coordinate triggers game termination conditions.
 * @param[in] S Pointer to Snake instance.
 * @param[in] Direction Target movement direction.
 * @return u8 Returns 1 if game over condition triggered, 0 if position is valid.
 */
u8 SNAKE_CheckNextPosition(Snake *S, u8 Direction)
{
    if(Snake_CheckSelfCollision(S, Direction))
    {
        return 1;
    }
    
    if(Game_Mode == 0) /* Closed Mode Wall Collision Check */
    {
        if(Snake_CheckWallCollision(S, Direction))
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Checks if a matrix coordinate is currently occupied by any snake body segment.
 * @param[in] S Pointer to Snake instance.
 * @param[in] Row Matrix row index.
 * @param[in] Col Matrix column index.
 * @return u8 Returns 1 if position is occupied, 0 if free.
 */
u8 SNAKE_IsPositionOccupied(Snake *S, u8 Row, u8 Col)
{
    for(u8 i = 0; i < S->Length; i++)
    {
        if((S->Body[i].Row == Row) && (S->Body[i].Col == Col))
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Generates an 8-bit pseudo-random value using LSBs from floating ADC Channel 0.
 * @return u8 Generated 8-bit random value.
 */
u8 SNAKE_GetRandom8Bit(void)
{
    u8 Random = 0;

    for(u8 i = 0; i < 4; i++)
    {
        Random <<= 2;
        Random |= (ADC_ReadSynch(0) & 0x03);
    }

    return Random;
}

/**
 * @brief Spawns food at a random unoccupied position on the matrix.
 * @param[in,out] S Pointer to Snake instance.
 * @return void
 */
void SNAKE_GenerateFood(Snake *S)
{
    u8 Random;

    do
    {
        Random = SNAKE_GetRandom8Bit();

        S->Food.Row = Random & 0x0F;
        S->Food.Col = (Random >> 4) & 0x0F;

    } while(SNAKE_IsPositionOccupied(S, S->Food.Row, S->Food.Col));
}

/**
 * @brief Evaluates whether the snake's head overlaps with food coordinates.
 * @param[in] S Pointer to Snake instance.
 * @return u8 Returns 1 if food collision is detected, 0 otherwise.
 */
u8 SNAKE_CheckFoodCollision(Snake *S)
{
    if((S->Body[0].Col == S->Food.Col) && (S->Body[0].Row == S->Food.Row))
    {
        return 1;
    }
    return 0;
}