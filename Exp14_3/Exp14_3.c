/* ========================================================================== */
/*                  Exp14_3.c : Digital Clock using DS12C887                  */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

static uint8_t cursor; // cursor position

static uint8_t Max_date(uint8_t year, uint8_t month)
{
    uint8_t y;

    if (month == 0x02) {
        y = (year >> 4) * 10 + (year & 0x0F);
        return ((y & 0x03) == 0) ? 0x29 : 0x28;
    }

    if ((month == 0x04) || (month == 0x06) || (month == 0x09) ||
        (month == 0x11)) {
        return 0x30;
    }

    return 0x31;
}

void DSP_RTC(void) /* display clock from RTC */
{
    uint16_t timeout = 5000;
    uint8_t year, month, date, weekday, hour, minute, second;

    while ((RTC_A & 0x80) && --timeout) { // wait until UIP == 0
    }

    year = RTC_YEAR;
    month = RTC_MONTH;
    date = RTC_DATE;
    weekday = RTC_WEEKDAY;
    hour = RTC_HOUR;
    minute = RTC_MINUTE;
    second = RTC_SECOND;

    LCD_command(0x0C); // cursor OFF

    LCD_command(0x81); // display year
    LCD_2BCD(0x20);
    LCD_2BCD(year);

    LCD_command(0x86); // display month
    LCD_2BCD(month);

    LCD_command(0x89); // display date
    LCD_2BCD(date);

    if (weekday == 1) { // display weekday
        LCD_string(0x8C, "SUN");
    } else if (weekday == 2) {
        LCD_string(0x8C, "MON");
    } else if (weekday == 3) {
        LCD_string(0x8C, "TUE");
    } else if (weekday == 4) {
        LCD_string(0x8C, "WED");
    } else if (weekday == 5) {
        LCD_string(0x8C, "THU");
    } else if (weekday == 6) {
        LCD_string(0x8C, "FRI");
    } else {
        LCD_string(0x8C, "SAT");
    }

    LCD_command(0xC2); // display hour
    LCD_2BCD(hour & 0x7F);
    LCD_command(0xCB); // display AM, PM
    if (hour < 0x80) {
        LCD_data('A');
    } else {
        LCD_data('P');
    }

    LCD_command(0xC5); // display minute
    LCD_2BCD(minute);

    LCD_command(0xC8); // display second
    LCD_2BCD(second);

    LCD_command(cursor); // go cursor position
    LCD_command(0x0F);   // cursor ON
    Delay_ms(10);        // time delay for cursor

    if ((minute == 0x00) && (second == 0x00)) { // beep for each o'clock
        Beep();
        Delay_ms(950);
    }
}

void Cursor_left(void) /* go cursor left */
{
    if (cursor == 0xCF) {
        cursor = 0xCC;
    } else if (cursor == 0xCC) {
        cursor = 0xC9;
    } else if (cursor == 0xC9) {
        cursor = 0xC6;
    } else if (cursor == 0xC6) {
        cursor = 0xC3;
    } else if (cursor == 0xC3) {
        cursor = 0x8E;
    } else if (cursor == 0x8E) {
        cursor = 0x8A;
    } else if (cursor == 0x8A) {
        cursor = 0x87;
    } else if (cursor == 0x87) {
        cursor = 0x84;
    } else if (cursor == 0x84) {
        cursor = 0xCF;
    }
}

void Cursor_right(void) /* go cursor right */
{
    if (cursor == 0xCF) {
        cursor = 0x84;
    } else if (cursor == 0x84) {
        cursor = 0x87;
    } else if (cursor == 0x87) {
        cursor = 0x8A;
    } else if (cursor == 0x8A) {
        cursor = 0x8E;
    } else if (cursor == 0x8E) {
        cursor = 0xC3;
    } else if (cursor == 0xC3) {
        cursor = 0xC6;
    } else if (cursor == 0xC6) {
        cursor = 0xC9;
    } else if (cursor == 0xC9) {
        cursor = 0xCC;
    } else if (cursor == 0xCC) {
        cursor = 0xCF;
    }
}

void Increment(void) /* increment time */
{
    uint8_t val, max_date;

    if (cursor == 0xCF) {
        return;
    }

    RTC_B = 0x80; // SET=1: inhibit update during write
    switch (cursor) {
    case 0x84:
        val = RTC_YEAR; // in case of year
        if (val == 0x99) {
            val = 0x00;
        } else {
            val = BCD_increment(val);
        }

        RTC_YEAR = val;
        max_date = Max_date(val, RTC_MONTH);
        if (RTC_DATE > max_date) {
            RTC_DATE = max_date;
        }

        break;
    case 0x87:
        val = RTC_MONTH; // in case of month
        if (val == 0x12) {
            val = 0x01;
        } else {
            val = BCD_increment(val);
        }

        RTC_MONTH = val;
        max_date = Max_date(RTC_YEAR, val);
        if (RTC_DATE > max_date) {
            RTC_DATE = max_date;
        }

        break;
    case 0x8A:
        max_date = Max_date(RTC_YEAR, RTC_MONTH);
        val = RTC_DATE; // in case of date
        if (val >= max_date) {
            val = 0x01;
        } else {
            val = BCD_increment(val);
        }

        RTC_DATE = val;
        break;
    case 0x8E:
        val = RTC_WEEKDAY; // in case of weekday
        if (val == 0x07) {
            val = 0x01;
        } else {
            val++;
        }

        RTC_WEEKDAY = val;
        break;
    case 0xC3:
        val = RTC_HOUR; // in case of hour
        if (val == 0x12) {
            val = 0x01;
        } else if (val == 0x92) {
            val = 0x81;
        } else {
            val = BCD_increment(val);
        }

        RTC_HOUR = val;
        break;
    case 0xC6:
        val = RTC_MINUTE; // in case of minute
        if (val == 0x59) {
            val = 0x00;
        } else {
            val = BCD_increment(val);
        }

        RTC_MINUTE = val;
        break;
    case 0xC9:
        val = RTC_SECOND; // in case of second
        if (val == 0x59) {
            val = 0x00;
        } else {
            val = BCD_increment(val);
        }

        RTC_SECOND = val;
        break;
    case 0xCC:
        val = RTC_HOUR; // in case of AM/PM
        if (val < 0x80) {
            val |= 0x80;
        } else {
            val &= 0x7F;
        }

        RTC_HOUR = val;
        break;
    default:
        break;
    }

    RTC_B = 0x00; // SET=0: resume RTC updates
}

void Decrement(void) /* decrement time */
{
    uint8_t val, max_date;

    if (cursor == 0xCF) {
        return;
    }

    RTC_B = 0x80; // SET=1: inhibit update during write
    switch (cursor) {
    case 0x84:
        val = RTC_YEAR; // in case of year
        if (val == 0x00) {
            val = 0x99;
        } else {
            val = BCD_decrement(val);
        }

        RTC_YEAR = val;
        max_date = Max_date(val, RTC_MONTH);
        if (RTC_DATE > max_date) {
            RTC_DATE = max_date;
        }

        break;
    case 0x87:
        val = RTC_MONTH; // in case of month
        if (val == 0x01) {
            val = 0x12;
        } else {
            val = BCD_decrement(val);
        }

        RTC_MONTH = val;
        max_date = Max_date(RTC_YEAR, val);
        if (RTC_DATE > max_date) {
            RTC_DATE = max_date;
        }

        break;
    case 0x8A:
        max_date = Max_date(RTC_YEAR, RTC_MONTH);
        val = RTC_DATE; // in case of date
        if ((val <= 0x01) || (val > max_date)) {
            val = max_date;
        } else {
            val = BCD_decrement(val);
        }

        RTC_DATE = val;
        break;
    case 0x8E:
        val = RTC_WEEKDAY; // in case of weekday
        if (val == 0x01) {
            val = 0x07;
        } else {
            val--;
        }

        RTC_WEEKDAY = val;
        break;
    case 0xC3:
        val = RTC_HOUR; // in case of hour
        if (val == 0x01) {
            val = 0x12;
        } else if (val == 0x81) {
            val = 0x92;
        } else {
            val = BCD_decrement(val);
        }

        RTC_HOUR = val;
        break;
    case 0xC6:
        val = RTC_MINUTE; // in case of minute
        if (val == 0x00) {
            val = 0x59;
        } else {
            val = BCD_decrement(val);
        }

        RTC_MINUTE = val;
        break;
    case 0xC9:
        val = RTC_SECOND; // in case of second
        if (val == 0x00) {
            val = 0x59;
        } else {
            val = BCD_decrement(val);
        }

        RTC_SECOND = val;
        break;
    case 0xCC:
        val = RTC_HOUR; // in case of AM/PM
        if (val < 0x80) {
            val |= 0x80;
        } else {
            val &= 0x7F;
        }

        RTC_HOUR = val;
        break;
    default:
        break;
    }

    RTC_B = 0x00; // SET=0: resume RTC updates
}

void main(void)
{
    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module

    LCD_string(0x80, " Digital Clock  "); // display logo
    LCD_string(0xC0, "  by DS12C887   ");
    Delay_ms(2000);

    if (RTC_FLAG != 'G') { // RTC data are available ?
        Beep();
        Delay_ms(100);
        Beep();
        RTC_FLAG = 'G';     // initialize RTC data flag
        RTC_B = 0x80;       // SET=1: inhibit update during initialization
        RTC_YEAR = 0x06;    // initialize year(2006)
        RTC_MONTH = 0x01;   // initialize month(01)
        RTC_DATE = 0x01;    // initialize date(01)
        RTC_WEEKDAY = 0x01; // initialize weekday(SUN)
        RTC_HOUR = 0x12;    // initialize hour(12)
        RTC_MINUTE = 0x00;  // initialize minute(00)
        RTC_SECOND = 0x00;  // initialize second(00)
        RTC_A = 0x2F;       // oscillator ON, SQW=2Hz
        RTC_B = 0x00;       // SET=0, interrupt disable, SQW disable
    } else {
        Beep();
    }

    LCD_string(0x80, " 2006/01/01 SUN "); // display title
    LCD_string(0xC0, "  12:00:00 AM   ");
    LCD_command(0x0F); // cursor ON, cursor blink
    cursor = 0xCF;     // initial cursor position

    while (true) {
        DSP_RTC(); // display clock

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
