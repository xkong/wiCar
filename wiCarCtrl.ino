
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

void setup(){
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  Mirf.setTADDR((byte *)"clie1");
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload =1;

  Mirf.channel=90;
  Mirf.config();  
  Serial.println("Start.."); 
}

void loop(){
  byte c;
  if(Serial.available())
  {
    c=Serial.read();

    Mirf.send(&c);
    Serial.println(c);
  }
}
