/**
 * @file STD.h
 * @brief Standard type definitions and basic constant macros.
 * @details Provides portable explicit-width integer and floating-point type aliases 
 *          along with common standard definitions (True, false, NULL) for embedded applications.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef STD_H_
#define STD_H_

/**
 * @name Unsigned Integer Types
 * @{
 */
typedef unsigned char          u8;   /**< 8-bit unsigned integer  (0 to 255) */
typedef unsigned short int     u16;  /**< 16-bit unsigned integer (0 to 65,535) */
typedef unsigned long int      u32;  /**< 32-bit unsigned integer (0 to 4,294,967,295) */
typedef unsigned long long int u64;  /**< 64-bit unsigned integer */
/** @} */

/**
 * @name Signed Integer Types
 * @{
 */
typedef signed char            s8;   /**< 8-bit signed integer  (-128 to 127) */
typedef signed short int       s16;  /**< 16-bit signed integer (-32,768 to 32,767) */
typedef signed long int        s32;  /**< 32-bit signed integer (-2,147,483,648 to 2,147,483,647) */
typedef signed long long int   s64;  /**< 64-bit signed integer */
/** @} */

/**
 * @name Floating Point Types
 * @{
 */
typedef float                  f32;  /**< Single-precision 32-bit IEEE 754 floating point */
typedef double                 f64;  /**< Double-precision 64-bit IEEE 754 floating point */
/** @} */

/**
 * @name Common Constants
 * @{
 */
#define True    1   /**< Boolean True definition */
#define false   0   /**< Boolean False definition */

#ifndef NULL
#define NULL    ((void*)0)  /**< Null pointer definition */
#endif
/** @} */

#endif /* STD_H_ */