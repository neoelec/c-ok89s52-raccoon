/* ========================================================================== */
/*                      Exp06_3.c : Sequential Addition                       */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t i;
    uint16_t sum;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    while (true) {
        Beep();
        LCD_string(0x80, "1+2+3+ ... +100 "); // display title
        LCD_string(0xC0, "    = 00000     ");

        for (i = 1, sum = 0; i <= 100; i++) { // integer from 1 to 100
            sum += i;
        }

        LCD_command(0xC6); // display total sum
        LCD_5dec(sum);
        Delay_ms(2000);

        Beep();
        LCD_string(0x80, "1+2+3+ ... +255 "); // display title
        LCD_string(0xC0, "    = 00000     ");

        for (i = 1, sum = 0; i > 0; i++) { // integer from 1 to 255
            sum += i;
        }

        LCD_command(0xC6); // display total sum
        LCD_5dec(sum);
        Delay_ms(2000);
    }
}
