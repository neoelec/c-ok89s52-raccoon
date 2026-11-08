/* ========================================================================== */
/*                  Exp18_3.c : Inline Assemble in C Program                  */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

volatile uint8_t LED;

void main(void)
{
    uint8_t i;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, "Inline Assemble "); // display title
    LCD_string(0xC0, "   LED Shift    ");

    while (true) {
        LED = 0x01;
        for (i = 1; i <= 4; i++) { // LED from 1 to 4
            /* clang-format off */
            __asm
                LED_CS = 0x8200; LED4 - LED1 output address
            MOV DPTR, #LED_CS
            MOV A, _LED; LED is global variable
            MOVX @DPTR, A
                 __endasm;
            /* clang-format on */
            Delay_ms(300);
            LED <<= 1;
        }

        LED = 0x08;
        for (i = 1; i <= 4; i++) { // LED from 4 to 1
            /* clang-format off */
            __asm
            MOV DPTR, #LED_CS
            MOV A, _LED; LED is global variable
            MOVX @DPTR, A
                 __endasm;
            /* clang-format on */
            Delay_ms(300);
            LED >>= 1;
        }
    }
}
