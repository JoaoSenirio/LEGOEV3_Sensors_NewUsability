/*
  Check out the details and usage of this project on README.md

  Reading touch, light/color and infrared sensors from the LEGO MINDSTORM EV3 collection

  Compiler: Arduino IDE 2.0.3
  Board: Arduino Uno

  Author: João Senírio de Sousa Costa
  Date: February of 2023
*/

#include <AltSoftSerial.h>

#define Max_baudrate 57600
#define ID_sensor A4
#define SimpleSensor_read 8
#define NACK 0x02
#define ACK 0x04
#define checkbyte_cst 0xFF

bool flag_pinMode = false,
     flag_Serialbegin = false,
     isConnected = false,
     isBtnSensor = false,
     isColorSensor = false,
     isIRSensor = false;

byte select_mode = 0; 

void Setup_UARTSensor();
void Read_UARTSensor(int *value);
void Show_UARTSensor_Read(int *value);
void ChangeMode();

AltSoftSerial LegoSerial;

void setup(){
  Serial.begin(57600);
  pinMode(ID_sensor, INPUT);
}

void loop(){  
  
  unsigned long last_millis; 
  int value_read; 

  //No sensor connected
  if(analogRead(ID_sensor) > 950){ //Reset all flags and variables
    if(flag_pinMode){
      flag_pinMode = false; 
      isBtnSensor = false;
    }
    else if(isConnected){
      isConnected = false;
      flag_Serialbegin = false; 
      isIRSensor = false;
      isColorSensor = false;
      LegoSerial.end();
    } 
  }

  //Simple sensor connected 
  while(analogRead(ID_sensor) >= 80 && analogRead(ID_sensor) <= 100){ //Internal resistor between GND and Pin 1 provide low voltage on analog port
    if(!flag_pinMode){ //Handle setup input pin only once
      flag_pinMode = true;
      isBtnSensor = true;
      pinMode(SimpleSensor_read, INPUT);
    }
    Serial.println(digitalRead(SimpleSensor_read));
  }

  //Sensor which needs communication connected
  while(analogRead(ID_sensor) == 0){ //Pin 1 is short-circuted with GND, providing GND voltage on analog port
    if(!isConnected) Setup_UARTSensor();
    else{ //The sensor is already connected
      if((millis() - last_millis) >= 100){
        last_millis = millis();
        LegoSerial.write(NACK);
      }
      if(isColorSensor && Serial.available()) ChangeMode(); //Change color sensor mode by user request
      if(LegoSerial.available() >= 3){ //Handle data package
        Read_UARTSensor(&value_read);
        Show_UARTSensor_Read(&value_read);
      }
    }
  }
}

void Setup_UARTSensor(){

  byte First_Package[2];

  if(!flag_Serialbegin){ //Control if to execute Serial1.begin() only once
    LegoSerial.begin(2400);
    flag_Serialbegin = true;
  }
  while(LegoSerial.available()){ //Process sensor all initial package
    First_Package[0] = First_Package[1];
    First_Package[1] = LegoSerial.read();
    if(First_Package[1] == 0x1D) isColorSensor = true; //0x1D indicate device type of color sensor
    if(First_Package[1] == 0x21) isIRSensor = true; //0x21 indicate device type of IR sensor
    if((First_Package[0] == 0xED) && (First_Package[1] == 0x04)){ //Look for the end of initial package  
      LegoSerial.write(ACK); //Send ACK
      LegoSerial.flush(); //Wait until all bytes written go out
      LegoSerial.end(); 
      LegoSerial.begin(Max_baudrate); //Restart Serial communication on Max baurate acept by the sensor
      isConnected = true;
      delay(50);
    }  
  }
}

void Read_UARTSensor(int *value){

  byte checkbyte, Data_Package[3];

  LegoSerial.readBytes(Data_Package, 3);
  checkbyte = Data_Package[0] ^ Data_Package[1] ^ checkbyte_cst; //Checks if checkbyte is correct
  if(checkbyte == Data_Package[2]) *value = int(Data_Package[1]); //If checkbyte matches change the value to the new value received
}

void Show_UARTSensor_Read(int *value){
  if(isIRSensor) Serial.println(*value);
  else if(isColorSensor){
    switch(select_mode){
      case 0: 
        if(*value >= 0 && *value <= 100) Serial.println(*value); //Check if *value is on correct range, depending on the mode
        break;
      case 1: 
        if(*value >= 0 && *value <= 100) Serial.println(*value); //Check if *value is on correct range, depending on the mode
        break;
      case 2:
        if(*value >= 0 && *value <= 7) Serial.println(*value); //Check if *value is on correct range, depending on the mode
        break;
    }
  }
}

void ChangeMode(){

  select_mode = Serial.read() - 48;

  if(select_mode >= 0 && select_mode <= 2){ //Check if mode select is on range [0,2]
    LegoSerial.write(0x43);
    LegoSerial.write(select_mode); 
    LegoSerial.write(0x43 ^ select_mode ^ checkbyte_cst); //Calculating checkbyte
    LegoSerial.flush();
    }
}
