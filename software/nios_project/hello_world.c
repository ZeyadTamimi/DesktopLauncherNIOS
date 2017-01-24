/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>

#define RS232_Control     (*(volatile unsigned char *)(0x84000210))
#define RS232_Status      (*(volatile unsigned char *)(0x84000210))
#define RS232_TxData      (*(volatile unsigned char *)(0x84000212))
#define RS232_RxData      (*(volatile unsigned char *)(0x84000212))
#define RS232_Baud        (*(volatile unsigned char *)(0x84000214))
#define GPS_Control     (*(volatile unsigned char *)(0x84000210))
#define GPS_Status      (*(volatile unsigned char *)(0x84000210))
#define GPS_TxData      (*(volatile unsigned char *)(0x84000212))
#define GPS_RxData      (*(volatile unsigned char *)(0x84000212))
#define GPS_Baud        (*(volatile unsigned char *)(0x84000214))
#define Bluetooth_Control     (*(volatile unsigned char *)(0x84000220))
#define Bluetooth_Status      (*(volatile unsigned char *)(0x84000220))
#define Bluetooth_TxData      (*(volatile unsigned char *)(0x84000222))
#define Bluetooth_RxData      (*(volatile unsigned char *)(0x84000222))
#define Bluetooth_Baud        (*(volatile unsigned char *)(0x84000224))

void Init_RS232(void);
int putcharRS232(int c);
int getcharRS232(void);
int RS232TestForReceivedData(void);

void Init_RS232(void)
{
  // set up 6850 Control Register to utilise a divide by 16 clock,
  // set RTS low, use 8 bits of data, no parity, 1 stop bit,
  // transmitter interrupt disabled
  // program baud rate generator to use 115k baud

  // 0001 0101
  RS232_Control = 0x15;
  // 115200 baud rate
  RS232_Baud = 0x01;
}

int putcharRS232(int c)
{
  // poll Tx bit in 6850 status register. Wait for it to become '1'
  // write 'c' to the 6850 TxData register to output the character
  while (!(RS232_Status & 0x02));
  RS232_TxData = (unsigned char) c;
  return c; // return c
}

int getcharRS232(void)
{
  // poll Rx bit in 6850 status register. Wait for it to become '1'
  // read received character from 6850 RxData register.
  while (!RS232TestForReceivedData());
  return RS232_RxData;
}

int RS232TestForReceivedData(void)
{
  // Test Rx bit in 6850 serial comms chip status register
  // if RX bit is set, return TRUE, otherwise return FALSE
  return RS232_Status & 0x01;
}

int main()
{
  Init_RS232();

  while(1)
  {
    char c = getcharRS232();
    printf("%c\n", c);
  }

  /*
  Bluetooth_Control = 0x15;
  Bluetooth_Baud = 0x01;

  Bluetooth_TxData = 'x';
  char c = getcharRS232();

  putcharRS232('a');
  while (!(Bluetooth_Status & 0x01));

  printf("Bluetooth_RxData: %c\n", Bluetooth_RxData);

  printf("Hello from Nios II! %c\n", c);
  */
  // printf("Hello from Nios II!\n");
  return 0;
}
