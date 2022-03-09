
#ifndef __ACCES_H__
#define __ACCES_H__

#include <stdint.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif //F_CPU

typedef struct
{
    uint8_t controlA;
    uint8_t controlB;
    uint8_t controlC;
    int8_t _reserved;
    uint8_t baudL;
    uint8_t baudH;
    uint8_t data;

} usart_t;

#define USART ((usart_t *)0xC0) // >>> map the pointer to fierst addres in usart chank

#define UBRR(BAUD) (F_CPU / 16 / BAUD - 1) // calculat the value of the baud reg for Async mode

#define _two_stop (1 << 2) | (1 << 3)

#endif //__ACCES_H__