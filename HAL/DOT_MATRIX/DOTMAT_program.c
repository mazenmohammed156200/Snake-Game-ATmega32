/**
 * @file DOTMAT_program.c
 * @brief Implementation of the LED Dot Matrix HAL driver using Shift Registers.
 * @details Implements multiplexed row and column control using two cascaded
 *          74LS595 shift registers for driving a 16x16 LED Dot Matrix.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "DOTMAT_config.h"
#include "DOTMAT_private.h"
#include "DOTMAT_interface.h"
#include "../SHIFT_REG/Shift_REG_interface.h"

/**
 * @brief Hardware pin configuration instance for the Row Shift Register.
 */
Shift_REG DOTMAT_Rows = {
    DIO_PORTC,
    DIO_PIN0,
    DIO_PIN1,
    DIO_PIN2};

/**
 * @brief Hardware pin configuration instance for the Column Shift Register.
 */
Shift_REG DOTMAT_Cols = {
    DIO_PORTD,
    DIO_PIN7,
    DIO_PIN6,
    DIO_PIN5};

/**
 * @brief Internal 16-bit frame buffer array storing pixel states for each row.
 * @details Each 16-bit element represents 16 column LEDs for a specific row.
 */
static u16 Frame_Buffer[DOTMATRIX_ROWS] = {0};

/**
 * @brief Initializes the Row and Column Shift Registers and clears the matrix display.
 * @return void
 */
void DOTMAT_Init(void)
{
    Shift_REG_Init(&DOTMAT_Rows);
    Shift_REG_Init(&DOTMAT_Cols);

    DOTMAT_Clear();
}

/**
 * @brief Sets or clears a single pixel state in the frame buffer at coordinates (x, y).
 * @param[in] x Column coordinate (0 to DOTMATRIX_COLUMNS - 1).
 * @param[in] y Row coordinate (0 to DOTMATRIX_ROWS - 1).
 * @param[in] state Pixel state: 1 for ON, 0 for OFF.
 * @return void
 */
void DOTMAT_SetPixel(u8 x, u8 y, u8 state)
{
    if (x >= DOTMATRIX_COLUMNS || y >= DOTMATRIX_ROWS)
    {
        return;
    }

    if (state == 1)
    {
        SET_BIT(Frame_Buffer[y], x);
    }
    else
    {
        CLR_BIT(Frame_Buffer[y], x);
    }
}

/**
 * @brief Resets all entries in the frame buffer to zero (turns off all LEDs).
 * @return void
 */
void DOTMAT_Clear(void)
{
    for (u32 i = 0; i < DOTMATRIX_ROWS; i++)
    {
        Frame_Buffer[i] = 0x0000;
    }
}

/**
 * @brief Performs active row multiplexing to render the frame buffer contents on screen.
 * @details Iterates through rows, sends column pattern data, activates corresponding
 *          row sink pin, and latches shift register data to eliminate flickering.
 * @return void
 */
void DOTMAT_Refresh(void)
{
    u8 Current_Row;

    for (Current_Row = 0; Current_Row < DOTMATRIX_ROWS; Current_Row++)
    {
        /* Turn off all rows to prevent ghosting during data transition */
        Shift_REG_SendTwoByte(&DOTMAT_Rows, 0xFFFF);
        Shift_REG_LatchPulse(&DOTMAT_Rows);

        u16 Col_Data = Frame_Buffer[Current_Row];
        u16 Row_Data = ~((u16)1 << Current_Row);

        /* Output Column pattern for current row */
        Shift_REG_SendTwoByte(&DOTMAT_Cols, Col_Data);
        Shift_REG_LatchPulse(&DOTMAT_Cols);

        /* Activate current Row */
        Shift_REG_SendTwoByte(&DOTMAT_Rows, Row_Data);
        Shift_REG_LatchPulse(&DOTMAT_Rows);
    }

    /* Disable all rows after multiplexing loop */
    Shift_REG_SendTwoByte(&DOTMAT_Rows, 0xFFFF);
    Shift_REG_LatchPulse(&DOTMAT_Rows);
}