A MiniReteLoRa is a technology that allows the acquisition and transmission of quantities detected by sensors, located in mainly outdoor locations, therefore without WiFi connectivity, requiring little energy and low costs. However, nothing prevents us from using this technique even in a closed environment, such as our home or factory.
While the term LoRa indicates the modulation technology of a radio carrier, patented by the Semtech company, the terms MiniReteLoRa and LoRaWAN are used to define a type of device architecture, with their software, which exploit LoRa technology to transmit and receive data .
The MiniReteLoRa, which I describe here, should not be confused with the LoRaWAN protocol, created for a more complex network infrastructure and more suitable for commercial use. LoRaWAN is made for many transmitter nodes and some receivers (gateways) connected on the Internet to a network server managed by the service provider. The LoRaWAN architecture, having multiple gateways in the network, offers greater spatial coverage. 
For more detailed informations, you can read the pdf file "How you can make and set up a Mini Rete LoRa ... and monitor (almost) anything”.
The programs are compatible for these boards: for TX nodes: 
•	LILYGO®TTGO T-Deer Pro Mini; 
•	LILYGO®TTGO LoRa32 SX1276; 
•	LILYGO®TTGO LoRa32 T3_V1.6.1 (LoRa32 V2.1_1.6); 
•	Arduino Pro Mini 8 MHz 3V3 + RFM95 LoRa module; 
•	Adafruit Feather 32u4 LoRa.
…and for RX node:
•	LILYGO®TTGO LoRa32 T3_V1.6.1 (LoRa32 V2.1_1.6)
•	LILYGO® TTGO LORA32 868/915Mhz (LoRa32 V1.0)

Programs can be uploaded by means of Arduino IDE.

New programs are available:  TX_Generic_LoRa and RX_Generic_Autoconnect_Milano_V4.  
The first program can be used for a generic TX node, it uses  LoRa.h library instead of RadioHead. It has the possibility to change Spreading Factor value, from 7 to 12.
The second program can be used for a generic RX node that can receive messages from TX node using LoRa.h or RadioHead library. In this program you can interactively set frequency, Spreading Factor and WiFi credential.

