/*
 *    ESP2Ard.c :
 *
 *          ESP32 to Arduino serial port (UART) communication
 *
 *  A basic library for sending simple packets back and forth
 *
 * Packet format: (8-bit bytes)
 * [  0]   0xff      Start Flag 1
 * [  1]   0x00      Start Flag 2
 * [  2]   (byte)L   number of payload bytes
 * [  3]   ...       start of payload
 * [3+L]  cksum      Checksum of payload (%256)
 * [4+L]  '\n'       End of packet flag
 *
 * L = # of payload bytes
 *   (1 <= L <= 255)
 *
 * Packet total length:   ESP2Ard_OVERHEAD_BYTES + L bytes
 */

//  Debugging?
//#define ESP2Ard_DEBUG   1


/////////////////////////  Configuration Zone ///////////////////////////////////////////
//  ESP2Ard_DEBUG works only on Arduino for now
//#define ESP2Ard_DEBUG  // more verbose debugging output

////////////////////////////////////////////
//
//  What platform and IDE are we running on?
//    uncomment just one of these:

// #define ARDUINO_PLATFORM            // arduino HW on Arduino IDE
#define ESP32_IDF_PLATFORM        // ESP32 HW on IDF IDE
//#define ESP32_Arduino_PLATFORM    // ESP32 HW on Arduino IDE


//
//  All platforms:
//
//   Configure comm parameters which should be same on both ends
//
#define ESP32Ard_max_packet_size         50
#define ESP32Ard_timeout_delay_ms        50
#define ESP2Ard_BaudRate               9600
#define ESP2Ard_OVERHEAD_BYTES            5  //len(packet) - len(payload)
#define ESP2Ard_max_payload_size  ESP32Ard_max_packet_size -  ESP2Ard_OVERHEAD_BYTES

//
//  >>> ESP32, configure serial params here
//
#define ESP_PIN_RX             2
#define ESP_PIN_TX             3
#define ESP_UART_NUM    UART_NUM_2  //UART_NUM_2 from driver/uart.h

#ifdef ARDUINO_PLATFORM

//
//  >>>Arduino, configure serial params here:
//

//
//   Arduino pin setup
#define ARD_PIN_RX   2
#define ARD_PIN_TX   3

//  Serial port type
#define ARDUINO_SW_SERIAL
//#define ARDUINO_HW_SERIAL
#endif // ARDUINO_PLATFORM

/////////////////////////////////  End of Configuration Zone ////////////////////////////

////////////////////////////////////////////
//  types and function protos

#ifdef ESP32_IDF_PLATFORM
#include "esp_log.h"
#include "driver/uart.h"

#define ESP32_HW_SERIAL

#define TAG "ESP2Ard message:"  // used for logging

typedef   unsigned char  byte;  // used w/ arduino just in case

#endif  // ESP32_IDF_PLATFORM

//
// defines for all platforms and ports:
//

// Error codes
#define ESP32Ard_timeout_error           -1
#define ESP32Ard_bad_pkt_header          -2
#define ESP32Ard_packet_length_overrun   -3
#define ESP32Ard_packet_length_incorrect -4
#define ESP32Ard_payload_size_zero       -5
#define ESP32Ard_packet_cksum_error      -6

#define ESP32Ard_packet_check_OK          1

//
//   Our basic coms functions (all platforms)
//
void EA_log(const char* msg);
int  EA_available();
void EA_delay_ms(int dms);
char EA_read();
char EA_write_buffer(char buf[], int len);
int  EA_get_packet_serial(char buf[]);
int  EA_test_packet(char pkt[]); 
int  EA_pkt_build(char* pkt,int pll, char* payload);
int  EA_write_pkt_serial(char pkt[], int len);
void EA_init_serial(int rcv, int tx);
