/*
 * DOTMAT_interface.h
 *
 *  Created on: Sep 5, 2026
 *      Author: ot
 */

#ifndef HAL_DOT_MATRIX_DOTMAT_INTERFACE_H_
#define HAL_DOT_MATRIX_DOTMAT_INTERFACE_H_

void DOTMAT_Init();

void DOTMAT_SetPixel(u8 x,u8 y,u8 state);
void DOTMAT_Clear();

void DOTMAT_Refresh();

#endif /* HAL_DOT_MATRIX_DOTMAT_INTERFACE_H_ */
