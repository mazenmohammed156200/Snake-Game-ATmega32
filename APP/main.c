/**
 * @file main.c
 * @brief Main application entry point for the ATmega32 Snake Game.
 * @details Initializes system peripherals, registers periodic scheduler tasks, 
 *          and controls the game loop using a bare-metal cooperative OS.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#include "../LIB/STD.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/DOT_MATRIX/DOTMAT_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/TIMER_0/TIMER0_interface.h"
#include "../MCAL/Scheduler/Scheduler_interface.h"
#include "../MCAL/Interrupt/GIE/GIE_interface.h"
#include "../MCAL/USART/USART_config.h"
#include "../MCAL/USART/USART_interface.h"
#include "../HAL/SHIFT_REG/SHIFT_REG_interface.h"
#include "SNAKE_config.h"
#include "SNAKE_interface.h"

/**
 * @brief Global Snake structure instance representing the player state.
 */
Snake S;

/**
 * @brief Holds the current moving direction of the snake.
 * @note Defaults to RIGHT on initialization.
 */
u8 CurrentDirection = RIGHT;

/**
 * @brief Flag indicating whether the game state is active.
 * @value 0 Game is idle / awaiting user input to start.
 * @value 1 Game is actively running.
 */
u8 GameStarted = 0;

/**
 * @brief Task 1: Refreshes the LED Dot Matrix display.
 * @details Executed periodically by the scheduler. Toggles PORTC PIN7 
 *          for debugging and execution time profiling.
 * @return void
 */
void Task1(void){
    DIO_SetPinValue(DIO_PORTC, DIO_PIN7, DIO_HIGH);
    DOTMAT_Refresh();
    DIO_SetPinValue(DIO_PORTC, DIO_PIN7, DIO_LOW);
}

/**
 * @brief Task 2: Polls and updates player movement controls.
 * @details Handles input detection from both push buttons and USART serial 
 *          commands ('w', 'a', 's', 'd') to change direction or start the game.
 * @return void
 */
void Task2(void){
    if(GameStarted == 0)
    {
        if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_RIGHT) == DIO_LOW)
        {
            CurrentDirection = RIGHT;
            GameStarted = 1;
        }
        else if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_DOWN) == DIO_LOW)
        {
            CurrentDirection = DOWN;
            GameStarted = 1;
        }
        else if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_UP) == DIO_LOW)
        {
            CurrentDirection = UP;
            GameStarted = 1;
        }
        else if(USART_Is_Read())
        {
            u8 Key = USART_ReceiveChar();
            if(Key == 's')
            {
                CurrentDirection = DOWN;
                GameStarted = 1;
            }
            else if(Key == 'd')
            {
                CurrentDirection = RIGHT;
                GameStarted = 1;
            }
            else if(Key == 'w')
            {
                CurrentDirection = UP;
                GameStarted = 1;
            }
        }
    }
    else
    {
        CurrentDirection = Snake_GetDirection(&CurrentDirection);
        CurrentDirection = Get_Direction_USART(&CurrentDirection);
    }
}

/**
 * @brief Task 3: Game logic update cycle.
 * @details Evaluates the next snake position, handles collision detection, 
 *          resets the game on game over, or advances the snake position.
 * @return void
 */
void Task3(void){
    switch(GameStarted)
    {
        case 1:
            if (SNAKE_CheckNextPosition(&S, CurrentDirection) == 1)
            {
                /* Game Over: Reset Snake and Game State */
                Snake_Init(&S);
                CurrentDirection = RIGHT;
                Snake_Draw(&S);
                GameStarted = 0;
            }
            else
            {
                Snake_Update(&S, CurrentDirection);
            }
            break;
    }
}

/**
 * @brief Main function initializing hardware, OS scheduler, and tasks.
 * @return int Standard return code (infinite loop execution).
 */
int main(void){

    /* Initialize Peripherals & Hardware Layers */
    DIO_SetPinDirection(DIO_PORTC, DIO_PIN7, DIO_OUTPUT);
    USART_Init(Asynch_Mode, One_SB, Disable_Parity, Data_Mode_8);
    TIMER0_Init();
    ADC_Init();
    Timer0_SetPrescaler(TIMER0_PRESCALER_64);
    DOTMAT_Init();
    Snake_Init(&S);
    Bottons_Init();

    /* Configure System Tick via Timer0 CTC Interrupt */
    Set_Call_Back_CTC(Scheduler_ISR);
    Timer0_SetCompareValue(125);
    Timer0_COMP0_Interrupt_Enable(1);
    GIE_Enable();
    
    DOTMAT_Clear();
    Snake_Draw(&S);

    /* Register Tasks with Cooperative Scheduler: Tasks_creation(ID, Periodicity_ms, TaskPtr) */
    Tasks_creation(0, 3, Task1);
    Tasks_creation(1, 40, Task2);
    Tasks_creation(2, 100, Task3);

    /* Super Loop managed by OS Scheduler Interrupts */
    while (1){

    }

    return 0;
}