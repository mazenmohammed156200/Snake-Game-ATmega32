/*
 * TIMER_program.c
 *
 *  Created on: Sep 2, 2026
 *      Author: ot
 */


#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"

static void (*ptr_OVF)()=NULL;
static void (*ptr_CTC)()=NULL;

void TIMER0_Init(){
	// WGM00
#if Timer0_Mode == TIMER0_NORMAL
	CLR_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);

#elif Timer0_Mode == TIMER0_CTC
	CLR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);

#elif Timer0_Mode == TIMER0_FAST_PWM
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);

#elif Timer0_Mode == TIMER0_PHASE_PWM
	SET_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);

#endif
	// COM00
#if Timer0_Mode == TIMER0_NORMAL ||Timer0_Mode == TIMER0_CTC

	#if Timer0_OC_Mode == Timer0_OC_Normal
		CLR_BIT(TCCR0, COM00);
		CLR_BIT(TCCR0, COM01);

	#elif Timer0_OC_Mode == Timer0_OC_TOG
		SET_BIT(TCCR0, COM00);
		CLR_BIT(TCCR0, COM01);

	#elif Timer0_OC_Mode == Timer0_OC_CLR
		CLR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
	#elif Timer0_OC_Mode == Timer0_OC_SET
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);

	#endif

#elif Timer0_Mode == TIMER0_FAST_PWM

	#if Timer0_OC_Mode == Timer0_OC_Normal
		CLR_BIT(TCCR0, COM00);
		CLR_BIT(TCCR0, COM01);

	#elif Timer0_OC_Mode == Timer0_OC_CLR
		CLR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);

	#elif Timer0_OC_Mode == Timer0_OC_SET
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);

	#endif

#elif Timer0_Mode == TIMER0_PHASE_PWM

	#if Timer0_OC_Mode == Timer0_OC_Normal
		CLR_BIT(TCCR0, COM00);
		CLR_BIT(TCCR0, COM01);

	#elif Timer0_OC_Mode == Timer0_OC_CLR
		CLR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);

	#elif Timer0_OC_Mode == Timer0_OC_SET
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);

	#endif
#endif

		// CS00
		TCCR0 &= 0xF8;
		TCCR0 |= TIMER0_PRESCALER_VALUE;
		// TOIE0
		CLR_BIT(TIMSK,TOIE0);

		// OCIE0
		CLR_BIT(TIMSK,OCIE0);

	}


void Timer0_SetPrescaler(u8 prescaler)
	{
		TCCR0&=0xF8;
		TCCR0|=prescaler;
	}

void Timer0_OVF0_Interrupt_Enable(u8 enable)
	{
		if(enable==1){
			SET_BIT(TIMSK,TOIE0);
		}else{
			CLR_BIT(TIMSK, TOIE0);
		}
	}
void Timer0_COMP0_Interrupt_Enable(u8 enable)
	{
		if(enable==1){
			SET_BIT(TIMSK,OCIE0);
		}else{
			CLR_BIT(TIMSK, OCIE0);
		}
	}

void Timer0_SetTimerValue(u8 value)
	{
		TCNT0 = value;
	}

void Timer0_SetCompareValue(u8 value)
	{
		OCR0 = value;

	}

u8 Timer0_GetTimerValue()
	{
		return TCNT0;

	}

u8 Timer0_GetCompareValue()
	{
		return OCR0;
	}


void Timer0_GetCom(f32 ms, f32 *ticks, f32 *overflow)
{
    f32 timer_tick;
    f32 total_ticks;

    timer_tick = (1024.0f / F_CPU) * 1000.0f;

    total_ticks = (ms) / timer_tick;

    *overflow = total_ticks / 256.0f;

    if (*overflow > (u32)(*overflow))
    {
        *ticks =
            (1.0f - (*overflow - (u32)(*overflow))) * 256.0f;

        *overflow = (u32)(*overflow) + 1;
    }
    else
    {
        *ticks = 0;
    }
}
void Set_Call_Back_OVF(void (*ptr)()){
	if (ptr != NULL)
	ptr_OVF=ptr;
}

void Set_Call_Back_CTC(void (*ptr)()){
	if (ptr != NULL)
	ptr_CTC=ptr;
}

void __vector_11(void)__attribute__((signal,used));
void __vector_11(void)
{
    if (ptr_OVF != NULL)
    {
    	ptr_OVF();
    }
}
void __vector_10(void)__attribute__((signal,used));
void __vector_10(void)
{
    if (ptr_CTC != NULL)
    {
    	ptr_CTC();
    }
}
