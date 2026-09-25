/**
 * @file ADC_program.c
 * @brief Driver implementation for ATmega32 Analog-to-Digital Converter (ADC).
 * @details Implements ADC initialization, synchronous polling-based reads, 
 *          asynchronous interrupt-driven reads, and ISR handling.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#include "../../LIB/STD.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"

/**
 * @brief Global variable to store asynchronous interrupt conversion result.
 */
u16 int_reading;

/**
 * @brief Initializes ADC hardware settings (AVCC reference, 64 Prescaler, Enable bit).
 * @return void
 */
void ADC_Init(void)
{
    /* Disable Global Interrupts during configuration */
    CLR_BIT(SREG, SREG_E);

    SET_BIT(ADCSRA, ADIE);
    CLR_BIT(ADCSRA, ADEN);
    
    /* Select AVCC reference voltage */
    ADMUX = CH_select;
    
    /* Set Prescaler to 64 (16MHz / 64 = 250kHz ADC Clock) */
    ADCSRA |= ADC_64_PRE;
    
    /* Enable ADC Peripheral */
    SET_BIT(ADCSRA, ADEN);
}

/**
 * @brief Starts an analog conversion on a channel and waits synchronously for completion.
 * @param[in] channel Analog channel number (0 to 7).
 * @return u16 10-bit converted digital output value.
 */
u16 ADC_ReadSynch(u8 channel)
{
    u16 reading = 0;
    
    /* Clear channel selection bits and set target channel */
    ADMUX &= 0xE0;
    ADMUX |= channel;

    /* Start conversion */
    SET_BIT(ADCSRA, ADSC);

    /* Poll ADC Interrupt Flag until conversion finishes */
    while(GET_BIT(ADCSRA, ADIF) != 1);
    
    /* Clear flag by writing logical one */
    SET_BIT(ADCSRA, ADIF);
    
    /* Read 10-bit result (ADCL must be read first) */
    reading = ADCL;
    reading |= ((u16)ADCH << 8);

    return reading;
}

/**
 * @brief Initiates non-blocking asynchronous analog conversion on a selected channel.
 * @param[in] channel Analog channel number (0 to 7).
 * @return u16 Status or immediate register state.
 */
u16 ADC_ReadAsynch(u8 channel)
{
    ADMUX &= 0xE0;
    ADMUX |= channel;
    
    /* Enable Global Interrupts and ADC Interrupt */
    SET_BIT(SREG, SREG_E);
    SET_BIT(ADCSRA, ADIE);

    /* Start Conversion */
    SET_BIT(ADCSRA, ADSC);
}

/**
 * @brief ADC Conversion Complete Interrupt Service Routine (Vector 16).
 * @details Automatically triggers when asynchronous conversion is complete and stores 
 *          the 10-bit result in global variable \ref int_reading.
 */
void __vector_16(void) __attribute__((signal, used));
void __vector_16(void)
{
    int_reading = ADCL;
    int_reading |= ((u16)ADCH << 8);
}