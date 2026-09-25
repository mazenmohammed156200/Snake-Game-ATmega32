/**
 * @file Shift_REG_program.c
 * @brief Driver implementation for 74HC595 / 74LS595 Serial-In Parallel-Out Shift Registers.
 * @details Implements GPIO-based bit-banging algorithm to shift out 8-bit and 16-bit 
 *          data serially to control external expansion hardware.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DIO/DIO_private.h"
#include "Shift_REG_private.h"
#include "Shift_REG_config.h"
#include "Shift_REG_interface.h"
#include <util/delay.h>

/**
 * @brief Configures shift register control pins as outputs and sets default idle states.
 * @param[in] ptr Pointer to Shift_REG hardware configuration structure.
 * @return void
 */
void Shift_REG_Init(Shift_REG* ptr)
{
    DIO_SetPinDirection(ptr->Port, ptr->DataPin, DIO_OUTPUT);
    DIO_SetPinDirection(ptr->Port, ptr->ClockPin, DIO_OUTPUT);
    DIO_SetPinDirection(ptr->Port, ptr->LatchPin, DIO_OUTPUT);

    DIO_SetPinValue(ptr->Port, ptr->ClockPin, DIO_LOW);
    DIO_SetPinValue(ptr->Port, ptr->LatchPin, DIO_LOW);
}

/**
 * @brief Generates a high-to-low clock pulse on SRCLK to advance bit data in shift register.
 * @param[in] ptr Pointer to Shift_REG hardware configuration structure.
 * @return void
 */
void Shift_REG_ClockPulse(Shift_REG* ptr)
{
    DIO_SetPinValue(ptr->Port, ptr->ClockPin, DIO_HIGH);
    DIO_SetPinValue(ptr->Port, ptr->ClockPin, DIO_LOW);
}

/**
 * @brief Generates a high-to-low pulse on RCLK to transfer shifted bits into storage register outputs.
 * @param[in] ptr Pointer to Shift_REG hardware configuration structure.
 * @return void
 */
void Shift_REG_LatchPulse(Shift_REG* ptr)
{
    DIO_SetPinValue(ptr->Port, ptr->LatchPin, DIO_HIGH);
    DIO_SetPinValue(ptr->Port, ptr->LatchPin, DIO_LOW);
}

/**
 * @brief Transmits an 8-bit byte serially (MSB First) to a single shift register IC.
 * @param[in] ptr Pointer to Shift_REG hardware configuration structure.
 * @param[in] value 8-bit data byte to shift out.
 * @return void
 */
void Shift_REG_SendByte(Shift_REG* ptr, u8 value)
{
    for (s8 i = _8_BITS - 1; i >= 0; i--)
    {
        if (GET_BIT(value, i) == DIO_HIGH)
        {
            DIO_SetPinValue(ptr->Port, ptr->DataPin, DIO_HIGH);
        }
        else
        {
            DIO_SetPinValue(ptr->Port, ptr->DataPin, DIO_LOW);
        }

        Shift_REG_ClockPulse(ptr);
    }
    Shift_REG_LatchPulse(ptr);
}

/**
 * @brief Transmits a 16-bit word serially (MSB First) to cascaded shift registers.
 * @param[in] ptr Pointer to Shift_REG hardware configuration structure.
 * @param[in] value 16-bit data word to shift out.
 * @return void
 */
void Shift_REG_SendTwoByte(Shift_REG* ptr, u16 value)
{
    for (s8 i = _16_BITS - 1; i >= 0; i--)
    {
        if (GET_BIT(value, i) == DIO_HIGH)
        {
            DIO_SetPinValue(ptr->Port, ptr->DataPin, DIO_HIGH);
        }
        else
        {
            DIO_SetPinValue(ptr->Port, ptr->DataPin, DIO_LOW);
        }
        Shift_REG_ClockPulse(ptr);
    }
    Shift_REG_LatchPulse(ptr);
}