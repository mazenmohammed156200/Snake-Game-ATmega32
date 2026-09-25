/*
 * EXTI_program.c
 *
 *  Created on: Aug 31, 2026
 *      Author: ot
 */


#include"../BIT_MATH.h"
#include"../STD.h"
#include"../../DIO/DIO_interface.h"
#include"EXTI_private.h"
#include"EXTI_config.h"
#include"EXTI_interface.h"

void(*ptr[3])()={0,0,0};


void EXTI_SetCallBack(u8 EXTI_id, void (*func)(void)) {
    if (func != 0) {
        switch (EXTI_id) {
            case INT0: ptr[0] = func; break;
            case INT1: ptr[1] = func; break;
            case INT2: ptr[2] = func; break;
            default:   break;
        }
    }
}


void __vector_1(void) __attribute__((signal,used));
void __vector_1(void) {
    if (ptr[0] != 0) {
        ptr[0]();
    }
}


void __vector_2(void) __attribute__((signal,used));
void __vector_2(void) {
    if (ptr[1] != 0) {
        ptr[1]();
    }
}


void __vector_3(void) __attribute__((signal,used));
void __vector_3(void) {
    if (ptr[2] != 0) {
        ptr[2]();
    }
}

void EXTI_Enable(u8 EXTI_id){

	if(EXTI_id>=INT2&&EXTI_id<=INT1){
		SET_BIT(GICR,EXTI_id);
	}

}

void EXTI_Disable(u8 EXTI_id){
	if(EXTI_id>=INT2&&EXTI_id<=INT1){

		CLR_BIT(GICR,EXTI_id);
	}

}

void EXTI_SenseControl(u8 EXTI_id,u8 sense){
	switch(EXTI_id){
	case INT0:
		switch(sense){
		case EXTI_LOW_LOGIC:
			CLR_BIT(MCUCR,ISC01);
			CLR_BIT(MCUCR,ISC00);

			break;
		case EXTI_ANY_LOGIC:
			CLR_BIT(MCUCR,ISC01);
			SET_BIT(MCUCR,ISC00);
			break;
		case EXTI_RISING:
			SET_BIT(MCUCR,ISC01);
			SET_BIT(MCUCR,ISC00);
			break;
		case EXTI_FALLING:
			SET_BIT(MCUCR,ISC01);
			CLR_BIT(MCUCR,ISC00);
			break;
		}
		break;

	case INT1:
		switch(sense){
		case EXTI_LOW_LOGIC:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);

			break;
		case EXTI_ANY_LOGIC:
			CLR_BIT(MCUCR,ISC11);
			SET_BIT(MCUCR,ISC01);
			break;
		case EXTI_RISING:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
		case EXTI_FALLING:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
		}
		break;
	case INT2:
		switch(sense){
			case EXTI_RISING:
				SET_BIT(MCUCSR,ISC2);

				break;
			case EXTI_FALLING:
				CLR_BIT(MCUCSR,ISC2);

				break;
		}
		break;
	}


}
