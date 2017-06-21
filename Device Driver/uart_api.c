/*
 * UART_API.C
 *
 * By Kim Jong Keol (jongkkim@adc.co.kr)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "uart_api.h"

static int __uart_dev = -1;

int uart_open (void)
{
    int handle;

    if ((handle = open(UART_DEV_NAME, O_RDWR)) < 0) {
        printf("Open Error %s\n", UART_DEV_NAME);
        return -1;
    }

    __uart_dev = handle;

    return 0;
}

void uart_close (void)
{
    close(__uart_dev);
}

int uart_config(int ch, int baud, int bits,
        int parity, int stops)
{
    struct uart_config uart_conf;

    uart_conf.uart_ch = ch;
    uart_conf.baud = baud;
    uart_conf.bits = bits;
    uart_conf.parity = parity;
    uart_conf.stops = stops;

    return ioctl(__uart_dev, UART_SET_CONFIG, &uart_conf);
}

int uart_tx_buf_full(int ch)
{
    return ioctl(__uart_dev, UART_TXBUF_FULL, ch);
}

int uart_write(int ch, unsigned char *ubuf, int size)
{
    struct uart_data uart_d;

    uart_d.uart_ch = ch;
    uart_d.buf_size = size;
    uart_d.uart_buf = ubuf;

    return ioctl(__uart_dev, UART_DATA_WRITE, &uart_d);
}

int uart_rx_level(int ch)
{
    return ioctl(__uart_dev, UART_RXBUF_LEVEL, ch);
}

int uart_read(int ch, unsigned char *ubuf, int size)
{
    struct uart_data uart_d;

    uart_d.uart_ch = ch;
    uart_d.buf_size = size;
    uart_d.uart_buf = ubuf;

    return ioctl(__uart_dev, UART_DATA_READ, &uart_d);
}

void uart1_buffer_write(unsigned char *buf, int size)
{
	int ret;
	
	while(uart_tx_buf_full(UART1) == 1);
	ret = uart_write(UART1, buf, size);
	if(ret<0) {
		printf("Maybe UART Buffer is Full!\n");
	}	
}

void uart1_buffer_read(unsigned char *buf, int size)
{
	int rx_len=0;
	int rx_cnt=0;

	while(1) {
		rx_cnt += rx_len;
		rx_len = uart_rx_level(UART1);
		uart_read(UART1, &buf[rx_cnt], rx_len);
		if(rx_cnt + rx_len >= size) break;
	}	
}




