/*
 * Shift_REG_interface.h
 */

#ifndef HAL_SHIFT_REG_SHIFT_REG_INTERFACE_H_
#define HAL_SHIFT_REG_SHIFT_REG_INTERFACE_H_


typedef struct {
	u8 Port;
    u8 DataPin;
    u8 ClockPin;
    u8 LatchPin;
} Shift_REG;



void Shift_REG_Init( Shift_REG* ptr);
void Shift_REG_ClockPulse( Shift_REG* ptr);
void Shift_REG_LatchPulse( Shift_REG* ptr);
void Shift_REG_SendByte( Shift_REG* ptr, u8 value);
void Shift_REG_SendTwoByte( Shift_REG* ptr, u16 value);

#endif /* HAL_SHIFT_REG_SHIFT_REG_INTERFACE_H_ */
