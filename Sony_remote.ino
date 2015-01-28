/*
 
 * This program uses an IR transmitter and reciever simultaneously 
 * It will not work with the original Library from Ken Shirrif, but instead with the modified one by targetto
 * I have forked his library in my profile
 * Sony Power or 'A20' will send a series of NEC commands
 
 */

#include <IRremote.h> // targetto's library
#include <IRremoteInt.h>
IRsend irsend;

int RECV_PIN = 15; // TSOP reciever
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
//end of audio system control


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(10,OUTPUT); //Light
  pinMode(11,OUTPUT);//fan1
  pinMode(12,OUTPUT);//fan2
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX); //for debugging only

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

    case 0xA90: 

      {
        delay(1200);
        for (int i = 0; i < 3; i++) {
          irsend.sendNEC(0x10EF00FF, 32); //Philips '1' code
          delay(500);
        }
        for (int i = 0; i < 6; i++) {
          reduceBass();
          delay(400);
        }
        for(int i=0;i<10;i++)
        {
          volUp();
          delay(400);
        }
        irrecv.enableIRIn();
        break;
      }

    }

    delay(100);
    irrecv.resume(); // Receive the next value
  }
}
