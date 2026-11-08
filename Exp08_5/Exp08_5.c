/* ========================================================================== */
/*                Exp08_5.c : Calculation of logf(x),log10f(x)                */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <math.h>
#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    float x;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    LCD_string(0x80, "  log(00.)=0.000"); // display title
    LCD_string(0xC0, "log10(00.)=0.000");

    while (true) {
        Beep();
        for (x = 5.0; x <= 95.0; x += 5.0) {
            LCD_command(0x86);
            LCD_2dec0(x); // display natural logarithm
            LCD_command(0x8B);
            LCD_1dec3(logf(x));
            LCD_command(0xC6);
            LCD_2dec0(x); // display common logarithm
            LCD_command(0xCB);
            LCD_1dec3(log10f(x));
            Delay_ms(2000);
        }
    }
}
