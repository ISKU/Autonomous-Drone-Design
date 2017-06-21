/*
 * uart_api.h
 */

#ifndef __UART_API_H__
#define __UART_API_H__

#define UART_DEV_NAME "/dev/uart123"

#define	UART1		1
#define	UART2		2
#define	UART3		3

#define UART_PARNONE	0	/* Defines for setting parity */
#define UART_PARODD	1
#define UART_PAREVEN	2

#define	UART_NO_ERR	 0	/* Function call was successful */
#define	UART_BAD_CH	-1	/* Invalid communications port channel*/
#define	UART_RX_EMPTY	-2	/* Rx buffer is empty, no character available */
#define	UART_TX_FULL	-3	/* Tx buffer is full, could not deposit char */
#define	UART_TX_EMPTY	-4	/* If the Tx buffer is empty. */

struct uart_data {
    int uart_ch; // channel: UART1, UART2, UART3
    int buf_size;
    unsigned char *uart_buf;
};

struct uart_config {
    int uart_ch; // channel: UART1, UART2, UART3
    int baud;    // 1200, 2400, 4800, 9600, 38400, 57600, 115200
    int bits;    // 8
    int parity;  // UART_PARNONE, UART_PARODD, UART_PAREVEN
    int stops;   // 1, 2
};

/* Function command codes for io_ctl. */
#define UART_SET_CONFIG     0x6000 // use struct uart_config
#define UART_RXBUF_LEVEL    0x6001 // arg: channel
#define UART_DATA_READ      0x6002 // use struct uart_data
#define UART_TXBUF_FULL     0x6003
#define UART_DATA_WRITE     0x6004 // use struct uart_data
#define UART_RXBUF_CLEAR    0x6005
#define UART_TXBUF_CLEAR    0x6006


/* UART API Function Prototypes */
int uart_open (void);
void uart_close (void);
int uart_config(int ch, int baud, int bits, int parity, int stops);
int uart_write(int ch, unsigned char *ubuf, int size);
int uart_rx_level(int ch);
int uart_tx_buf_full(int ch);
int uart_read(int ch, unsigned char *ubuf, int size);
void uart1_buffer_write(unsigned char *buf, int size);
void uart1_buffer_read(unsigned char *buf, int size);

#endif // __UART_API_H__

