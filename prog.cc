#include <avr/io.h>
#include <util/delay.h>
int main()
{
    // DDRB  Data Direction Register for port B
    // 1 corresponds to output. 0 for input.
    // _BV is Bit Value, i.e. BV(x) is 1<<x
    DDRB |= _BV(DDB5); 
 
    while(1) 
    {
    PORTB^=_BV(PB5);
        _delay_ms(100);
    }
}

