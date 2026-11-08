/* ========================================================================== */
/*                    Exp13_5.c : Stop Watch using Timer 0                    */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

static volatile uint16_t sec;    // seconds (0..999)
static volatile uint8_t csec;    // 1/100 seconds (0..99)
static volatile __bit disp_flag; // LCD update flag

static void Display_stopwatch(uint16_t s, uint8_t cs)
{
    LCD_command(0xC2);
    LCD_3dec(s);
    LCD_data('.');
    LCD_02dec(cs);
}

void TF0_ISR(void) __interrupt(1)
{                                /* Timer 0 int. service routine */
    TH0 = (0 - 20000U) >> 8;     // initial Timer 0 value
    TL0 = (0 - 20000U) & 0x00FF; // (24MHz/12/20000 = 100Hz)

    csec++;
    if (csec == 100) {
        csec = 0;
        sec++;
        if (sec == 1000) {
            sec = 0;
        }
    }

    disp_flag = 1;
}

void main(void)
{
    uint8_t run_flag = 0;
    uint16_t s;
    uint8_t cs;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " STOP WATCH(T0) "); // display title
    LCD_string(0xC0, "  000.00 [SEC]  ");

    TMOD = (TMOD & 0xF0) | 0x01; // Timer 0, mode 1
    TH0 = (0 - 20000U) >> 8;
    TL0 = (0 - 20000U) & 0x00FF;
    TF0 = 0;
    PT0 = 1;           // interrupt priority
    DIG_SELECT = 0x04; // LED3 on

    while (true) {
        if (disp_flag) {
            ET0 = 0;
            s = sec;
            cs = csec;
            disp_flag = 0;
            if (run_flag) {
                ET0 = 1;
            }

            Display_stopwatch(s, cs);
        }

        switch (Key_input()) {
        case 0x1C:
            if (run_flag == 1) {
                break; // if KEY1, start
            }

            DIG_SELECT = 0x01; // LED1 on
            run_flag = 1;
            ET0 = 1;
            EA = 1;
            TR0 = 1;
            break;
        case 0x16:
            if (run_flag == 1) {
                break; // if KEY3, reset
            }

            TH0 = (0 - 20000U) >> 8;
            TL0 = (0 - 20000U) & 0x00FF;
            TF0 = 0;
            sec = 0;
            csec = 0;
            disp_flag = 0;
            LCD_string(0xC0, "  000.00 [SEC]  ");
            DIG_SELECT = 0x04; // LED3 on
            break;
        case 0x0E:
            if (run_flag == 0) {
                break; // if KEY4, stop
            }

            TR0 = 0;
            ET0 = 0;
            run_flag = 0;
            disp_flag = 0;
            Display_stopwatch(sec, csec);
            DIG_SELECT = 0x08; // LED4 on
            break;
        default:
            break;
        }
    }
}
