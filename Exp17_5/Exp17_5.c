/* ========================================================================== */
/*              Exp17_5.c : D/A Converter Output Voltage by Key               */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

void main(void)
{
    uint8_t volt;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, "   D/A Output   "); // display title
    LCD_string(0xC0, " 80H = +00.0[V] ");

    volt = 0x80; // initial voltage 0.0[V]
    DAC_CS = volt;

    while (true) {
        switch (Key_input()) { // key input
        case 0x1C:
            volt += 0x10; // if KEY1, increment by 0x10
            DAC_CS = volt;
            break;
        case 0x1A:
            volt -= 0x10; // if KEY2, decrement by 0x10
            DAC_CS = volt;
            break;
        case 0x16:
            volt += 0x01; // if KEY3, increment by 0x01
            DAC_CS = volt;
            break;
        case 0x0E:
            volt -= 0x01; // if KEY4, decrement by 0x01
            DAC_CS = volt;
            break;
        default:
            break;
        }

        LCD_command(0xC1); // display D/A in HEX format
        LCD_02hex(volt);
        LCD_command(0xC7); // display D/A voltage
        LCD_s2dec1(volt);
    }
}
