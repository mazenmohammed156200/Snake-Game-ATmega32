/**
 * @file BIT_MATH.h
 * @brief Bitwise manipulation macros for register access and bit-level operations.
 * @details Provides standard macros for setting, clearing, toggling, and getting specific bits 
 *          within memory-mapped control registers or variables.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/**
 * @brief Sets a specific bit to 1 in a register or variable.
 * @param[in,out] REG Target register or variable.
 * @param[in] BIT Zero-based index of the bit to set.
 */
#define SET_BIT(REG, BIT)    ((REG) |= (1U << (BIT)))

/**
 * @brief Clears a specific bit to 0 in a register or variable.
 * @param[in,out] REG Target register or variable.
 * @param[in] BIT Zero-based index of the bit to clear.
 */
#define CLR_BIT(REG, BIT)    ((REG) &= ~(1U << (BIT)))

/**
 * @brief Toggles (flips) the value of a specific bit in a register or variable.
 * @param[in,out] REG Target register or variable.
 * @param[in] BIT Zero-based index of the bit to toggle.
 */
#define TOG_BIT(REG, BIT)    ((REG) ^= (1U << (BIT)))

/**
 * @brief Reads the value of a specific bit from a register or variable.
 * @param[in] REG Target register or variable.
 * @param[in] BIT Zero-based index of the bit to read.
 * @return 1 if the bit is set, 0 if the bit is clear.
 */
#define GET_BIT(REG, BIT)    (((REG) >> (BIT)) & 0x01U)

#endif /* BIT_MATH_H_ */