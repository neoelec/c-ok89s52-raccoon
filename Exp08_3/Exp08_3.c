/* ========================================================================== */
/*                         Exp08_3.c : Real Division                          */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t i, j;
    float x, y;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    LCD_string(0x80, " Real Division  "); // display title
    LCD_string(0xC0, "0.0 / 0.0 = 0.00");

    while (true) {
        Beep();
        for (i = 1; i <= 9; i++) {
            x = i * 1.1f;
            for (j = 1; j <= 9; j++) {
                y = j * 1.1f;
                LCD_command(0xC0);
                LCD_1dec1(x); // display dividend
                LCD_command(0xC6);
                LCD_1dec1(y); // display divisor
                LCD_command(0xCC);
                LCD_1dec2(x / y); // display quotient
                Delay_ms(2000);
            }
        }
    }
}
