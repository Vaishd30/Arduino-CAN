#include <SPI.h>
#include "mcp2515_can.h"
const int SPI_CS_PIN = 10;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
unsigned char len=0;
unsigned char recvmsg[4];
void setup() {
Serial.begin(115200);
while(!Serial){};
// init can bus : baudrate = 500k
while (CAN_OK != CAN.begin(CAN_500KBPS)) {
Serial.println("CAN init fail, retry...");
delay(100);
}
Serial.println("CAN init ok!");
}
unsigned char stmp[3] = {0, 0, 0};
int i=0;
void loop() {
// send data: id = 0x00, standrad frame, data len = 8, stmp: data buf
stmp[2] = stmp[2] + 1;
if (stmp[2] == 60) {
stmp[2] = 0;
stmp[1] = stmp[1] + 1;
if (stmp[1] == 60) {
stmp[0] = 0;
stmp[0] = stmp[0] + 1;
if(stmp[0]==24)
stmp[0]=0;
}
}
CAN.sendMsgBuf(0x00, 0, 3, stmp);
CAN.readMsgBuf(&len,recvmsg);
for(i=0;i<4;i++)
{
if(recvmsg[i]==65)
Serial.print("A");
else if(recvmsg[i]==67)
Serial.print("C");
else if(recvmsg[i]==75)
Serial.print("K received");
}
Serial.print("\n");
delay(1000); // send data per 100ms
Serial.println("CAN BUS sendMsgBuf ok!");
}
