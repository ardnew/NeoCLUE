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

#define __PIN_5V_LOGIC_LEVEL__         5 // special 5V level-shifted GPIO pin

#define __PIN_QSPI_FLASH_SCK__         PIN_QSPI_SCK      // 26
#define __PIN_QSPI_FLASH_CS__          PIN_QSPI_CS       // 27
#define __PIN_QSPI_FLASH_IO0__         PIN_QSPI_IO0      // 28
#define __PIN_QSPI_FLASH_IO1__         PIN_QSPI_IO1      // 29
#define __PIN_QSPI_FLASH_IO2__         PIN_QSPI_IO2      // 30
#define __PIN_QSPI_FLASH_IO3__         PIN_QSPI_IO3      // 31

//
// ============================================================
//        WS2815 RGB 5050 LED (300LED/5m => 60LED/m)
// ------------------------------------------------------------
//

#define __NEOPIXEL_LENGTH_PX__         30
#define __NEOPIXEL_TYPE__              NEO_KHZ800 // in Adafruit_NeoPixel.h
#define __NEOPIXEL_ORDER__             NEO_GRB    //
#define __NEOPIXEL_DATA_PIN__          __PIN_5V_LOGIC_LEVEL__

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
#define __BLUETOOTH_CHAR_LEN_MAX__     20 // max size of characteristic
#define __BLUETOOTH_DEVICE_MFG__      "Adafruit Industries"
#define __BLUETOOTH_DEVICE_MODEL__    "ItsyBitsy nRF52840"

// convert 128-bit UUID to uint8_t[16] literal:
//   $ perl -le 'print join ", ", map { "0x$_" } reverse((shift) =~ /([a-f0-9]{2})/ig)' 3f1d00c0-632f-4e53-9a14-437dd54bcccc
//   0xcc, 0xcc, 0x4b, 0xd5, 0x7d, 0x43, 0x14, 0x9a, 0x53, 0x4e, 0x2f, 0x63, 0xc0, 0x00, 0x1d, 0x3f

#define _neoclue_service_uuid128(id)                                           \
    { 0xCC, 0xCC, 0x4B, 0xD5, 0x7D, 0x43, 0x14, 0x9A,                          \
      0x53, 0x4E, 0x2F, 0x63, (id), 0x00, 0x1D, 0x3F }

#define __NEOCLUE_SERVICE_UUID128__            _neoclue_service_uuid128(0xC0) // 3f1d00c0-632f-4e53-9a14-437dd54bcccc
#define __NEOCLUE_SERVICE_STRIP_CHAR_UUID128__ _neoclue_service_uuid128(0xC1) // 3f1d00c1-632f-4e53-9a14-437dd54bcccc
#define __NEOCLUE_SERVICE_FILL_CHAR_UUID128__  _neoclue_service_uuid128(0xC2) // 3f1d00c2-632f-4e53-9a14-437dd54bcccc

//                                           128-bit / 8-bit == 16 bytes
#define __UUID128_SIZE__                       ( 128 / 8 )

extern const uint8_t NEOCLUE_SERVICE_UUID128[__UUID128_SIZE__];
extern const uint8_t NEOCLUE_SERVICE_STRIP_CHAR_UUID128[__UUID128_SIZE__];
extern const uint8_t NEOCLUE_SERVICE_FILL_CHAR_UUID128[__UUID128_SIZE__];

#endif // __PERIPH_H__
