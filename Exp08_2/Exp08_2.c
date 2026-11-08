/* ========================================================================== */
/*                 Exp08_2.c : Real Number Multiplication(2)                  */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    float x, y;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    LCD_string(0x80, " Real Multi(2)  "); // display title
    LCD_string(0xC0, "0.0 x 0.0 =00.00");

    while (true) {
        Beep();
        for (x = 1.1; x <= 9.9; x += 1.1) {     // multiplicand from 1.1 to 9.9
            for (y = 1.1; y <= 9.9; y += 1.1) { // multiplier from 1.1 to 9.9
                LCD_command(0xC0);
                LCD_1dec1(x); // display multiplicand
                LCD_command(0xC6);
                LCD_1dec1(y); // display multiplier
                LCD_command(0xCB);
                LCD_2dec2(x * y); // display multiplication
                Delay_ms(2000);
            }
        }
    }
}
