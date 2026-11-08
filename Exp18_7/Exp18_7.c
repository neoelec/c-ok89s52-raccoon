/* ========================================================================== */
/*              Exp18_7.c : Use printf_fast_f() for Serial Port               */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    int16_t i;
    float x, y;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    LCD_string(0x80, "sin(+000)=+0.000"); // display title
    LCD_string(0xC0, "cos(+000)=+0.000");

    T2CON = 0x34;        // TCLK=RCLK=1, TR2=1, C/-T2=0
    T2MOD = 0x00;        // (baud rate generator)
    RCAP2H = 65523 >> 8; // 57600 bps
    RCAP2L = 65523 & 0x00FF;
    SCON = 0x52; // 8 data, 1 stop, REN=TI=1
    i = SBUF;    // dummy read(clear SBUF)

    while (true) {
        Beep();
        for (i = -360; i <= +360; i += 30) {
            x = i * 3.141592654 / 180.;
            y = sinf(x);
            LCD_command(0x84);
            LCD_s3dec(i); // display sin()
            LCD_command(0x8A);
            LCD_s1dec3(y);
            printf_fast_f("sin(%c%03d)=%c%5.3f\n", (i >= 0) ? '+' : '-',
                          (i >= 0) ? i : -i, (y >= 0.0f) ? '+' : '-',
                          fabsf(y)); // printf_fast_f for sin output
            y = cosf(x);
            LCD_command(0xC4);
            LCD_s3dec(i); // display cos()
            LCD_command(0xCA);
            LCD_s1dec3(y);
            printf_fast_f("cos(%c%03d)=%c%5.3f\n\n", (i >= 0) ? '+' : '-',
                          (i >= 0) ? i : -i, (y >= 0.0f) ? '+' : '-',
                          fabsf(y)); // printf_fast_f for cos output
            Delay_ms(2000);
        }
    }
}
