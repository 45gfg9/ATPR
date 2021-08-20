#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <ATPR.h>

void usbReset() {
  USBDDR |= USBMASK;
  _delay_ms(10);
  USBDDR = 0;
}

int main() {
  wdt_enable(WDTO_1S);

  usbReset();

  usbInit();
  sei();

  while (true) {
    wdt_reset();
    usbPoll();
  }

  return 0;
}

usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
  (void)(usbRequest_t *) data;

  return USB_NO_MSG;
}
