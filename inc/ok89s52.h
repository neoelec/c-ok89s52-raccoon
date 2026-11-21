/*   ok89s52.h : Designed by Duck-Yong Yoon in 2005.                          */

#ifndef OK89S52_H
#define OK89S52_H

#include <stdint.h>

#include <at89s52.h>

/* -------------------------------------------------------------------------- */
/*   OK-89S52 Kit I/O Address                                                 */
/* -------------------------------------------------------------------------- */

SFRX(RTC_SECOND, 0x8000); /* DS12C887 RTC */
SFRX(RTC_SEC_ALM, 0x8001);
SFRX(RTC_MINUTE, 0x8002);
SFRX(RTC_MIN_ALM, 0x8003);
SFRX(RTC_HOUR, 0x8004);
SFRX(RTC_HOUR_ALM, 0x8005);
SFRX(RTC_WEEKDAY, 0x8006);
SFRX(RTC_DATE, 0x8007);
SFRX(RTC_MONTH, 0x8008);
SFRX(RTC_YEAR, 0x8009);
SFRX(RTC_A, 0x800A);
SFRX(RTC_B, 0x800B);
SFRX(RTC_C, 0x800C);
SFRX(RTC_D, 0x800D);
SFRX(RTC_FLAG, 0x800F);

SFRX(SEG_PATTERN, 0x8100); /* segment pattern data */
SFRX(DIG_SELECT, 0x8200);  /* digit select data */

SFRX(LCD_WR_INST, 0x8300); /* LCD module */
SFRX(LCD_WR_DATA, 0x8301);

SFRX(ADC_CH0, 0x8400); /* select ADC0809 channel */
SFRX(ADC_CH1, 0x8401);
SFRX(ADC_CH2, 0x8402);
SFRX(ADC_CH3, 0x8403);
SFRX(ADC_CH4, 0x8404);
SFRX(ADC_CH5, 0x8405);
SFRX(ADC_CH6, 0x8406);
SFRX(ADC_CH7, 0x8407);
SFRX(ADC_READ, 0x8400); /* read ADC0809 */

SFRX(DAC_CS, 0x8500); /* output DAC0800 */

/* -------------------------------------------------------------------------- */
/*   OK-89S52 Kit User-defined Function                                       */
/* -------------------------------------------------------------------------- */

void Kit_initialize(void);
void Delay_us(uint8_t us);
void Delay_ms(uint16_t ms);
void Beep(void);
uint8_t Key_input(void);

void LCD_command(uint8_t command);
void LCD_data(uint8_t character);
void LCD_string(uint8_t command, const char *string);
void LCD_initialize(void);

void LCD_2dec(uint8_t number);
void LCD_3dec(uint16_t number);
void LCD_4dec(uint16_t number);
void LCD_5dec(uint16_t number);
void LCD_s3dec(int16_t number);
void LCD_02dec(uint8_t number);
void LCD_03dec(uint8_t number);
void LCD_02hex(uint8_t number);
void LCD_04hex(uint16_t number);
void LCD_08bin(uint8_t number);
void LCD_1dec1(float number);
void LCD_1dec2(float number);
void LCD_1dec3(float number);
void LCD_2dec0(float number);
void LCD_2dec1(float number);
void LCD_2dec2(float number);
void LCD_s1dec2(float number);
void LCD_s1dec3(float number);
void LCD_s2dec1(uint8_t number);
void LCD_2BCD(uint8_t number);
uint8_t BCD_increment(uint8_t number);
uint8_t BCD_decrement(uint8_t number);
uint8_t Bin2LED(uint8_t number);

#endif
