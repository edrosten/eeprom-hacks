//#include <avr/io.h>
//#include <util/delay.h>
#include <Arduino.h>




/*template<class C> 
void write_bits_LSB_first(C data, int bits_to_write)
{
	

}
*/


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

