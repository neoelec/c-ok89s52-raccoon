/* ========================================================================== */
/*                    Exp13_6.c : Stop Watch using Timer 2                    */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

static volatile uint8_t csec;    // 1/100 second (0..99)
static volatile uint8_t second;  // second (0..59)
static volatile uint8_t minute;  // minute (0..59)
static volatile uint8_t hour;    // hour (0..99)
static volatile __bit disp_flag; // LCD update flag

static void Display_stopwatch(uint8_t h, uint8_t m, uint8_t s, uint8_t cs)
{
    LCD_command(0xC2);
    LCD_02dec(h);
    LCD_command(0xC5);
    LCD_02dec(m);
    LCD_command(0xC8);
    LCD_02dec(s);
    LCD_command(0xCB);
    LCD_02dec(cs);
}

void TF2_ISR(void) __interrupt(5)
{            /* Timer 2 int. service routine */
    TF2 = 0; // clear TF2 flag
    csec++;
    if (csec == 100) {
        csec = 0;
        second++;
        if (second == 60) {
            second = 0;
            minute++;
            if (minute == 60) {
                minute = 0;
                hour++;
                if (hour == 100) {
                    hour = 0;
                }
            }
        }
    }

    disp_flag = 1;
}

void main(void)
{
    uint8_t run_flag = 0;
    uint8_t h, m, s, cs;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " STOP WATCH(T2) "); // display title
    LCD_string(0xC0, "  00:00:00.00   ");

    T2CON = 0x00;                   // Timer 2 stopped during setup
    T2MOD = 0x00;                   // (up counter)
    RCAP2H = (0 - 20000U) >> 8;     // initialize time constant
    RCAP2L = (0 - 20000U) & 0x00FF; // (24MHz/12/20000 = 100Hz)
    TH2 = (0 - 20000U) >> 8;
    TL2 = (0 - 20000U) & 0x00FF;
    PT2 = 1;           // interrupt priority
    DIG_SELECT = 0x04; // LED3 on

    while (true) {
        if (disp_flag) {
            ET2 = 0;
            h = hour;
            m = minute;
            s = second;
            cs = csec;
            disp_flag = 0;
            if (run_flag) {
                ET2 = 1;
            }

            Display_stopwatch(h, m, s, cs);
        }

        switch (Key_input()) {
        case 0x1C:
            if (run_flag == 1) {
                break; // if KEY1, start
            }

            DIG_SELECT = 0x01; // LED1 on
            run_flag = 1;
            ET2 = 1;
            EA = 1;
            TR2 = 1;
            break;
        case 0x16:
            if (run_flag == 1) {
                break; // if KEY3, reset
            }

            TH2 = (0 - 20000U) >> 8;
            TL2 = (0 - 20000U) & 0x00FF;
            TF2 = 0;
            csec = 0;
            second = 0;
            minute = 0;
            hour = 0;
            disp_flag = 0;
            LCD_string(0xC0, "  00:00:00.00   ");
            DIG_SELECT = 0x04; // LED3 on
            break;
        case 0x0E:
            if (run_flag == 0) {
                break; // if KEY4, stop
            }

            TR2 = 0;
            ET2 = 0;
            run_flag = 0;
            disp_flag = 0;
            Display_stopwatch(hour, minute, second, csec);
            DIG_SELECT = 0x08; // LED4 on
            break;
        default:
            break;
        }
    }
}
