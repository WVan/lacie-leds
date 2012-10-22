#ifndef LEDS_H
#define LEDS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/io.h>

#define PORT 0x4e
#define LDN_SEL_REG 0x07
#define GPIO_LDN 0x06
#define LED_GPIO_DATA_REG 0xf1
#define CLEAR_VAL 0x00
#define ENABLE_BIT_VAL 0x80
#define ENTER_CONF_MODE 0x87
#define EXIT_CONF_MODE 0xaa

/*
 * The LEDs are controlled by a CPLD and can be configured through a GPIO
 * extension bus, notice that the data and address value bits should be
 * written in inverted order:
 *
 * - address register : bit [0-2] -> GPIO [2-0] 
 * - data register    : bit [0-2] -> GPIO [5-3]
 * - enable register  : GPIO 7
 *
 *    0 0 0 0 0 0 0 0
 *    e 0 | d | | a |
 *
 * Address register selection:
 *
 * addr | register
 * ----------------------------
 *   0  | front LED
 *   1  | front LED brightness
 *   2  | HDD LED brightness
 *   3  | HDD1 LED
 *   4  | HDD2 LED
 *   5  | HDD3 LED
 *   6  | HDD4 LED
 *   7  | HDD5 LED
 *
 * Data register configuration:
 *
 * data | LED brightness
 * -------------------------------------------------
 *   0  | min (off)
 *   -  | -
 *   7  | max
 *
 * data | front and HDD LED mode
 * -------------------------------------------------
 *   0  | fix off
 *   1  | fix blue on
 *   2  | fix red on
 *   3  | blink blue on=1 sec and blue off=1 sec
 *   4  | blink red on=1 sec and red off=1 sec
 *   5  | blink blue on=2.5 sec and red on=0.5 sec
 *   6  | blink blue on=1 sec and red on=1 sec
 *   7  | blink blue on=0.5 sec and blue off=2.5 sec
 */

#define FRONT_LED_ADDR 0x00 // 0 0 000 000
#define FRONT_BRIGHTNESS_ADDR 0x04 // 0 0 000 100
#define HDD_BRIGHTNESS_ADDR 0x02 // 0 0 000 010
#define HDD1_LED_ADDR 0x06 // 0 0 000 110
#define HDD2_LED_ADDR 0x01 // 0 0 000 001
#define HDD3_LED_ADDR 0x05 // 0 0 000 101
#define HDD4_LED_ADDR 0x03 // 0 0 000 011
#define HDD5_LED_ADDR 0x07 // 0 0 000 111

#define OFF_LED_MODE 0x00 // 0 0 000 000
#define BLUE_LED_MODE 0x20 // 0 0 100 000
#define RED_LED_MODE 0x10 // 0 0 010 000
#define BLUE_BLINK_EVEN_LED_MODE 0x30 // 0 0 110 000
#define RED_BLINK_EVEN_LED_MODE 0x08 // 0 0 001 000
#define BLUE_RED_BLINK_UNEVEN_LED_MODE 0x28 // 0 0 101 000
#define BLUE_RED_BLINK_EVEN_LED_MODE 0x18 // 0 0 011 000
#define BLUE_BLINK_UNEVEN_LED_MODE 0x38 // 0 0 111 000

void enter_conf_mode();
void exit_conf_mode();

uint8_t reg_read(uint8_t reg);
void reg_write(uint8_t reg, uint8_t val);

void select_gpio_ldn();

void print_usage();

#endif /* LEDS_H */
