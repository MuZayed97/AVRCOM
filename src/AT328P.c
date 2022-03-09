#include <AVR/io.h>
#include <AVRCom.h>
#include <acces.h>
#include <stdarg.h>
#include <stdio.h>

char test;
int test1;

void USART_Init(uint32_t baudRate,...)
{   
    
    int i;
    va_list args;
    char *tt;
    va_start(args, baudRate);
    for (i=0; i<5; i++){
        *tt = va_arg(args, int);
        USART_Print(tt)
    }
    va_end(args);
    uint16_t temp = UBRR(baudRate);
    USART->baudH = (uint8_t)(temp >> 8);
    USART->baudL = (uint8_t)temp;

    USART->controlB |= (1 << TXEN0);
    USART->controlC |= (3 << UCSZ00);
}

void USART_Transmit(uint8_t data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    USART->data = data;
}

void USART_Print(uint8_t *str)
{

    for (str = str; *str; str++)
    {
        test = *str;
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        USART->data = (uint8_t)*str;
    }
    test = 'Z';
}

void USART_Println(const char *str,...)
{   

    // +++++++++++++++++++++create printf properties++++++++++++++++++++++++++
    // char * temp_s;
    // va_list args;
    // va_start(args, str);
    // vsprintf(temp_s, str, args);
    // va_end(args);
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    for (str = str; *str; str++)
    {
        test = *str;
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        USART->data = (uint8_t)*str;
    }
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    USART->data = '\n';
}