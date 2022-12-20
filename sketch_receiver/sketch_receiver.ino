#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 10); // CE, NAN

const byte address[6] = "00001";

int mikI = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    //radio.read(&mikI, sizeof(int));
    //char a[20];
    //radio.read(&a, sizeof(a));
    //Serial.println(radio.available());
    /*if(mikI != 0){
      Serial.println(mikI);
    }*/
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}