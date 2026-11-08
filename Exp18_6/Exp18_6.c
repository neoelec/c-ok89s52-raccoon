/* ========================================================================== */
/*                Exp18_6.c : C Program for C & Assembly Link                 */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

uint8_t Mul_8bit(uint8_t i, uint8_t j);
void Delay_1sec(void);

void main(void)
{
    uint8_t i, j, k;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " Multiplication "); // display title
    LCD_string(0xC0, "   0 * 0 = 00   ");

    while (true) {
        for (i = 2; i <= 9; i++) {
            for (j = 1; j <= 9; j++) {
                LCD_command(0xC3); // display multiplicand
                LCD_data(i + '0');
                LCD_command(0xC7); // display multiplier
                LCD_data(j + '0');
                k = Mul_8bit(i, j); // call assembly routine(1)
                LCD_command(0xCB);  // display multiplication
                LCD_2dec(k);
                Delay_1sec(); // call assembly routine(2)
            }

            Beep();
        }
    }
}
