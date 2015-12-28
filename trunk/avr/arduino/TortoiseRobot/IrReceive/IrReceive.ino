/*
 * IRRemote Infrared remote teaching
 * Sample 1.2: Show infrared protocol types, such as NEC, Sony SIRC, Philips RC5, Philips RC6 and other agreements
 */
#include <IRremote.h>                    // References IRRemote library

const int irReceiverPin = 2;             // Infrared signal receiver connected to the pin 2 OUTPUT

IRrecv irrecv(irReceiverPin);            // Definition IRrecv object to receive infrared signals
decode_results results;                  // Decoding results will be placed in decode_results result variable structure

void setup()
{
  Serial.begin(9600);                     // Open the Serial port, communication speed is 9600 bps
  Serial.print("Waiting for remote input: \n");            
  irrecv.enableIRIn();                   // Start infrared decoding
}

// Display types of infrared messages
void showIRProtocol(decode_results *results) 
{
  Serial.print("Protocol: ");
  
  switch(results->decode_type) {
   case NEC:
     Serial.print("NEC");
     break;
   case SONY:
     Serial.print("SONY");
     break;
   case RC5:
     Serial.print("RC5");
     break;
   case RC6:
     Serial.print("RC6");
     break;
   default:
     Serial.print("Unknown encoding");  
  }  

  // The infrared code printed on the Serial port
  Serial.print(", irCode: ");            
  Serial.print(results->value, HEX);    // Infrared code
  Serial.print(",  bits: ");           
  Serial.println(results->bits);        // Infrared code bit number   
}

void loop() 
{
  if (irrecv.decode(&results)) {         // Decoding is successful, receive a set of infrared signals
    showIRProtocol(&results);            // Display decoded message
    irrecv.resume();                     // Continue to receive the next set of infrared signals      
  }  
}

