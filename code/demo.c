#include <stdio.h>
#include "pico/stdlib.h"
#include <stdlib.h>
#include "hardware/gpio.h"
#include "data_out.pio.h"

#define INPUT_PIN 12
#define OUT_START_PIN 0

// Define patterns, array of 1-byte integers
// Since there is only 8 leds, 1 byte is enough for storing all leds status,
// Ex: hex 0x2 is in binary 0b00000010
uint_least8_t patterns[] = {
  0x0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80,
  0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2,
  0x81, 0x42, 0x24, 0x18, 0x24, 0x42,
  0xAA, 0x55,
  0x0, 0xFF
};
// C does not support array of arrays, so we must manually keep track of each
// pattern length.
uint patternLengths[] = {9, 14, 6, 2, 2};
uint numOfPatterns = sizeof(patternLengths)/sizeof(uint);

uint curPatternIteration;
uint curPatternIndex;
uint curStartIndex;

/* Get the offset value that is needed to acces the correct pattern. */
uint get_start_index() {
  uint startIndex = 0;
  for (uint i = 0; i < curPatternIndex; i++) {
    startIndex += patternLengths[i];
  }
  return startIndex;
}

/* Define interupt call */
void inter_test(uint gpio, uint32_t events) {
  curPatternIndex = (curPatternIndex + 1) % numOfPatterns;
  curPatternIteration = 0;
  printf("Show pattern %d\n", curPatternIndex);
  curStartIndex = get_start_index();
}


int main() {
    stdio_init_all();
    // Setup a pio for data output
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &data_out_program);
    uint sm = pio_claim_unused_sm(pio, true);
    data_out_program_init(pio, sm, offset, OUT_START_PIN);

    // Set first pattern
    curStartIndex = 0;
    curPatternIndex = 0;
    curPatternIteration = 0;

    // Initialize button
    gpio_init(INPUT_PIN);
    gpio_pull_up(INPUT_PIN);
    gpio_set_irq_enabled_with_callback(INPUT_PIN, GPIO_IRQ_EDGE_FALL, true, &inter_test);

    sleep_ms(2000);
    printf("\n----New-run----\n");

    uint bin;

    // Main loop
    while (true) {
      bin = patterns[curStartIndex + curPatternIteration]; // Integer that in binary represents the led status
      pio_sm_put_blocking(pio, sm, bin);
      curPatternIteration = (curPatternIteration + 1) % patternLengths[curPatternIndex];
      sleep_ms(200);
    }
    return 0;
}
