/*
 * Pin definitions for LILYGO® TTGO LoRa32 V2.1_1.6
 * This file cannot be used with other boards even if are similar
 * By Giovanni Bernardo (https://www.settorezero.com)
 * Read the full article here:
 * https://www.settorezero.com/wordpress/lilygo_ttgo_lora32_esp32_point_to_point
 * if you want to share the code please mention: Giovanni Bernardo of settorezero.com
 */

// LoRa Chip, we'll use the LoRa on the VSPI module (SPI3)
// since the VSPI is normally tied to pins 5, 18, 19 and 23
// even if we'll re-arrange them
#define LORA_SCK      5   // 5
#define LORA_MISO     19  // 19
#define LORA_MOSI     27  // 27
#define LORA_SS       18  // 18
#define LORA_RST      23  // 14
#define LORA_DI0      26  // LORA_IRQ 26

//  set your frequency  from 868E6 to 868.6E6
//  Pay attention: don't set 868.0 but 868
#define LORA_BAND     868E6  // Values: 433E6, 866E6, 915E6 => Check you country, module and Antenna!


// LILYGO® TTGO LoRa32 V2.1_1.6
/*
// OLED Display (SSD1306 128x64)
#define OLED_SDA      21   // 4
#define OLED_SCL      22   // 15
#define OLED_RST      -1
#define OLED_ADDRESS  0x3C
#define LED           25 // the green led near the on/off button  // 2
#define VBAT          35 // Analog Input from 1:2 voltage divider on LiPo Battery
*/

// SCheda TTGO LoRa32 SX1276 con OLED
#define OLED_SDA      4   // 
#define OLED_SCL      15   //
#define OLED_RST      16  //16 ?
#define OLED_ADDRESS  0x3C
#define LED           2 // the green led near the on/off button  // 2
#define VBAT          35 // Analog Input from 1:2 voltage divider on LiPo Battery

// Others
