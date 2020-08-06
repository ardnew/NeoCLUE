#ifndef __PERIPH_H__
#define __PERIPH_H__

//
// ============================================================
//               Adafruit CLUE (nRF52840) Pinout
// ------------------------------------------------------------
//  Peripheral                         Variant           Pin
// --------------------------------   ---------------   -------
//

#define __PIN_LED_RED_BACK__           PIN_LED1          // 17
#define __PIN_LED_WHITE_FRONT__        PIN_LED2          // 43
#define __PIN_LED_NEOPIXEL_BACK__      PIN_NEOPIXEL      // 18

#define __PIN_BUTTON_LEFT__            PIN_BUTTON1       // 5
#define __PIN_BUTTON_RIGHT__           PIN_BUTTON2       // 11

#define __PIN_I2C_ACCEL_GYRO_SDA__     PIN_WIRE_SDA      // 20
#define __PIN_I2C_ACCEL_GYRO_SCL__     PIN_WIRE_SCL      // 19

#define __PIN_I2C_MAGNETO_SDA__        PIN_WIRE_SDA      // 20
#define __PIN_I2C_MAGNETO_SCL__        PIN_WIRE_SCL      // 19

#define __PIN_I2C_LIGHT_PROXY_SDA__    PIN_WIRE_SDA      // 20
#define __PIN_I2C_LIGHT_PROXY_SCL__    PIN_WIRE_SCL      // 19

#define __PIN_I2C_HUMIDITY_SDA__       PIN_WIRE_SDA      // 20
#define __PIN_I2C_HUMIDITY_SCL__       PIN_WIRE_SCL      // 19

#define __PIN_I2C_TEMP_ATMO_SDA__      PIN_WIRE_SDA      // 20
#define __PIN_I2C_TEMP_ATMO_SCL__      PIN_WIRE_SCL      // 19

#define __PIN_PDM_MIC_DIN__            PIN_PDM_DIN       // 35
#define __PIN_PDM_MIC_CLK__            PIN_PDM_CLK       // 36

#define __PIN_SPEAKER__                PIN_BUZZER        // 46

#define __PIN_IPS_LCD_MISO__           PIN_SPI1_MISO     // 35
#define __PIN_IPS_LCD_MOSI__           PIN_SPI1_MOSI     // 30
#define __PIN_IPS_LCD_SCK__            PIN_SPI1_SCK      // 29
#define __PIN_IPS_LCD_CS__             PIN_TFT_CS        // 31
#define __PIN_IPS_LCD_DC__             PIN_TFT_DC        // 32
#define __PIN_IPS_LCD_RST__            PIN_TFT_RST       // 33
#define __PIN_IPS_LCD_LITE__           PIN_TFT_LITE      // 34

#define __PIN_QSPI_FLASH_SCK__         PIN_QSPI_SCK      // 37
#define __PIN_QSPI_FLASH_CS__          PIN_QSPI_CS       // 38
#define __PIN_QSPI_FLASH_IO0__         PIN_QSPI_IO0      // 39
#define __PIN_QSPI_FLASH_IO1__         PIN_QSPI_IO1      // 40
#define __PIN_QSPI_FLASH_IO2__         PIN_QSPI_IO2      // 41
#define __PIN_QSPI_FLASH_IO3__         PIN_QSPI_IO3      // 42

//
// ============================================================
//               Adafruit CLUE (nRF52840) IPS LCD
// ------------------------------------------------------------
//

// LCD connected to the one and only SPIM3 (32MHz) on nRF52840.
// ST7789, IPS, 1.3" (diag), 240x240, 260ppi, 16-bit RGB565
#define __IPS_LCD_WIDTH__              240
#define __IPS_LCD_HEIGHT__             240
#define __IPS_LCD_ROTATE__             1
#define __IPS_LCD_SPI__                SPI1

#define _enable_backlight(enable)                             \
  pinMode(__PIN_IPS_LCD_LITE__, OUTPUT);                      \
  digitalWrite(__PIN_IPS_LCD_LITE__, (enable) ? HIGH : LOW);

//
// ============================================================
//           Adafruit CLUE (nRF52840) Bluetooth (LE)
// ------------------------------------------------------------
//

// nRF52840 supported Tx power settings (dBm):
//   -40 -20 -16 -12 -8 -4 0 +2 +3 +4 +5 +6 +7 +8
#define __BLUETOOTH_TX_POWER__         4
#define __BLUETOOTH_CONN_MAX__         1
#define __BLUETOOTH_LED_INTERVAL__     250
#define __BLUETOOTH_RSSI_MIN__         -80

#endif // __PERIPH_H__
