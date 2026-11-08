/* ========================================================================== */
/*             Exp11_3.c : 7-Segment LED Display - Numerical Data             */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

static uint8_t pattern[8]; // 7-segment LED pattern data

void LED_2hex(uint8_t number) /* display 2-digit hex number */
{
    pattern[0] = Bin2LED(number >> 4);   // 16^1
    pattern[1] = Bin2LED(number & 0x0F); // 16^0
    pattern[2] = Bin2LED('H');
}

void LED_3d(uint16_t number) /* display 3-digit decimal number */
{
    uint8_t i, flag;

    flag = 0;
    i = number / 100; // 10^2
    if (i == 0) {
        pattern[5] = 0x00;
    } else {
        pattern[5] = Bin2LED(i);
        flag = 1;
    }

    number = number % 100; // 10^1
    i = number / 10;
    if ((i == 0) && (flag == 0)) {
        pattern[6] = 0x00;
    } else {
        pattern[6] = Bin2LED(i);
        flag = 1;
    }

    i = number % 10; // 10^0
    pattern[7] = Bin2LED(i);
}

void main(void)
{
    uint8_t i, j, k, digit;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, "   LCD & LED    "); // display title
    LCD_string(0xC0, "   00H = 000    ");

    while (true) {
        for (i = 1; i > 0; i++) { // display from 1 to 255
            LCD_command(0xC3);    // display hexadecimal on LCD
            LCD_02hex(i);
            LCD_command(0xC9); // display decimal on LCD
            LCD_3dec(i);

            LED_2hex(i); // convert hex to LED pattern
            LED_3d(i);   // convert decimal to LED pattern

            for (j = 1; j <= 125; j++) { // display 7-segment LED
                for (k = 0, digit = 0x80; k <= 7; k++) {
                    DIG_SELECT = 0x00;        // blank before changing pattern
                    SEG_PATTERN = pattern[k]; // output segment pattern data
                    DIG_SELECT = digit;       // output digit select data
                    Delay_ms(1);              // delay 1ms
                    digit >>= 1;
                }
            }

            DIG_SELECT = 0x00; // turn off last digit during LCD update
        }
    }
}
