/******************************************************************************/
/*                                                                            */
/*   putchar.c: Modified by D.Y.Yoon for Text LCD module.                     */
/*                                                                            */
/******************************************************************************/

#include <ok89s52.h>

int putchar(int c)
{
    if ((uint8_t)c == '\n') { // if LF, move cursor to 2nd line
        LCD_command(0xC0);
        return c;
    }

    LCD_WR_DATA = (uint8_t)c; // output character
    Delay_us(50);

    return c;
}
