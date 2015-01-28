
#include <IRremote.h>
int RECV_PIN = 15;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Philips Audio System Control
void volDown()
{ 
  irsend.sendNEC(0x10EFA857, 32); // Philips Volume Up
}

void reduceBass()
{
  irsend.sendNEC(0x10EFE817, 32); //Philips reduce bass
}
void volUp()
{
  irsend.sendNEC(0x10EF28D7, 32); // Philips Volume Up
}

void setVol()
{
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x10EF00FF, 32); //Philips '1' code
    delay(40);
  }
  for (int i = 0; i < 6; i++) {
    reduceBass();
    delay(200);
  }
  for(int i=0;i<10;i++)
  {
    volUp();
    delay(200);
  }
}
//end of audio system control


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX); 

    switch(results.value)
    {

    case 0xC10: 

      digitalWrite(11,HIGH);
      delay(200);
      break;

    case 0x210: 

      digitalWrite(11,LOW);
      delay(200);
      break;

    case 0x610: 

      digitalWrite(12,HIGH);
      delay(200);
      break;

    case 0xE10: 

      digitalWrite(12,LOW);
      delay(200);
      break;

    case 0x10: 

      digitalWrite(13,HIGH);
      delay(200);
      break;

    case 0x810: 

      digitalWrite(13,LOW);
      delay(200);
      break;
    }


    irrecv.resume(); // Receive the next value
  }
} 





