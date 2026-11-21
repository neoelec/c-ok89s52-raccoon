#include <stdbool.h>
#include <stdint.h>

#include <at89s52.h>

SFRX(SEG_PATTERN, 0x8100); /* segment pattern data */
SFRX(DIG_SELECT, 0x8200);  /* digit select data */

void Delay_ms(uint16_t ms) /* time delay for ms[ms] at 24MHz */
{
    uint8_t i;

    while (ms--) {
        i = 248;
        do {
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
        } while (--i);
    }
}

void main(void) /* main function */
{
    uint8_t LED = 0x03;

    SEG_PATTERN = 0x00; // 7-segment LED off

    while (true) {
        LED = LED ^ 0x0F; // blink LED4 - LED1
        DIG_SELECT = LED;
        Delay_ms(500); // delay 500 ms
    }
}
