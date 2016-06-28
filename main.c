#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= 1 << PINB0;    // Set Direction for output for PINB0 (First LED)
    PORTB ^= 1 << PINB0;   // Toggling only Pin 0 on port B
    DDRB |= 1 << PINB2;    // Set Direction for output for PINB1 (Second LED)
    DDRB &= ~(1 << PINB1); // Data Direction Register input PINB1
    PORTB |= 1 << PINB1;   // Set PINB1 to a high reading

    int pressed = 0;
    int pressed_confidence_level = 0;
    int released_confidence_level = 0;

    while (1) {
        if (bit_is_clear(PINB, 1)) {
            pressed_confidence_level++;
            if (pressed_confidence_level > 800) {
                if (pressed == 0) {
                    PORTB ^= 1 << PINB0;
                    PORTB ^= 1 << PINB2;
                    pressed = 1;
                }
                pressed_confidence_level = 0;
            }
        } else {
            released_confidence_level++;
            if (released_confidence_level > 800) {
                pressed = 0;
                released_confidence_level = 0;
            }
        }
    }
}
