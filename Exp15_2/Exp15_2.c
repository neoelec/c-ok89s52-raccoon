/* ========================================================================== */
/*               Exp15_2.c : RS-232C Communication by Interrupt               */
/* ========================================================================== */
/*                         Designed and programmed by Duck-Yong Yoon in 2005. */

#include <stdbool.h>

#include <at89s52.h> // include AT89S52 definition file
#include <ok89s52.h> // include OK-89S52 kit function

#define RX_BUF_SIZE 32

static uint8_t rx_buf[RX_BUF_SIZE];
static volatile uint8_t rx_head;
static volatile uint8_t rx_tail;
static volatile __bit tx_busy;

void TXD_char(uint8_t character) /* transmit a character */
{
    while (tx_busy) {
        ; // wait until previous byte completes
    }

    tx_busy = 1;
    SBUF = character; // transmit a character
}

void TXD_string(const char *string) /* transmit a string */
{
    while (*string != '\0') {
        TXD_char(*string);
        string++;
    }
}

void TIRI_ISR(void) __interrupt(4)
{             /* serial int. service routine */
    if (RI) { // receive ready ?
        uint8_t ch = SBUF;
        uint8_t next = (rx_head + 1) & (RX_BUF_SIZE - 1);

        RI = 0;
        if (next != rx_tail) {
            rx_buf[rx_head] = ch;
            rx_head = next;
        }
    }

    if (TI) { // transmit complete ?
        TI = 0;
        tx_busy = 0;
    }
}

void main(void)
{
    uint8_t cursor;

    Kit_initialize(); // initialize OK-89S52 kit
    Delay_ms(50);     // wait for system stabilization
    LCD_initialize(); // initialize text LCD module
    Beep();

    LCD_string(0x80, "    RS-232C     "); // display title
    LCD_string(0xC0, "                ");

    LCD_command(0x0F); // cursor ON
    LCD_command(0xC0); // initialize cursor position
    cursor = 1;

    T2CON = 0x34;        // TCLK=RCLK=1, TR2=1, C/-T2=0
    T2MOD = 0x00;        // (baud rate generator)
    RCAP2H = 65523 >> 8; // 57600 bps
    RCAP2L = 65523 & 0x00FF;
    SCON = 0x50; // 8 data, 1 stop, REN=1, TI=0, RI=0
    (void)SBUF;  // dummy read(clear SBUF)
    RI = 0;
    TI = 0;

    PS = 1; // interrupt priority
    ES = 1; // enable serial interrupt
    EA = 1;

    while (true) {
        while (rx_tail != rx_head) {
            uint8_t ch = rx_buf[rx_tail];

            rx_tail = (rx_tail + 1) & (RX_BUF_SIZE - 1);
            LCD_data(ch);
            cursor++;
            if (cursor == 17) {
                LCD_command(0xC0); // go first column
                cursor = 1;
                Beep();
            }
        }

        switch (Key_input()) { // key input
        case 0x1C:
            DIG_SELECT = 0x01;
            TXD_string("KEY1 was pressed.");
            TXD_char(0x0D);
            TXD_char(0x0A);
            break;
        case 0x1A:
            DIG_SELECT = 0x02;
            TXD_string("KEY2 was pressed.");
            TXD_char(0x0D);
            TXD_char(0x0A);
            break;
        case 0x16:
            DIG_SELECT = 0x04;
            TXD_string("KEY3 was pressed.");
            TXD_char(0x0D);
            TXD_char(0x0A);
            break;
        case 0x0E:
            DIG_SELECT = 0x08;
            TXD_string("KEY4 was pressed.");
            TXD_char(0x0D);
            TXD_char(0x0A);
            break;
        default:
            break;
        }
    }
}
