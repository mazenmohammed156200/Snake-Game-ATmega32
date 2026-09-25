/**
 * @file TIMER0_program.c
 * @brief Implementation file for ATmega32 Timer0 driver.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"

/** @brief Global callback function pointer for Timer0 Overflow ISR */
static void (*ptr_OVF)(void) = NULL;

/** @brief Global callback function pointer for Timer0 Compare Match ISR */
static void (*ptr_CTC)(void) = NULL;

/**
 * @brief Initializes Timer0 according to static configuration settings.
 * @return void
 */
void TIMER0_Init(void)
{
    /* Select Waveform Generation Mode */
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

    /* Configure Output Compare Pin (OC0) Behavior */
#if (Timer0_Mode == TIMER0_NORMAL) || (Timer0_Mode == TIMER0_CTC)
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

#elif (Timer0_Mode == TIMER0_FAST_PWM) || (Timer0_Mode == TIMER0_PHASE_PWM)
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

    /* Configure Clock Prescaler */
    TCCR0 &= 0xF8;
    TCCR0 |= TIMER0_PRESCALER_VALUE;

    /* Disable interrupts by default */
    CLR_BIT(TIMSK, TOIE0);
    CLR_BIT(TIMSK, OCIE0);
}

/**
 * @brief Sets new prescaler value for Timer0 clock source.
 * @param[in] prescaler Selected clock source/prescaler.
 * @return void
 */
void Timer0_SetPrescaler(u8 prescaler)
{
    TCCR0 &= 0xF8;
    TCCR0 |= (prescaler & 0x07);
}

/**
 * @brief Enables or disables Timer0 Overflow Interrupt.
 * @param[in] enable 1 to enable, 0 to disable.
 * @return void
 */
void Timer0_OVF0_Interrupt_Enable(u8 enable)
{
    if (enable == 1)
    {
        SET_BIT(TIMSK, TOIE0);
    }
    else
    {
        CLR_BIT(TIMSK, TOIE0);
    }
}

/**
 * @brief Enables or disables Timer0 Compare Match Interrupt.
 * @param[in] enable 1 to enable, 0 to disable.
 * @return void
 */
void Timer0_COMP0_Interrupt_Enable(u8 enable)
{
    if (enable == 1)
    {
        SET_BIT(TIMSK, OCIE0);
    }
    else
    {
        CLR_BIT(TIMSK, OCIE0);
    }
}

/**
 * @brief Sets counter register (TCNT0) value.
 * @param[in] value Value from 0 to 255.
 * @return void
 */
void Timer0_SetTimerValue(u8 value)
{
    TCNT0 = value;
}

/**
 * @brief Sets compare match register (OCR0) value.
 * @param[in] value Value from 0 to 255.
 * @return void
 */
void Timer0_SetCompareValue(u8 value)
{
    OCR0 = value;
}

/**
 * @brief Reads current TCNT0 value.
 * @return u8 Current counter register value.
 */
u8 Timer0_GetTimerValue(void)
{
    return TCNT0;
}

/**
 * @brief Reads current OCR0 value.
 * @return u8 Current compare match register value.
 */
u8 Timer0_GetCompareValue(void)
{
    return OCR0;
}

/**
 * @brief Calculates timing counts and overflows for requested millisecond delay.
 * @param[in] ms Target time interval in milliseconds.
 * @param[out] ticks Pointer to store remaining preload ticks.
 * @param[out] overflow Pointer to store required overflow counts.
 * @return void
 */
void Timer0_GetCom(f32 ms, f32 *ticks, f32 *overflow)
{
    f32 timer_tick;
    f32 total_ticks;

    timer_tick = (1024.0f / F_CPU) * 1000.0f;
    total_ticks = ms / timer_tick;
    *overflow = total_ticks / 256.0f;

    if (*overflow > (u32)(*overflow))
    {
        *ticks = (1.0f - (*overflow - (u32)(*overflow))) * 256.0f;
        *overflow = (u32)(*overflow) + 1;
    }
    else
    {
        *ticks = 0;
    }
}

/**
 * @brief Registers callback function for Timer0 Overflow Interrupt.
 * @param[in] ptr Pointer to target function.
 * @return void
 */
void Set_Call_Back_OVF(void (*ptr)(void))
{
    if (ptr != NULL)
    {
        ptr_OVF = ptr;
    }
}

/**
 * @brief Registers callback function for Timer0 Compare Match Interrupt.
 * @param[in] ptr Pointer to target function.
 * @return void
 */
void Set_Call_Back_CTC(void (*ptr)(void))
{
    if (ptr != NULL)
    {
        ptr_CTC = ptr;
    }
}

/**
 * @brief ISR Handler for Timer0 Overflow Interrupt Vector (11).
 */
void __vector_11(void) __attribute__((signal, used));
void __vector_11(void)
{
    if (ptr_OVF != NULL)
    {
        ptr_OVF();
    }
}

/**
 * @brief ISR Handler for Timer0 Compare Match Interrupt Vector (10).
 */
void __vector_10(void) __attribute__((signal, used));
void __vector_10(void)
{
    if (ptr_CTC != NULL)
    {
        ptr_CTC();
    }
}