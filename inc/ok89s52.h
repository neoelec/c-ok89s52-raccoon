/*   ok89s52.h : Designed by Duck-Yong Yoon in 2005.                          */

#ifndef OK89S52_H
#define OK89S52_H

#include <stdint.h>

#include <at89s52.h>

/* -------------------------------------------------------------------------- */
/*   OK-89S52 Kit I/O Address                                                 */
/* -------------------------------------------------------------------------- */

#define RTC_SECOND (*(volatile uint8_t __xdata *)0x8000) /* DS12C887 RTC */
#define RTC_SEC_ALM (*(volatile uint8_t __xdata *)0x8001)
#define RTC_MINUTE (*(volatile uint8_t __xdata *)0x8002)
#define RTC_MIN_ALM (*(volatile uint8_t __xdata *)0x8003)
#define RTC_HOUR (*(volatile uint8_t __xdata *)0x8004)
#define RTC_HOUR_ALM (*(volatile uint8_t __xdata *)0x8005)
#define RTC_WEEKDAY (*(volatile uint8_t __xdata *)0x8006)
#define RTC_DATE (*(volatile uint8_t __xdata *)0x8007)
#define RTC_MONTH (*(volatile uint8_t __xdata *)0x8008)
#define RTC_YEAR (*(volatile uint8_t __xdata *)0x8009)
#define RTC_A (*(volatile uint8_t __xdata *)0x800A)
#define RTC_B (*(volatile uint8_t __xdata *)0x800B)
#define RTC_C (*(volatile uint8_t __xdata *)0x800C)
#define RTC_D (*(volatile uint8_t __xdata *)0x800D)
#define RTC_FLAG (*(volatile uint8_t __xdata *)0x800F)

#define SEG_PATTERN \
    (*(volatile uint8_t __xdata *)0x8100) /* segment pattern data */
#define DIG_SELECT (*(volatile uint8_t __xdata *)0x8200) /* digit select data */

#define LCD_WR_INST (*(volatile uint8_t __xdata *)0x8300) /* LCD module */
#define LCD_WR_DATA (*(volatile uint8_t __xdata *)0x8301)

#define ADC_CH0 \
    (*(volatile uint8_t __xdata *)0x8400) /* select ADC0809 channel */
#define ADC_CH1 (*(volatile uint8_t __xdata *)0x8401)
#define ADC_CH2 (*(volatile uint8_t __xdata *)0x8402)
#define ADC_CH3 (*(volatile uint8_t __xdata *)0x8403)
#define ADC_CH4 (*(volatile uint8_t __xdata *)0x8404)
#define ADC_CH5 (*(volatile uint8_t __xdata *)0x8405)
#define ADC_CH6 (*(volatile uint8_t __xdata *)0x8406)
#define ADC_CH7 (*(volatile uint8_t __xdata *)0x8407)
#define ADC_READ (*(volatile uint8_t __xdata *)0x8400) /* read ADC0809 */

#define DAC_CS (*(volatile uint8_t __xdata *)0x8500) /* output DAC0800 */

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
