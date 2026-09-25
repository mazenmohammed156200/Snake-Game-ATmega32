#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DIO/DIO_private.h"
#include "Shift_REG_private.h"
#include "Shift_REG_config.h"
#include "Shift_REG_interface.h"
#include <util/delay.h>

void Shift_REG_Init( Shift_REG* ptr)
{
	DIO_SetPinDirection(ptr->Port, ptr->DataPin, DIO_OUTPUT);
	DIO_SetPinDirection(ptr->Port, ptr->ClockPin, DIO_OUTPUT);
	DIO_SetPinDirection(ptr->Port, ptr->LatchPin, DIO_OUTPUT);

	DIO_SetPinValue(ptr->Port, ptr->ClockPin, DIO_LOW);
	DIO_SetPinValue(ptr->Port, ptr->LatchPin, DIO_LOW);
}

void Shift_REG_ClockPulse( Shift_REG* ptr)
{
	DIO_SetPinValue(ptr->Port, ptr->ClockPin, DIO_HIGH);
	DIO_SetPinValue(ptr->Port, ptr->ClockPin, DIO_LOW);
}

void Shift_REG_LatchPulse( Shift_REG* ptr)
{
	DIO_SetPinValue(ptr->Port, ptr->LatchPin, DIO_HIGH);
    DIO_SetPinValue(ptr->Port, ptr->LatchPin, DIO_LOW);
}

void Shift_REG_SendByte( Shift_REG* ptr, u8 value)
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

void Shift_REG_SendTwoByte( Shift_REG* ptr, u16 value)
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
