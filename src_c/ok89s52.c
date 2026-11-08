/*   ok89s52.c : Designed by Duck-Yong Yoon in 2005.                          */

#include <math.h>
#include <stdbool.h>

#include <ok89s52.h>

/* -------------------------------------------------------------------------- */
/*   OK-89S52 Kit User-defined Function                                       */
/* -------------------------------------------------------------------------- */

void Kit_initialize(void) /* initialize OK-89S52 kit */
{
    P3_5 = 1;           // buzzer off
    SEG_PATTERN = 0x00; // clear 7-segment LED
    DIG_SELECT = 0x00;
}

void Delay_us(uint8_t us) /* time delay for us[us] at 24MHz */
{
    uint8_t i;

    if (us < 8) {
        return;
    }

    i = (uint8_t)(us - 6U) >> 1;
    do {
        __asm__("nop");
        __asm__("nop");
    } while (--i);
}

void Delay_ms(uint16_t ms) /* time delay for ms[ms] at 24MHz */
{
    uint8_t i;

    while (ms--) {
        i = 248;
        do {
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
        } while (--i);
    }
}

void Beep(void) /* beep sound for 50 ms */
{
    P3_5 = 0;
    Delay_ms(50);
    P3_5 = 1;
}

uint8_t Key_input(void) /* input key switch KEY4 - KEY1 */
{
    static bool key_flag = false;
    uint8_t key;

    key = P1 & 0x1E;   // any key pressed ?
    if (key == 0x1E) { // if no key, check key off
        if (!key_flag) {
            Delay_ms(20);
            key_flag = 0;
        }

        return key;
    }

    if (key_flag) { // if continuous key, treat as no key input
        return 0x1E;
    }

    Beep(); // if new key, beep and delay for debounce
    key_flag = true;

    return key;
}

void LCD_command(uint8_t command) /* write a command on text LCD */
{
    LCD_WR_INST = command;
    Delay_us(50);
}

void LCD_data(uint8_t character) /* display a character on text LCD */
{
    LCD_WR_DATA = character;
    Delay_us(50);
}

void LCD_string(uint8_t command,
                const char *string) /* display a string on text LCD */
{
    LCD_command(command);
    while (*string != '\0') {
        LCD_data((uint8_t)*string);
        string++;
    }
}

void LCD_initialize(void) /* initialize text LCD module */
{
    LCD_command(0x38); // function set(8 bit, 2 line, 5x7 dot)
    LCD_command(0x0C); // display control(display ON, cursor OFF)
    LCD_command(0x06); // entry mode set(increment, not shift)
    LCD_command(0x01); // clear display
    Delay_ms(2);
}

void LCD_2dec(uint8_t number) /* display 2-digit decimal number */
{
    uint8_t i;

    i = number / 10; // 10^1
    if (i == 0) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
    }

    LCD_data((number % 10) + '0'); // 10^0
}

void LCD_3dec(uint16_t number) /* display 3-digit decimal number */
{
    uint8_t i, flag;

    flag = 0;
    i = number / 100; // 10^2
    if (i == 0) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
        flag = 1;
    }

    number %= 100; // 10^1
    i = number / 10;
    if ((i == 0) && (flag == 0)) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
    }

    LCD_data((number % 10) + '0'); // 10^0
}

void LCD_4dec(uint16_t number) /* display 4-digit decimal number */
{
    uint16_t i;
    bool flag = false;

    i = number / 1000; // 10^3
    if (i == 0) {
        LCD_data(' ');
    } else {
        LCD_data((uint8_t)(i + '0'));
        flag = true;
    }

    number = number % 1000; // 10^2
    i = number / 100;
    if ((i == 0) && !flag) {
        LCD_data(' ');
    } else {
        LCD_data((uint8_t)(i + '0'));
        flag = true;
    }

    number = number % 100; // 10^1
    i = number / 10;
    if ((i == 0) && !flag) {
        LCD_data(' ');
    } else {
        LCD_data((uint8_t)(i + '0'));
    }

    i = number % 10; // 10^0
    LCD_data((uint8_t)(i + '0'));
}

void LCD_5dec(uint16_t number) /* display 5-digit decimal number */
{
    uint8_t i, flag;

    flag = 0;
    i = number / 10000; // 10^4
    if (i == 0) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
        flag = 1;
    }

    number %= 10000; // 10^3
    i = number / 1000;
    if ((i == 0) && (flag == 0)) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
        flag = 1;
    }

    number %= 1000; // 10^2
    i = number / 100;
    if ((i == 0) && (flag == 0)) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
        flag = 1;
    }

    number %= 100; // 10^1
    i = number / 10;
    if ((i == 0) && (flag == 0)) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
    }

    LCD_data((number % 10) + '0'); // 10^0
}

void LCD_s3dec(int16_t number) /* display signed 3-digit decimal number +xxx */
{
    uint16_t mag;

    if (number >= 0) {
        LCD_data('+');
        mag = (uint16_t)number;
    } else {
        LCD_data('-');
        mag = 0U - (uint16_t)number;
    }

    LCD_3dec(mag);
}

void LCD_02dec(uint8_t number) /* display zero-padded 2-digit number */
{
    LCD_data((number / 10) + '0'); // 10^1
    LCD_data((number % 10) + '0'); // 10^0
}

void LCD_03dec(uint8_t number) /* display 3-digit decimal number */
{
    uint8_t rem;

    LCD_data(number / 100 + '0'); // 10^2
    rem = number % 100;
    LCD_data(rem / 10 + '0'); // 10^1
    LCD_data(rem % 10 + '0'); // 10^0
}

void LCD_02hex(uint8_t number) /* display 2-digit hex number */
{
    uint8_t i;

    i = (number >> 4) & 0x0F; // 16^1
    LCD_data((i <= 9) ? (i + '0') : (i - 10 + 'A'));

    i = number & 0x0F; // 16^0
    LCD_data((i <= 9) ? (i + '0') : (i - 10 + 'A'));
}

void LCD_04hex(uint16_t number) /* display 4-digit hex number */
{
    LCD_02hex((uint8_t)(number >> 8));
    LCD_02hex((uint8_t)(number & 0xFF));
}

void LCD_08bin(uint8_t number) /* display 8-bit binary number */
{
    uint8_t mask;

    for (mask = 0x80; mask != 0; mask >>= 1) {
        LCD_data((number & mask) ? '1' : '0');
    }
}

void LCD_1dec1(float number) /* display real number x.x */
{
    uint16_t j;

    j = (uint16_t)(number * 10.0f + 0.5f);
    LCD_data((j / 10) + '0'); // 10^0
    LCD_data('.');
    LCD_data((j % 10) + '0'); // 10^-1
}

void LCD_1dec2(float number) /* display real number x.xx */
{
    uint16_t j;

    j = (uint16_t)(number * 100.0f + 0.5f);
    LCD_data((j / 100) + '0'); // 10^0
    LCD_data('.');
    LCD_02dec((uint8_t)(j % 100)); // 10^-1..10^-2
}

void LCD_1dec3(float number) /* display real number x.xxx */
{
    uint16_t j;

    j = (uint16_t)(number * 1000.0f + 0.5f);
    LCD_data((j / 1000) + '0'); // 10^0
    LCD_data('.');
    j %= 1000;
    LCD_data((j / 100) + '0');     // 10^-1
    LCD_02dec((uint8_t)(j % 100)); // 10^-2..10^-3
}

void LCD_2dec0(float number) /* display real number xx. */
{
    LCD_2dec((uint8_t)number);
    LCD_data('.');
}

void LCD_2dec1(float number) /* display real number xx.x */
{
    uint16_t j;

    j = (uint16_t)(number * 10.0f + 0.5f);
    LCD_2dec((uint8_t)(j / 10)); // 10^1..10^0
    LCD_data('.');
    LCD_data((j % 10) + '0'); // 10^-1
}

void LCD_2dec2(float number) /* display real number xx.xx */
{
    uint16_t j;

    j = (uint16_t)(number * 100.0f + 0.5f);
    LCD_2dec((uint8_t)(j / 100)); // 10^1..10^0
    LCD_data('.');
    LCD_02dec((uint8_t)(j % 100)); // 10^-1..10^-2
}

void LCD_s1dec2(float number) /* floating-point number +/-x.xx */
{
    uint16_t i, j;

    if (number >= 0.0f) {
        LCD_data('+'); // sign +/-
    } else {
        LCD_data('-');
    }

    j = (uint16_t)(fabsf(number) * 100.0f + 0.5f);
    i = j / 100; // 10^0
    LCD_data((uint8_t)(i + '0'));
    LCD_data('.');

    j = j % 100; // 10^-1
    i = j / 10;
    LCD_data((uint8_t)(i + '0'));

    i = j % 10; // 10^-2
    LCD_data((uint8_t)(i + '0'));
}

void LCD_s1dec3(float number) /* display signed real number +x.xxx */
{
    if (number >= 0.0f) {
        LCD_data('+');
    } else {
        LCD_data('-');
        number = -number;
    }

    LCD_1dec3(number);
}

void LCD_s2dec1(uint8_t number) /* display signed real number +xx.x */
{
    if (number >= 0x80) { // positive
        number = number - 0x80;
        LCD_data('+');
    } else { // negative
        number = 0x80 - number;
        LCD_data('-');
    }

    LCD_2dec1((float)number * 10.0f / 128.0f);
}

void LCD_2BCD(uint8_t number) /* display 2-digit BCD number */
{
    LCD_data(((number >> 4) & 0x0F) + '0'); // 10^1
    LCD_data((number & 0x0F) + '0');        // 10^0
}

uint8_t BCD_increment(uint8_t number) /* BCD increment */
{
    uint8_t i;

    i = (number >> 4) * 10 + (number & 0x0F) + 1;

    return ((i / 10) << 4) | (i % 10);
}

uint8_t BCD_decrement(uint8_t number) /* BCD decrement */
{
    uint8_t i;

    i = (number >> 4) * 10 + (number & 0x0F) - 1;

    return ((i / 10) << 4) | (i % 10);
}

uint8_t Bin2LED(uint8_t number) /* convert binary to LED pattern */
{
    static const uint8_t __code led_table[16] = {
        0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4,
        0xFE, 0xF6, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E,
    };

    if (number < 16) {
        return led_table[number];
    } else if (number == 'H') {
        return 0x6E;
    } else if (number == '-') {
        return 0x02;
    } else if (number == '.') {
        return 0x01;
    } else if (number == 0x27) {
        return 0x40;
    }

    return 0x00;
}
