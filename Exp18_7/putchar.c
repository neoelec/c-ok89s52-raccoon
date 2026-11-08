/******************************************************************************/
/*                                                                            */
/*   putchar.c: Modified by D.Y.Yoon for Serial Port                          */
/*                                                                            */
/******************************************************************************/

#include <ok89s52.h>

int putchar(int c) /* output a character to serial port */
{
    if ((uint8_t)c == '\n') {
        while (!TI) {
        }

        TI = 0;
        SBUF = 0x0D;
    }

    while (!TI) {
    }

    TI = 0;
    SBUF = c;

    return c;
}
