/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
const int num = 4;
int array[num];
int newArray[num];
int stickLeftX = 90;
int stickLeftY = 90;
int stickRightX = 90;
int stickRightY = 90;

void setup() {
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
  s4.attach(5);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()){ 
    radio.read( &array, sizeof(array) ); 
    Serial.println(array[0]);
    stickLeftX = map(array[0], 0, 1023, 0, 180);
    stickLeftY = map(array[1], 0, 1023, 0, 180);
    stickRightX = map(array[2], 0, 1023, 0, 180);
    stickRightY = map(array[3], 0, 1023, 0, 180);
    Serial.println(stickLeftX);
   }
   //Serial.println(stickLeftX);
  s1.write(stickLeftX);
  s2.write(stickLeftY);
  s3.write(stickRightX);
  s4.write(stickRightY);
  //delay(100);
}