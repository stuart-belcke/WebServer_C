/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"

#define LED_DELAY_MS 500
#define BUTTON_PIN 14
#define PICO_DEFAULT_LED_PIN 15

int pico_switch_init(void) {
    // Initialize GPIO
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);  // Set as INPUT
    gpio_pull_up(BUTTON_PIN);           // Enable internal pull-up resistor
    return PICO_OK;
}

// Perform initialisation
int pico_led_init(void) {
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
}

// Turn the led on or off
void pico_set_led(bool led_on) {
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
}

int main() {
    stdio_init_all();  // Initialize USB Serial Communication
    sleep_ms(2000);    // Delay to allow the USB connection to initialize

    int rc_switch = pico_switch_init();
    hard_assert(rc_switch == PICO_OK);

    int rc_led = pico_led_init();
    hard_assert(rc_led == PICO_OK);

    while (true) {
        if (gpio_get(BUTTON_PIN) == 0) {
            pico_set_led(true);
            printf("Hello, World!\n");
            // sleep_ms(LED_DELAY_MS);
        } else {
            pico_set_led(false);
            printf("Goodbye, World!\n");
            // sleep_ms(LED_DELAY_MS);
        }
        printf("Another day goes by.\n");

        sleep_ms(LED_DELAY_MS);
    }
}

// /**
//  * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
//  *
//  * SPDX-License-Identifier: BSD-3-Clause
//  */

// #include "pico/stdlib.h"

// // Pico W devices use a GPIO on the WIFI chip for the LED,
// // so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
// #ifdef CYW43_WL_GPIO_LED_PIN
// #include "pico/cyw43_arch.h"
// #endif

// #ifndef LED_DELAY_MS
// #define LED_DELAY_MS 100
// #endif

// // Perform initialisation
// int pico_led_init(void) {
// #if defined(PICO_DEFAULT_LED_PIN)
//     // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
//     // so we can use normal GPIO functionality to turn the led on and off
//     gpio_init(PICO_DEFAULT_LED_PIN);
//     gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
//     return PICO_OK;
// #elif defined(CYW43_WL_GPIO_LED_PIN)
//     // For Pico W devices we need to initialise the driver etc
//     return cyw43_arch_init();
// #endif
// }

// // Turn the led on or off
// void pico_set_led(bool led_on) {
// #if defined(PICO_DEFAULT_LED_PIN)
//     // Just set the GPIO on or off
//     gpio_put(PICO_DEFAULT_LED_PIN, led_on);
// #elif defined(CYW43_WL_GPIO_LED_PIN)
//     // Ask the wifi "driver" to set the GPIO on or off
//     cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
// #endif
// }

// int main() {
//     int rc = pico_led_init();
//     hard_assert(rc == PICO_OK);
//     while (true) {
//         pico_set_led(true);
//         sleep_ms(LED_DELAY_MS);
//         pico_set_led(false);
//         sleep_ms(LED_DELAY_MS);
//     }
// }
