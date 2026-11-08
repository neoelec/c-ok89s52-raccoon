/* ========================================================================== */
/*                 Exp08_6.c : Calculation of sinf(x),cosf(x)                 */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <math.h>
#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    int16_t i;
    float x;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    LCD_string(0x80, "sin(+000)=+0.000"); // display title
    LCD_string(0xC0, "cos(+000)=+0.000");

    while (true) {
        Beep();
        for (i = -360; i <= +360; i += 30) {
            x = i * 3.141592654 / 180.;
            LCD_command(0x84);
            LCD_s3dec(i); // display sine
            LCD_command(0x8A);
            LCD_s1dec3(sinf(x));
            LCD_command(0xC4);
            LCD_s3dec(i); // display cosine
            LCD_command(0xCA);
            LCD_s1dec3(cosf(x));
            Delay_ms(2000);
        }
    }
}
