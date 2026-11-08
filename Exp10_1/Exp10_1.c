/* ========================================================================== */
/*                   Exp10_1.c : Key Input - No Debouncing                    */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t key;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, "   KEY INPUT    "); // display title
    LCD_string(0xC0, " P1 = 00011110  ");

    while (true) {
        LCD_command(0xC6);              // cursor position
        key = P1 & 0x1E;                // key input
        LCD_08bin(key);                 // display binary data
        DIG_SELECT = (key >> 1) ^ 0x0F; // display LED
    }
}
