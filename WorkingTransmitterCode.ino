#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <stdlib.h>

// pin 12 is the transmit pin
RH_ASK driver;

unsigned int counter=0;
void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
  // word is a char array where we have the bytes after index 4 be a number based on a counter
    char word[50];
    word[0]='h';
    word[1]='e';
    word[2]='l';
    word[3]='l';
    word[4]='o';
    // modify based on the length of the number
    if(counter>=1000){
      counter=0;
    }else if(counter>=100){
      word[5]=counter/100+48;
      word[6]=(counter%100)/10 + 48;
      word[7]=((counter%100)%10)+48;
      word[8]='\0';
    }else if(counter>=10){
      word[5]=counter/10+48;
      word[6]=counter%10+48;
      word[7]='\0';
    }else{
      word[5]=48+counter;
      word[6]='\0';
    }

    driver.send((uint8_t *)word, strlen(50));
    driver.waitPacketSent();
    delay(500);
    Serial.println(word);
    counter++;
}