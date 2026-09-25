/*
 * GIE_program.c
 *
 *  Created on: Aug 30, 2026
 *      Author: ot
 */
#include"../BIT_MATH.h"
#include"../STD.h"
#include"../../DIO/DIO_interface.h"
#include"GIE_private.h"
#include"GIE_config.h"
#include"GIE_interface.h"
void GIE_Enable(){
	SET_BIT(SREG,I);

}
void GIE_Disable(){

	CLR_BIT(SREG,I);
}
