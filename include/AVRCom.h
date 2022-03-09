#ifndef __AVRCOM_H__
#define __AVRCOM_H__

#include <stdint.h>
#include <acces.h>
#define TOW_STOP _two_stop

void USART_Init(uint32_t baudRate, ...);
void USART_Transmit(unsigned char data);
void USART_Print(uint8_t *str);
void USART_Println(const char *str,...);

#endif //__AVRCOM_H__