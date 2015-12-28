#include <IRremote.h>  
#include <Servo.h>

const int MotorRB = 5;
const int MotorRF = 6;
const int MotorLB = 10;
const int MotorLF = 11;

const int USServoPin = 9;
const int USTriggerPin = 13;
const int USEchoPin = 12;

const int IRRecvPin = 2;

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance



IRrecv irrecv(IRRecvPin);
Servo myservo;


void setup()
{  
  Serial.begin(9600); 
  
  pinMode( MotorRB, OUTPUT);
  pinMode( MotorRF, OUTPUT);
  pinMode( MotorLB,  OUTPUT);
  pinMode( MotorLF,  OUTPUT);
  
  myservo.attach(USServoPin);
  myservo.write(0);
  delay(150);
  myservo.write(90);
  delay(150);

  pinMode (USTriggerPin, OUTPUT);
  pinMode (USEchoPin, INPUT) ;

  irrecv.enableIRIn(); // Start the receiver

  Serial.println("Yes sir, waiting for your commands!");
}


decode_results results;
void dump(decode_results *results) 
{
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



int idx = 0;
int cnt = 0;
int inp = 0;


long advence = 0x00EF807F;
long back = 0x00EFA05F;
long stop = 0x00EF906F;
long left = 0x00EF00FF;
long right = 0x00EF40BF;

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
    {
          Serial.println("IR command forward ");
    }
    
          
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
 
  
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    inp = Serial.read();
    
    switch ( inp )
    {
      case '1': 
      case '2': 
      case '3': 
      case '4': 
      case '5': 
        {
          int angle = (inp - '0' - 1)  * 45;
          Serial.println("Set servo to angle ");
          Serial.print(angle, DEC);
          myservo.write( angle ); 
        }
        break;
 
      case '0':
        Serial.print("Servo sweep ");
        for ( idx = 0; idx < 180; idx += 10 ) 
        {
          myservo.write( idx ); 
          delay(250);
        }
        for ( idx = 180; idx > 0; idx -= 10 ) 
        {
          myservo.write( idx ); 
          delay(250);
        }
        myservo.write( 90 ); 
        break;

      case 'q':
        Serial.println("Motor right backwards");
        digitalWrite (MotorRB, HIGH);
        delay(250);
        digitalWrite (MotorRB, LOW);
        break;
      case 'w':
        Serial.println("Motor right forwards");
        digitalWrite (MotorRF, HIGH);
        delay(250);
        digitalWrite (MotorRF, LOW);
        break;
      case 'e':
         Serial.println("Motor left backwards");
         digitalWrite (MotorLB, HIGH);
         delay(250);
         digitalWrite (MotorLB, LOW);
        break;
      case 'r':
         Serial.println("Motor left forwards");
         digitalWrite (MotorLF, HIGH);
         delay(250);
         digitalWrite (MotorLF, LOW);
        break;


     case 'p':
         Serial.println("Ultraound ping");
         for  (idx=0;idx<10; idx++ )
         {
         
          /* The following trigPin/echoPin cycle is used to determine the
           distance of the nearest object by bouncing soundwaves off of it. */ 
           digitalWrite(USTriggerPin, LOW); 
           delayMicroseconds(2); 
          
           digitalWrite(USTriggerPin, HIGH);
           delayMicroseconds(10); 
           
           digitalWrite(USTriggerPin, LOW);
           duration = pulseIn(USEchoPin, HIGH);
           
           //Calculate the distance (in cm) based on the speed of sound.
           distance = duration/58.2;
           
           if (distance >= maximumRange || distance <= minimumRange)
           {
             Serial.println("out of range");
           }
           else 
           {
             Serial.println(distance);
           }
           
           //Delay   150ms before next reading.
           delay(150);         
         }
        break;
    default:
             Serial.println("Unknown command");
     break;
    }
  }
}

 
