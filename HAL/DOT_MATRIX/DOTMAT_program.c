/*
 * DOTMAT_program.c
 *
 *  Created on: Sep 5, 2026
 *      Author: ot
 */


#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "DOTMAT_config.h"
#include "DOTMAT_private.h"
#include "DOTMAT_interface.h"
#include "../SHIFT_REG/Shift_REG_interface.h"

 Shift_REG DOTMAT_Rows = {
    DIO_PORTC,
    DIO_PIN0,
    DIO_PIN1,
    DIO_PIN2
};

 Shift_REG DOTMAT_Cols = {
    DIO_PORTD,
    DIO_PIN7,
    DIO_PIN6,
    DIO_PIN5
};
static u16 Frame_Buffer[DOTMATRIX_ROWS] = {0};

void DOTMAT_Init(){
	Shift_REG_Init(&DOTMAT_Rows);
	Shift_REG_Init(&DOTMAT_Cols);

	DOTMAT_Clear();

}

void DOTMAT_SetPixel(u8 x,u8 y,u8 state){
	 if (x >= DOTMATRIX_COLUMNS || y >= DOTMATRIX_ROWS)
	    {
	        return;
	    }
	    if (state == 1)
	    {
	        SET_BIT(Frame_Buffer[y], x); ////
	    }
	    else
	    {
	        CLR_BIT(Frame_Buffer[y], x);////
	    }
}

void DOTMAT_Clear(){
	for (u32 i = 0; i < DOTMATRIX_ROWS; i++)
	  {
	    Frame_Buffer[i] = 0x0000;
	  }

}



void DOTMAT_Refresh()
{
    u8 Current_Row;


    for (Current_Row = 0; Current_Row < DOTMATRIX_ROWS; Current_Row++)
    {

        Shift_REG_SendTwoByte(&DOTMAT_Rows, 0xFFFF);
        Shift_REG_LatchPulse(&DOTMAT_Rows);


        u16 Col_Data = Frame_Buffer[Current_Row];
        u16 Row_Data = ~((u16)1 << Current_Row);


        Shift_REG_SendTwoByte(&DOTMAT_Cols, Col_Data);
        Shift_REG_LatchPulse(&DOTMAT_Cols);


        Shift_REG_SendTwoByte(&DOTMAT_Rows, Row_Data);
        Shift_REG_LatchPulse(&DOTMAT_Rows);



    }
    Shift_REG_SendTwoByte(&DOTMAT_Rows, 0xFFFF);
    Shift_REG_LatchPulse(&DOTMAT_Rows);
}
