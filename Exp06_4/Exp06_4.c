/* ========================================================================== */
/*                       Exp06_4.c : Bit-Wise Operation                       */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t x, LED;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    LED = 0x00; // intial LED
    DIG_SELECT = LED;

    while (true) {
        Beep();
        LCD_string(0x80, "        10011101"); // display title
        LCD_string(0xC0, "AND 0F =00000000");

        x = 0x9D; // 0x9D & 0x0F = 0x0D
        LCD_command(0xC8);
        LCD_08bin(x & 0x0F);
        LED ^= 0x01;
        DIG_SELECT = LED;
        Delay_ms(3000);

        LCD_string(0x80, "        10011101"); // display title
        LCD_string(0xC0, " OR 0F =00000000");

        x = 0x9D; // 0x9D | 0x0F = 0x9F
        LCD_command(0xC8);
        LCD_08bin(x | 0x0F);
        LED ^= 0x02;
        DIG_SELECT = LED;
        Delay_ms(3000);

        LCD_string(0x80, "        10011101"); // display title
        LCD_string(0xC0, "XOR 0F =00000000");

        x = 0x9D; // 0x9D ^ 0x0F = 0x92
        LCD_command(0xC8);
        LCD_08bin(x ^ 0x0F);
        LED ^= 0x04;
        DIG_SELECT = LED;
        Delay_ms(3000);
    }
}
