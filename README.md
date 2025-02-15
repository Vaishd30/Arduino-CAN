# Arduino-CAN
CAN protocol communication between two Arduino Unos.

# Hardware Components
1. Two Arduino Uno Boards
2. MCP2515 CAN controller module
3. Jumper wires to connect the boards and modules

# Software Components
1. Arduino IDE
2. Libraries such as "mcp2515_can.h", "SPI.h"

# Arduino Uno

![Arduino UNO](https://github.com/user-attachments/assets/b74e05e6-04ed-4a97-bb29-77516f7d8715) 

# Arduino Uno Pinout

![Arduino Pinout](https://github.com/user-attachments/assets/a931d2a7-4864-4c96-a1a6-0edc6cb2b697)

# Arduino IDE

![Arduino IDE](https://github.com/user-attachments/assets/cdb9caf0-32d4-46bb-adb9-bd8fb245bba5)

# MCP2515

![MCP2515](https://github.com/user-attachments/assets/0e96ede6-0ea7-430c-b2d3-cc4871094b22) 

# Circuit Diagram

![Circuit Diagram](https://github.com/user-attachments/assets/33d83240-acb1-4898-afdb-b711e929307f)

MCP2515----Arduino Uno
VCC----5V
GND----GND
CS----D10
SO----D12
SI----D11
SCK----D13
INT(receiver)----D2(receiver)
Also connect CAN_H and CAN_L of transmitter MCP2515 to CAN_H and CAN_L of receiver MCP2515 

# Hardware Setup
![Hardware Setup](https://github.com/user-attachments/assets/e248becc-4bdd-483e-a857-a91ebf0873a7)

# Transmitter Code Explanation:

1. The code is for implementing CAN Bus communication betweeen two Arduino Uno boards using MCP2515 module. The MCP2515 module is connected to the Arduino Uno through SPI communication using the mcp2515_can library.
2. In the setup() function serial communication is initiated and the MCP2515 module is initialized with baud rate of 500Kbps. A loop is added to keep retrying the initialization process until it is succsessful
3. In the loop() function, a message is sent using the CAN.sendMsgBuf() function with an ID of 0x00, a standard frame, a data length of 3, and a data buffer stmp. The stmp buffer is incremented in each iteration of the loop.
4. Then, the CAN.readMsgBuf() function is called to receive any messages on the CAN bus. If there is a message, It is stored in the recvmsg buffer. The received message is then printed to the serial monitor.
5. The loop is delayed by 1000 milliseconds before sending the next message. The process repeats continously.
6. In this specific code, the recvmsg buffer is checked for specific values and the coressponding character is printed to the serial monitor. If the value in the recvmsg buffer is 65, "A" is printed, if the value is 67, "C" is printed, and if the value is 75, "K" is printed.

# Receiver Code Explanation:

1. This code demonstrates the use of the MCP2515 library to enable communication between two Arduino boards via a CAN bus. The code begins with the defenition of the SPI chip select (CS) pin and the CAN interrupt pin. The MCP2515_CAN object is then created with the specified CS pin.
2. The setup() function initializes the serial port and attaches an interrupt to the CAN interrupt pin. The CAN bus is then initialized with a baud rate of 500Kbps. The function waits until the initialization is successful before continuing.
3. The loop() function first checks if a flag flagRecv has been set to 1, indicating that a message has been received. If a message has been received, the flag is cleared and the function iterates over all pending messages using CAN.readMsgBuf() function is then used to read the length and data of the message into the len and buf variables.
4. The message is acknowledged using CAN.sendMsgBuf() with the ack message buffer. The message data is then printed to the serial monitor using a for loop.
5. The interrupt service routine MCP2515_ISR() is used to set the flagRecv flag to 1 when a message is received. The ISR is called when a falling edge is detected on the CAN interrupt pin.
6. Overall, the code demonstrates how to set up  communication between two Arduino boards using a CAN bus and the MCP2515 library.The code reads messages from the bus and prints them to the serial monitor, and also sends a response to acknowledge receipt of the original message.

# Result
Messages on Serial monitor indicating that the message has been successfully transmitted and Acknowledgement has been received

![Output](https://github.com/user-attachments/assets/ff7642e3-a892-463f-83ab-ed35a5336d3a)  

Received Messages on Serial Monitor

![Output1](https://github.com/user-attachments/assets/fb9874f4-4614-4a88-b241-eaa34b4f55d5)

# References

[1] "Arduino CAN Bus Module Tutorial" by Julian Ilett: https://www.youtube.com/watch?v=e6f3T8WJzgI

[2] "Arduino CAN Bus Interface: What is it and How to Use it" by All About Circuits: https://www.allaboutcircuits.com/projects/arduino-can-bus-interface-what-is-it-and-how-to-use-it/

[3] "CAN-BUS Shield V2" Wiki page by Seeed Studio: https://wiki.seeedstudio.com/CAN-BUS_Shield_V2/

[4] "MCP2515 Datasheet" by Microchip Technology Inc.: https://ww1.microchip.com/downloads/en/DeviceDoc/20001801H.pdf

[5] "CAN Bus Protocol Tutorial" by Copperhill Technologies: https://copperhilltech.com/blog/can-bus-protocol-tutorial/

[6] https://www.tutorialspoint.com/can-bus-with-arduino

[7] "Design and Implementation of CAN Bus Communication System Based on Arduino", by Yunhao Li, published in the 2nd International Conference on Computer Science and Network Technology.

[8] "Implementation of a CAN Bus System Using Arduino", by James J. E. Hughes, published in the 2015 IEEE Global Humanitarian Technology Conference.





