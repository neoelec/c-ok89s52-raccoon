/* ========================================================================== */
/*                  Exp14_1.c : Digital Clock using Timer 0                   */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

static volatile uint16_t int_count; // interrupt counter
static volatile uint8_t second;     // second
static volatile uint8_t minute;     // minute
static volatile uint8_t hour;       // hour
static volatile uint8_t ampm;       // AM='A', PM='P'
static volatile __bit disp_flag;    // display update flag

void TF0_ISR(void) __interrupt(1)
{ /* Timer 0 int. service routine */
    int_count--;
    if (int_count != 0) {
        return; // interrupt 8000 times ?
    }

    int_count = 8000;
    second++;                                    // if yes, increment second
    if (second == 60) {                          // 60 seconds ?
        second = 0;                              // if yes, clear seconds
        minute++;                                //         and increment minute
        if (minute == 60) {                      // 60 minutes ?
            minute = 0;                          // if yes, clear minutes
            hour++;                              //         and increment hour
            if ((hour == 12) && (ampm == 'A')) { // 12 hours ?
                ampm = 'P';                      // if yes, decide AM/PM
            } else if ((hour == 12) && (ampm == 'P')) {
                ampm = 'A';
            } else if (hour == 13) {
                hour = 1;
            }
        }
    }

    disp_flag = 1;
}

void main(void)
{
    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " Digital Clock  "); // display title
    LCD_string(0xC0, "  12:00:00 AM   ");

    hour = 12; // initial time
    ampm = 'A';
    int_count = 8000; // software counter (8000Hz/8000 = 1Hz)

    TMOD = (TMOD & 0xF0) | 0x02; // Timer 0, mode 2
    TH0 = 0 - 250;               // initialize time constant
    TL0 = 0 - 250;               // (24MHz/12/250 = 8000Hz)
    TF0 = 0;
    PT0 = 1; // interrupt priority
    TR0 = 1; // start Timer 0
    ET0 = 1; // enable Timer 0 interrupt
    EA = 1;

    while (true) {
        if (disp_flag) {
            uint8_t h, m, s, ap;

            ET0 = 0;
            disp_flag = 0;
            h = hour;
            m = minute;
            s = second;
            ap = ampm;
            ET0 = 1;

            LCD_command(0xC2); // display hour
            LCD_02dec(h);
            LCD_command(0xC5); // display minute
            LCD_02dec(m);
            LCD_command(0xC8); // display second
            LCD_02dec(s);
            LCD_command(0xCB); // display AM/PM
            LCD_data(ap);
        }
    }
}
