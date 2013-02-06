 /*   
  *  ------ Read EM4100/02 tag -------- 
  *   
  *  Explanation: This sketch looks for EM4100/02 RFID cards. If a tag is  
  *  detected, the module reads its serial number. 
  *   
  *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L. 
  *  http://www.libelium.com 
  *   
  *  This program is free software: you can redistribute it and/or modify 
  *  it under the terms of the GNU General Public License as published by 
  *  the Free Software Foundation, either version 3 of the License, or 
  *  (at your option) any later version. 
  *   
  *  This program is distributed in the hope that it will be useful, 
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  *  GNU General Public License for more details. 
  *   
  *  You should have received a copy of the GNU General Public License 
  *  along with this program. If not, see . 
  *   
  *  Version:                0.1 
  *  Design:                 David Gascon 
  *  Implementation:         Marcos Yarza, Javier Solobera 
  */ 
 
 
 
// stores the status of the executed command: 
uint8_t state = 1; 
// stores the first byte of the EM4100/02 card's serial number: 
uint8_t serNum0 = 0x00 
uint8_t serNum1 = 0x00; 
uint8_t serNum2 = 0x00; 
uint8_t serNum3 = 0x00; 
 
 
 
void setup() 
{ 
  USB.begin(); 
  USB.println("RFID @ 125 KHz module started"); 
  // switchs on the RFID @ 125 KHz module, and asigns the socket 
  RFID125.ON(SOCKET0); 
  delay(1000); 
} 
 
 
 
void loop() 
{ 
  USB.print("\n"); 
  USB.println("Ready to read..."); 
   
  state = RFID125.readSerialNumber(seconds, serNum0, serNum1, serNum2, serNum3); 
  if (state == 0) 
  { 
    USB.print("\r\nEM4100/02 card detected: "); 
    USB.print(serNum0); USB.print(" "); 
    USB.print(serNum1); USB.print(" "); 
    USB.print(serNum2); USB.print(" "); 
    USB.print(serNum3); 
  } 
}
