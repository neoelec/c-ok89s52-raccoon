/* ========================================================================== */
/*         Exp14_2a.c : Digital Clock using Timer 2 with Time Adjust          */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

static uint8_t cursor;              // LCD cursor position
static volatile uint8_t int_count;  // interrupt counter
static volatile uint8_t colon_flag; // colon blink flag
static volatile uint8_t second;     // second
static volatile uint8_t minute;     // minute
static volatile uint8_t hour;       // hour
static volatile uint8_t ampm;       // AM='A', PM='P'
static volatile __bit disp_flag;    // display update flag

void TF2_ISR(void) __interrupt(5)
{            /* Timer 2 int. service routine */
    TF2 = 0; // clear TF2 flag
    int_count--;
    if (int_count != 0) {
        return; // interrupt 20 times ?
    }

    int_count = 20;
    colon_flag ^= 0x01; // colon on or off ?
    disp_flag = 1;
    if (colon_flag != 0) {
        return;
    }

    second++;                                    // increment second
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
}

void Cursor_left(void) /* go cursor left */
{
    if (cursor == 0xC2) {
        cursor = 0xCF;
    } else if (cursor == 0xCF) {
        cursor -= 4;
    } else {
        cursor -= 3;
    }

    LCD_command(cursor);
}

void Cursor_right(void) /* go cursor right */
{
    if (cursor == 0xCF) {
        cursor = 0xC2;
    } else if (cursor == 0xCB) {
        cursor += 4;
    } else {
        cursor += 3;
    }

    LCD_command(cursor);
}

void Increment(void) /* increment time */
{
    uint8_t val;

    switch (cursor) {
    case 0xC2:
        ET2 = 0;
        hour++; // in case of hour
        if (hour == 13) {
            hour = 1;
        }

        val = hour;
        ET2 = 1;
        LCD_command(0xC2);
        LCD_02dec(val);
        LCD_command(cursor);
        break;
    case 0xC5:
        ET2 = 0;
        minute++; // in case of minute
        if (minute == 60) {
            minute = 0;
        }

        val = minute;
        ET2 = 1;
        LCD_command(0xC5);
        LCD_02dec(val);
        LCD_command(cursor);
        break;
    case 0xC8:
        ET2 = 0;
        second++; // in case of second
        if (second == 60) {
            second = 0;
        }

        val = second;
        ET2 = 1;
        LCD_command(0xC8);
        LCD_02dec(val);
        LCD_command(cursor);
        break;
    case 0xCB:
        ET2 = 0;
        if (ampm == 'A') {
            ampm = 'P'; // in case of AM/PM
        } else {
            ampm = 'A';
        }

        val = ampm;
        ET2 = 1;
        LCD_command(0xCB);
        LCD_data(val);
        LCD_command(cursor);
        break;
    default:
        break;
    }
}

void Decrement(void) /* decrement time */
{
    uint8_t val;

    switch (cursor) {
    case 0xC2:
        ET2 = 0;
        hour--; // in case of hour
        if (hour == 0) {
            hour = 12;
        }

        val = hour;
        ET2 = 1;
        LCD_command(0xC2);
        LCD_02dec(val);
        LCD_command(cursor);
        break;
    case 0xC5:
        ET2 = 0;
        minute--; // in case of minute
        if (minute == 0xFF) {
            minute = 59;
        }

        val = minute;
        ET2 = 1;
        LCD_command(0xC5);
        LCD_02dec(val);
        LCD_command(cursor);
        break;
    case 0xC8:
        ET2 = 0;
        second--; // in case of second
        if (second == 0xFF) {
            second = 59;
        }

        val = second;
        ET2 = 1;
        LCD_command(0xC8);
        LCD_02dec(val);
        LCD_command(cursor);
        break;
    case 0xCB:
        ET2 = 0;
        if (ampm == 'A') {
            ampm = 'P'; // in case of AM/PM
        } else {
            ampm = 'A';
        }

        val = ampm;
        ET2 = 1;
        LCD_command(0xCB);
        LCD_data(val);
        LCD_command(cursor);
        break;
    default:
        break;
    }
}

void main(void)
{
    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, " Digital Clock  "); // display title
    LCD_string(0xC0, "  12:00:00 AM   ");

    cursor = 0xCF;     // initial cursor position
    LCD_command(0x0F); // cursor ON
    LCD_command(cursor);

    hour = 12; // initial time
    ampm = 'A';
    colon_flag = 1; // colon blink flag
    int_count = 20; // software counter (40Hz/20 = 2Hz)

    T2CON = 0x00;                   // Timer 2, 16-bit reload mode
    T2MOD = 0x00;                   // (up counter)
    RCAP2H = (0 - 50000U) >> 8;     // initialize time constant
    RCAP2L = (0 - 50000U) & 0x00FF; // (24MHz/12/50000 = 40Hz)
    TH2 = (0 - 50000U) >> 8;        // initial Timer 2 value
    TL2 = (0 - 50000U) & 0x00FF;
    PT2 = 1; // interrupt priority
    TR2 = 1; // start Timer 2
    ET2 = 1; // enable Timer 2 interrupt
    EA = 1;

    while (true) {
        if (disp_flag) {
            uint8_t cf, colon, h, m, s, ap;

            ET2 = 0;
            disp_flag = 0;
            cf = colon_flag;
            h = hour;
            m = minute;
            s = second;
            ap = ampm;
            ET2 = 1;

            colon = (cf == 0) ? ' ' : ':';
            LCD_command(0xC4);
            LCD_data(colon);
            LCD_command(0xC7);
            LCD_data(colon);
            LCD_command(0xC2); // display hour
            LCD_02dec(h);
            LCD_command(0xC5); // display minute
            LCD_02dec(m);
            LCD_command(0xC8); // display second
            LCD_02dec(s);
            LCD_command(0xCB); // display AM/PM
            LCD_data(ap);
            LCD_command(cursor);
        }

        switch (Key_input()) { // key input
        case 0x0E:
            Cursor_left(); // if KEY4, go cursor left
            break;
        case 0x16:
            Cursor_right(); // if KEY3, go cursor right
            break;
        case 0x1A:
            Increment(); // if KEY2, increment time
            break;
        case 0x1C:
            Decrement(); // if KEY1, decrement time
            break;
        default:
            break;
        }
    }
}
