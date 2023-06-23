#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

// connect the reciever pin to 4, and a buzzer from 11 to ground
RH_ASK driver(2000, 4,12,10,false);

void setup()
{
    Serial.begin(9600);
    if (!driver.init())
         Serial.println("init failed");

  // this makes a buzzer signal when a message is recieved
  pinMode(11,OUTPUT);
  // this makes the onboard LED lightup
  pinMode(13,OUTPUT);

}

void loop()
{
    uint8_t buf[50];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {

      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf); 

      // turn on buzzer and LED
      analogWrite(11,255/2);
      digitalWrite(13,HIGH);
      delay(50);
      // turn back off
      analogWrite(11,0);
      digitalWrite(13,LOW);   

    }
}