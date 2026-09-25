/**
 * @file USART_private.h
 * @brief Hardware memory-mapped register definitions and bit field offsets for ATmega32 USART.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_USART_PRIVATE_H_
#define MCAL_USART_PRIVATE_H_

/* Hardware Memory-Mapped Registers */
#define UCSRA     (*(volatile u8*)(0x2B))  /**< Control and Status Register A */
#define UCSRB     (*(volatile u8*)(0x2A))  /**< Control and Status Register B */
#define UCSRC     (*(volatile u8*)(0x40))  /**< Control and Status Register C */

#define UBRRL     (*(volatile u8*)(0x29))  /**< Baud Rate Register Low Byte */
#define UBRRH     (*(volatile u8*)(0x40))  /**< Baud Rate Register High Byte (Shares address with UCSRC) */

#define UDR       (*(volatile u8*)(0x2C))  /**< I/O Data Register */

/* UCSRC Register Bit Definitions */
#define UCPOL     0   /**< Clock Polarity (Synchronous mode) */
#define UCSZ0     1   /**< Character Size Bit 0 */
#define UCSZ1     2   /**< Character Size Bit 1 */
#define USBS      3   /**< Stop Bit Select */
#define UPM0      4   /**< Parity Mode Bit 0 */
#define UPM1      5   /**< Parity Mode Bit 1 */
#define UMSEL     6   /**< USART Mode Select (0 = Asynchronous, 1 = Synchronous) */
#define URSEL     7   /**< Register Select (1 = UCSRC, 0 = UBRRH) */

/* UCSRB Register Bit Definitions */
#define TXB8      0   /**< Transmit Data Bit 8 (for 9-bit data mode) */
#define RXB0      1   /**< Receive Data Bit 8 (for 9-bit data mode) */
#define UCSZ2     2   /**< Character Size Bit 2 */
#define TXEN      3   /**< Transmitter Enable */
#define RXEN      4   /**< Receiver Enable */
#define UDRIE     5   /**< Data Register Empty Interrupt Enable */
#define TXCIE     6   /**< TX Complete Interrupt Enable */
#define RXCIE     7   /**< RX Complete Interrupt Enable */

/* UCSRA Register Bit Definitions */
#define MPCM      0   /**< Multi-processor Communication Mode */
#define U2X       1   /**< Double Transmission Speed */
#define PE        2   /**< Parity Error */
#define DOR       3   /**< Data OverRun */
#define FE        4   /**< Frame Error */
#define UDRE      5   /**< Data Register Empty Flag */
#define TXC       6   /**< Transmit Complete Flag */
#define RXC       7   /**< Receive Complete Flag */

#endif /* MCAL_USART_PRIVATE_H_ */