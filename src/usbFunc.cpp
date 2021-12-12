#include <ATPR.h>

// see declarations for impl notes
usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
  // TODO
  (void)reinterpret_cast<usbRequest_t *>(data);

  odDebug(0x10, data, 8);

  // control-in:
  // have `usbMsgPtr` set: return size
  // usbFunctionRead(): return USB_NO_MSG
  //
  // control-out:
  // ignore incoming data: return 0
  // usbFunctionWrite(): return USB_NO_MSG
  return USB_NO_MSG;
}

uint8_t usbFunctionRead(uint8_t *data, uint8_t len) {
  // TODO
  (void)data;
  (void)len;

  odDebug(0x11, data, len);

  // return actual bytes written to `data`
  return 0;
}

uint8_t usbFunctionWrite(uint8_t *data, uint8_t len) {
  // TODO
  (void)data;
  (void)len;

  odDebug(0x12, data, len);

  // received entire payload: return 1
  // expect more data: return 0
  return 1;
}
