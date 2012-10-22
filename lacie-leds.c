#include "lacie-leds.h"

int main(int argc, char *argv[]) {
    uint8_t val = 0x00;
    uint8_t led = 0x00;
    uint8_t mode = 0x00;

    // Check for root access.
    if(iopl(3) < 0) {
        printf("lacie-leds must be run as root.\n");
        exit(1);
    }

    // Check argument count.
    if(argc != 3) {
        printf("Incorrect argument count. ");
        print_usage();
        exit(1);
    }

    // Get LED argument.
    if(strncmp("front", argv[1], 16) == 0) {
        led = FRONT_LED_ADDR;
        printf("front");
    } else if(strncmp("front-brightness", argv[1], 16) == 0) {
        led = FRONT_BRIGHTNESS_ADDR;
    } else if(strncmp("hdd-brightness", argv[1], 14) == 0) {
        led = HDD_BRIGHTNESS_ADDR;
    } else if(strncmp("hdd1", argv[1], 4) == 0) {
        led = HDD1_LED_ADDR;
    } else if(strncmp("hdd2", argv[1], 4) == 0) {
        led = HDD2_LED_ADDR;
    } else if(strncmp("hdd3", argv[1], 4) == 0) {
        led = HDD3_LED_ADDR;
    } else if(strncmp("hdd4", argv[1], 4) == 0) {
        led = HDD4_LED_ADDR;
    } else if(strncmp("hdd5", argv[1], 4) == 0) {
        led = HDD5_LED_ADDR;
    } else {
        printf("Incorrect led argument");
        print_usage();
        exit(1);
    }

    // Get mode argument.
    if(strncmp("off", argv[2], 3) == 0 || argv[2][0] == '0') {
        mode = OFF_LED_MODE;
    } else if(strncmp("blue", argv[2], 21) == 0 || argv[2][0] == '1') {
        mode = BLUE_LED_MODE;
    } else if(strncmp("red", argv[2], 21) == 0 || argv[2][0] == '2') {
        mode = RED_LED_MODE;
    } else if(strncmp("blue-blink-even", argv[2], 21) == 0 || argv[2][0] == '3') {
        mode = BLUE_BLINK_EVEN_LED_MODE;
    } else if(strncmp("red-blink-even", argv[2], 21) == 0 || argv[2][0] == '4') {
        mode = RED_BLINK_EVEN_LED_MODE;
    } else if(strncmp("blue-red-blink-uneven", argv[2], 21) == 0 || argv[2][0] == '5') {
        mode = BLUE_RED_BLINK_UNEVEN_LED_MODE;
    } else if(strncmp("blue-red-blink-even", argv[2], 21) == 0 || argv[2][0] == '6') {
        mode = BLUE_RED_BLINK_EVEN_LED_MODE;
    } else if(strncmp("blue-blink-uneven", argv[2], 21) == 0 || argv[2][0] == '7') {
        mode = BLUE_BLINK_UNEVEN_LED_MODE;
    } else {
        printf("Incorrect mode argument");
        print_usage();
        exit(1);
    }

    // Build value
    val = led | mode;

    // Enter conf mode.
    enter_conf_mode();

    // Select GPIO logical device.
    select_gpio_ldn();

    // Clear GPIO value.
    reg_write(LED_GPIO_DATA_REG, CLEAR_VAL);

    // Write data value.
    reg_write(LED_GPIO_DATA_REG, val);

    // Write enable bit.
    reg_write(LED_GPIO_DATA_REG, val | ENABLE_BIT_VAL);

    // Clear GPIO value.
    reg_write(LED_GPIO_DATA_REG, CLEAR_VAL);

    // Exit conf mode.
    exit_conf_mode();
}

void enter_conf_mode() {
    outb(ENTER_CONF_MODE, PORT);
    outb(ENTER_CONF_MODE, PORT);
}

void exit_conf_mode() {
    outb(EXIT_CONF_MODE, PORT);
}

uint8_t reg_read(uint8_t reg) {
    outb(reg, PORT);
    return inb(PORT + 1);
}

void reg_write(uint8_t reg, uint8_t val) {
    outb(reg, PORT);
    outb(val, PORT + 1);
}

void select_gpio_ldn() {
    reg_write(LDN_SEL_REG, GPIO_LDN);
}

void print_usage() {
    printf("Usage: leds <led> <mode>\n");
    printf("Possible <led> values: front, hdd1, hdd2, hdd3, hdd4, hdd5\n");
    printf("Possible <mode> values: 0-7, off, blue, red, blue-blink-even, red-blink-even, blue-red-blink-uneven, blue-red-blink-even, blue-blink-uneven\n");
}
