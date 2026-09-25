/**
 * @file GIE_private.h
 * @brief Register definitions and bit macros for Global Interrupt Enable (GIE).
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date August 2026
 */

#ifndef GIE_GIE_PRIVATE_H_
#define GIE_GIE_PRIVATE_H_

/** @brief AVR Status Register (SREG) memory-mapped I/O address. */
#define SREG        (*(volatile u8 *)(0x5F))

/** @brief Global Interrupt Enable bit index in SREG register. */
#define I           7

#endif /* GIE_GIE_PRIVATE_H_ */