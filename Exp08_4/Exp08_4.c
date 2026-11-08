/* ========================================================================== */
/*                    Exp08_4.c : Calculation of sqrtf(x)                     */
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

    LCD_string(0x80, " Real Function  "); // display title
    LCD_string(0xC0, "sqrt(00.0)=0.000");

    while (true) {
        Beep();
        for (x = 0.0; x <= 97.5; x += 2.5) {
            LCD_command(0xC5);
            LCD_2dec1(x); // display argument
            LCD_command(0xCB);
            LCD_1dec3(sqrtf(x)); // display sqrt
            Delay_ms(2000);
        }
    }
}
