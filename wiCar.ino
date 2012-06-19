/**
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 */

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

const int pwm1=10;
const int pwm2=9; 
const int input1=4;
const int input2=5;
const int input3=6;
const int input4=3;


const int DefaultSpeedCtrl=150;
const int DefaultTurnCtrl=90;
 

void setup()
{
  unsigned char i;
  for(i=3;i<=6;i++)
  {
    pinMode(i,OUTPUT);
  }
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  Mirf.spi=&MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.setTADDR((byte *)"serv1");
  Mirf.payload=1;
  Mirf.channel=90;
  Mirf.config();
  Serial.begin(9600);
  Serial.println("Car Console Start...");
}

void loop()
{
  byte c;
  if (Mirf.dataReady())
  {
    Mirf.getData(&c);
    Serial.println(c);
    char cmd;
    cmd=char(c);
   // Serial.println(cmd);
    if(cmd=='w'){forward();}
    else if(cmd=='a'){left();}
    else if(cmd=='s'){back();}
    else if(cmd=='d'){right();}
    else if(cmd=='p'){parking();}
    else 
    {
      Serial.println(cmd);
    }
  }

}

void parking(void)
{
  analogWrite(pwm1,0);
  analogWrite(pwm2,0);
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
  //delay(1000);
}
void right(void)
{
  analogWrite(pwm1,DefaultTurnCtrl);
  analogWrite(pwm2,DefaultTurnCtrl);
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  //forward();
}
void back(void)
{
  analogWrite(pwm1,DefaultSpeedCtrl);
  analogWrite(pwm2,DefaultSpeedCtrl);
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
}
void left(void)
{
  analogWrite(pwm1,DefaultTurnCtrl);
  analogWrite(pwm2,DefaultTurnCtrl);
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  //forward();
}
void forward(void)
{
  analogWrite(pwm1,DefaultSpeedCtrl);
  analogWrite(pwm2,DefaultSpeedCtrl);
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
}

