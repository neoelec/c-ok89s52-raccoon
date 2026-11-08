/* ========================================================================== */
/*                      Exp06_5.c : Bit Shift Left/Right                      */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t i, LED;
    unsigned char x;
    signed char y;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    while (true) {
        Beep();
        LCD_string(0x80, "        10011101"); // display title
        LCD_string(0xC0, " << 0 = 00000000");

        x = 0x9D;                  // unsigned char
        for (i = 0; i <= 8; i++) { // shift left
            LCD_command(0xC4);
            LCD_data(i + '0');
            LCD_command(0xC8);
            LCD_08bin(x);
            Delay_ms(2000);
            x <<= 1;
        }

        Beep();
        LCD_string(0x80, "        10011101"); // display title
        LCD_string(0xC0, " >> 0 = 00000000");

        x = 0x9D;                  // unsigned char
        for (i = 0; i <= 8; i++) { // shift right
            LCD_command(0xC4);
            LCD_data(i + '0');
            LCD_command(0xC8);
            LCD_08bin(x);
            Delay_ms(2000);
            x >>= 1;
        }

        Beep();
        LCD_string(0x80, " signed 10011101"); // display title
        LCD_string(0xC0, " >> 0 = 00000000");

        y = (signed char)0x9D;     // signed char
        for (i = 0; i <= 8; i++) { // shift right
            LCD_command(0xC4);
            LCD_data(i + '0');
            LCD_command(0xC8);
            LCD_08bin(y);
            Delay_ms(2000);
            y >>= 1;
        }

        Beep();
        LCD_string(0x80, " signed 01011101"); // display title
        LCD_string(0xC0, " >> 0 = 00000000");

        y = 0x5D;                  // signed char
        for (i = 0; i <= 8; i++) { // shift right
            LCD_command(0xC4);
            LCD_data(i + '0');
            LCD_command(0xC8);
            LCD_08bin(y);
            Delay_ms(2000);
            y >>= 1;
        }

        for (i = 1, LED = 0x01; i <= 5; i++) { // shift from LED1 to LED4
            DIG_SELECT = LED;
            Delay_ms(500);
            LED <<= 1;
        }
    }
}
