/*
 * ADC_interface.h
 *
 *  Created on: Sep 1, 2026
 *      Author: ot
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

void ADC_Init();
u16 ADC_ReadSynch(u8 channel);
u16 ADC_ReadASynch(u8 channel);


#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
