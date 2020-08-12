#ifndef __PERIPH_H__
#define __PERIPH_H__

//
// =============================================================================
//                       Adafruit CLUE (nRF52840) Pinout
// -----------------------------------------------------------------------------
//

// ----------------------------------------   ---------------   -------
//  Peripheral                                 Variant           Pin
// ----------------------------------------   ---------------   -------

#define __PIN_LED_RED_BACK__                   PIN_LED1          // 17
#define __PIN_LED_WHITE_FRONT__                PIN_LED2          // 43
#define __PIN_LED_NEOPIXEL_BACK__              PIN_NEOPIXEL      // 18

#define __PIN_BUTTON_LEFT__                    PIN_BUTTON1       // 5
#define __PIN_BUTTON_RIGHT__                   PIN_BUTTON2       // 11

#define __PIN_I2C_ACCEL_GYRO_SDA__             PIN_WIRE_SDA      // 20
#define __PIN_I2C_ACCEL_GYRO_SCL__             PIN_WIRE_SCL      // 19
#define __PIN_I2C_ACCEL_GYRO_INT__             45 // not named in BSP variant.h

#define __PIN_I2C_MAGNETO_SDA__                PIN_WIRE_SDA      // 20
#define __PIN_I2C_MAGNETO_SCL__                PIN_WIRE_SCL      // 19

#define __PIN_I2C_LIGHT_PROXY_SDA__            PIN_WIRE_SDA      // 20
#define __PIN_I2C_LIGHT_PROXY_SCL__            PIN_WIRE_SCL      // 19
#define __PIN_I2C_LIGHT_PROXY_INT__            44 // not named in BSP variant.h

#define __PIN_I2C_TEMP_HUMID_SDA__             PIN_WIRE_SDA      // 20
#define __PIN_I2C_TEMP_HUMID_SCL__             PIN_WIRE_SCL      // 19

#define __PIN_I2C_ATMOS_SDA__                  PIN_WIRE_SDA      // 20
#define __PIN_I2C_ATMOS_SCL__                  PIN_WIRE_SCL      // 19

#define __PIN_PDM_MIC_DIN__                    PIN_PDM_DIN       // 35
#define __PIN_PDM_MIC_CLK__                    PIN_PDM_CLK       // 36

#define __PIN_SPEAKER__                        PIN_BUZZER        // 46

#define __PIN_IPS_LCD_MISO__                   PIN_SPI1_MISO     // 35
#define __PIN_IPS_LCD_MOSI__                   PIN_SPI1_MOSI     // 30
#define __PIN_IPS_LCD_SCK__                    PIN_SPI1_SCK      // 29
#define __PIN_IPS_LCD_CS__                     PIN_TFT_CS        // 31
#define __PIN_IPS_LCD_DC__                     PIN_TFT_DC        // 32
#define __PIN_IPS_LCD_RST__                    PIN_TFT_RST       // 33
#define __PIN_IPS_LCD_LITE__                   PIN_TFT_LITE      // 34

#define __PIN_QSPI_FLASH_SCK__                 PIN_QSPI_SCK      // 37
#define __PIN_QSPI_FLASH_CS__                  PIN_QSPI_CS       // 38
#define __PIN_QSPI_FLASH_IO0__                 PIN_QSPI_IO0      // 39
#define __PIN_QSPI_FLASH_IO1__                 PIN_QSPI_IO1      // 40
#define __PIN_QSPI_FLASH_IO2__                 PIN_QSPI_IO2      // 41
#define __PIN_QSPI_FLASH_IO3__                 PIN_QSPI_IO3      // 42

//
// =============================================================================
//                       Adafruit CLUE (nRF52840) IPS LCD
// -----------------------------------------------------------------------------
//

// LCD connected to the one and only SPIM3 (32MHz) on nRF52840.
// ST7789, IPS, 1.3" (diag), 240x240, 260ppi, 16-bit RGB565
#define __IPS_LCD_WIDTH__                      240
#define __IPS_LCD_HEIGHT__                     240
#define __IPS_LCD_ROTATE__                     1
#define __IPS_LCD_SPI__                        (&SPI1)

#define _enable_backlight(enable)                                              \
    pinMode(__PIN_IPS_LCD_LITE__, OUTPUT);                                     \
    digitalWrite(__PIN_IPS_LCD_LITE__, (enable) ? HIGH : LOW);

//
// =============================================================================
//                    Adafruit CLUE (nRF52840) Bluetooth (LE)
// -----------------------------------------------------------------------------
//

// nRF52840 supported Tx power settings (dBm):
//   -40 -20 -16 -12 -8 -4 0 +2 +3 +4 +5 +6 +7 +8
#define __BLUETOOTH_TX_POWER__                 4
#define __BLUETOOTH_CONN_MAX__                 1
#define __BLUETOOTH_LED_INTERVAL__             250
#define __BLUETOOTH_SCAN_TIMEOUT__             0 // indefinite
#define __BLUETOOTH_RSSI_MIN__                 -80
#define __BLUETOOTH_NAME_STRLEN_MAX__          32
#define __BLUETOOTH_NO_CONN_HANDLE__           ~0U

// convert 128-bit UUID to uint8_t[16] literal:
//   $ perl -le 'print join ", ", map { "0x$_" } reverse((shift) =~ /([a-f0-9]{2})/ig)' 3f1d00c0-632f-4e53-9a14-437dd54bcccc
//   0xcc, 0xcc, 0x4b, 0xd5, 0x7d, 0x43, 0x14, 0x9a, 0x53, 0x4e, 0x2f, 0x63, 0xc0, 0x00, 0x1d, 0x3f

#define _neoclue_service_uuid128(id)                                           \
    { 0xCC, 0xCC, 0x4B, 0xD5, 0x7D, 0x43, 0x14, 0x9A,                          \
      0x53, 0x4E, 0x2F, 0x63, (id), 0x00, 0x1D, 0x3F }

#define __NEOCLUE_SERVICE_UUID128__            _neoclue_service_uuid128(0xC0) // 3f1d00c0-632f-4e53-9a14-437dd54bcccc
#define __NEOCLUE_SERVICE_STRIP_CHAR_UUID128__ _neoclue_service_uuid128(0xC1) // 3f1d00c1-632f-4e53-9a14-437dd54bcccc

//                                           128-bit / 8-bit == 16 bytes
#define __UUID128_SIZE__                       ( 128 / 8 )

extern uint8_t const NEOCLUE_SERVICE_UUID128[__UUID128_SIZE__];
extern uint8_t const NEOCLUE_SERVICE_STRIP_CHAR_UUID128[__UUID128_SIZE__];

//
// =============================================================================
//                  Adafruit CLUE (nRF52840) I2C Sensor Suite
// -----------------------------------------------------------------------------
//

#define __SENSORS_I2C__                        (&Wire)

#define __SENSORS_I2C_ADDR_ACCEL_GYRO__        0x6A
#define __SENSORS_I2C_ADDR_MAGNETO__           0x1C
#define __SENSORS_I2C_ADDR_LIGHT_PROXY__       0x39
#define __SENSORS_I2C_ADDR_TEMP_HUMID__        0x44
#define __SENSORS_I2C_ADDR_ATMOS__             0x77

// time (milliseconds) to wait between successive sensor readings
#define __SENSORS_REFRESH_ACCEL__              100
#define __SENSORS_REFRESH_GYRO__               100
#define __SENSORS_REFRESH_MAGNETO__            500
#define __SENSORS_REFRESH_COLOR__              1000
#define __SENSORS_REFRESH_GESTURE__            1000
#define __SENSORS_REFRESH_PROXIMITY__          1000
#define __SENSORS_REFRESH_TEMPERATURE__        1000
#define __SENSORS_REFRESH_HUMIDITY__           1000
#define __SENSORS_REFRESH_ATMOS__              1000

#endif // __PERIPH_H__
