#include <IRremote.h>
int RECV_PIN = A0;
int pinLB=6;//定义I1接口
int pinLF=9;//定义I2接口
int pinRB=3;//定义I3接口
int pinRF=5;//定义I4接口

long advence = 0x00EF807F;
long back = 0x00EFA05F;
long stop = 0x00EF906F;
long left = 0x00EF00FF;
long right = 0x00EF40BF;
IRrecv irrecv(RECV_PIN);
decode_results results;
void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) 
    {
     Serial.println("Could not decode message");
    } 
  else 
   {
    if (results->decode_type == NEC) 
      {
       Serial.print("Decoded NEC: ");
      } 
    else if (results->decode_type == SONY) 
      {
       Serial.print("Decoded SONY: ");
      } 
    else if (results->decode_type == RC5) 
      {
       Serial.print("Decoded RC5: ");
      } 
    else if (results->decode_type == RC6) 
      {
       Serial.print("Decoded RC6: ");
      }
     Serial.print(results->value, HEX);
     Serial.print(" (");
     Serial.print(results->bits, DEC);
     Serial.println(" bits)");
   }
     Serial.print("Raw (");
     Serial.print(count, DEC);
     Serial.print("): ");

  for (int i = 0; i < count; i++) 
     {
      if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
     } 
    else  
     {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
     }
    Serial.print(" ");
     }
      Serial.println("");
     }

void setup()
 {
  pinMode(RECV_PIN, INPUT);   
  pinMode(pinLB,OUTPUT);
  pinMode(pinLF,OUTPUT);
  
  pinMode(pinRB,OUTPUT);
  pinMode(pinRF,OUTPUT);
 
Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
 }

int on = 0;
unsigned long last = millis();

void loop() 
{
  if (irrecv.decode(&results)) 
   {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250) 
      {
       on = !on;
//       digitalWrite(8, on ? HIGH : LOW);
       digitalWrite(13, on ? HIGH : LOW);
       dump(&results);
      }
    if (results.value == advence )
    {digitalWrite(pinRB,LOW);//使直流电机（右）GO
    digitalWrite(pinRF,HIGH);
    digitalWrite(pinLB,LOW);//使直流电机（左）GO
    digitalWrite(pinLF,HIGH);}

    if (results.value == back )
   

     {digitalWrite(pinRB,HIGH);//使直流电机（右）BACK
     digitalWrite(pinRF,LOW);}

    if (results.value == left )
    { digitalWrite(pinRB,LOW);//使直流电机（右） STOP
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);//使直流电机（左）GO
     digitalWrite(pinLF,LOW);}


    if (results.value == right )
    { digitalWrite(pinRB,HIGH);//使直流电机（右）GO
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,HIGH);//使直流电机（左）STOP
     digitalWrite(pinLF,HIGH);}

    if (results.value == stop )
      {
     digitalWrite(pinRB,HIGH);//使直流电机（右）STOP
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);//使直流电机（左）STOP
     digitalWrite(pinLF,HIGH);
   
   } 
          
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
}
