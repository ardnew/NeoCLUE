#ifndef __PERIPH_H__
#define __PERIPH_H__

//
// ============================================================
//            Adafruit ItsyBitsy (nRF52840) Pinout
// ------------------------------------------------------------
//  Peripheral                         Variant           Pin
// --------------------------------   ---------------   -------
//

#define __PIN_LED_RED__                PIN_LED1          // 3
#define __PIN_LED_DOTSTAR_DATA__       PIN_DOTSTAR_DATA  // 8
#define __PIN_LED_DOTSTAR_CLOCK__      PIN_DOTSTAR_CLOCK // 6

#define __PIN_BUTTON__                 PIN_BUTTON1       // 4

#define __PIN_5V_OUT_NEOPIXEL__        5 // special 5V level-shifted GPIO pin

#define __PIN_QSPI_FLASH_SCK__         PIN_QSPI_SCK      // 26
#define __PIN_QSPI_FLASH_CS__          PIN_QSPI_CS       // 27
#define __PIN_QSPI_FLASH_IO0__         PIN_QSPI_IO0      // 28
#define __PIN_QSPI_FLASH_IO1__         PIN_QSPI_IO1      // 29
#define __PIN_QSPI_FLASH_IO2__         PIN_QSPI_IO2      // 30
#define __PIN_QSPI_FLASH_IO3__         PIN_QSPI_IO3      // 31

//
// ============================================================
//         WS2815 RGB 5050 LED (300LED/5m => 60LED/m)
// ------------------------------------------------------------
//

#define __NEOPIXEL_LENGTH_PX__         300
#define __NEOPIXEL_TYPE__              NEO_KHZ800 // in Adafruit_NeoPixel.h
#define __NEOPIXEL_ORDER__             NEO_GRB    //

//
// ============================================================
//         Adafruit ItsyBitsy (nRF52840) Bluetooth (LE)
// ------------------------------------------------------------
//

// nRF52840 supported Tx power settings (dBm):
//   -40 -20 -16 -12 -8 -4 0 +2 +3 +4 +5 +6 +7 +8
#define __BLUETOOTH_TX_POWER__         4
#define __BLUETOOTH_CONN_MAX__         1
#define __BLUETOOTH_LED_INTERVAL__     250
#define __BLUETOOTH_RSSI_MIN__         -80

#endif // __PERIPH_H__
