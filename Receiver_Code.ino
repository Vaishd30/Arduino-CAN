#include <SPI.h>
#include "mcp2515_can.h"
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[3];
unsigned char ack[3]="ACK";
char str[20];
void setup() {
Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
// start interrupt
attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), MCP2515_ISR, FALLING);
// init can bus : baudrate = 500k
while (CAN_OK != CAN.begin(CAN_500KBPS)) {
Serial.println("CAN init fail, retry...");
delay(1000);
}
Serial.println("CAN init ok!");
}
void MCP2515_ISR() {
flagRecv = 1;
}
void loop() {
if (flagRecv==1) {
// check if get data
flagRecv = 0; // clear flag
Serial.println("into loop");
// iterate over all pending messages
// If either the bus is saturated or the MCU is busy,
// both RX buffers may be in use and reading a single
// message does not clear the IRQ conditon.
while (CAN_MSGAVAIL == CAN.checkReceive()) {
// read data, len: data length, buf: data buf
Serial.println("checkReceive");
CAN.readMsgBuf(&len, buf);
// print the data
CAN.sendMsgBuf(0x00,0,8,ack);
for (int i = 0; i < len; i++) {
Serial.print(buf[i]); Serial.print("\t");
}
Serial.println();
}
}
}
