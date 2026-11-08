/* ========================================================================== */
/*                Exp04_2.c : Hardware Time Delay Application                 */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void Timer0_ms(uint16_t ms) /* time delay for ms[ms] */
{
    uint16_t i, time;
    uint8_t hi, lo;

    if (ms == 0) {
        return;
    }

    TMOD = (TMOD & 0xF0) | 0x01; // Timer 0, mode 1

    for (i = 1; i <= ms; i++) {
        TR0 = 0;
        TH0 = 0x00; // initial Timer 0 value
        TL0 = 0x00;
        TR0 = 1; // Timer 0 run enable
        do {
            do {
                hi = TH0;
                lo = TL0;
            } while (hi != TH0);

            time = ((uint16_t)hi << 8) | lo;
        } while (time < 2000); // TH0:TL0 = 2000 ?
    }

    TR0 = 0;
}

void main(void)
{
    uint8_t mode, LED;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " H/W Time Delay "); // display title
    LCD_string(0xC0, "Press KEY4-KEY1!");

    mode = 1;   // initial speed mode
    LED = 0x05; // initial LED data

    while (true) {
        switch (Key_input()) { // key input
        case 0x1C:
            mode = 1;
            LCD_string(0xC0, "    100 [ms]    ");
            break;
        case 0x1A:
            mode = 2;
            LCD_string(0xC0, "    200 [ms]    ");
            break;
        case 0x16:
            mode = 3;
            LCD_string(0xC0, "    300 [ms]    ");
            break;
        case 0x0E:
            mode = 4;
            LCD_string(0xC0, "    400 [ms]    ");
            break;
        default:
            LED ^= 0x0F; // output LED with complement
            DIG_SELECT = LED;
            if (mode == 1) {
                Timer0_ms(100);
            } else if (mode == 2) {
                Timer0_ms(200);
            } else if (mode == 3) {
                Timer0_ms(300);
            } else {
                Timer0_ms(400);
            }

            break;
        }
    }
}
