#include <avr/io.h>
#include <AVRCom.h>
#include <util/delay.h>

int main()
{
    while (1)
    {
    USART_Init(9600, 50,10,29);
        // USART_Println("alyeldeen %d",10);
        USART_Transmit('D');
        // USART_Transmit('\n');
        _delay_ms(200);
    }

    return 0;
}
