#include <Servo.h> 
#include <avr/sleep.h>
#include <avr/wdt.h>
#include "pitches.h"

// pro mini info
// Serial: 0 (RX) and 1 (TX). Used to receive (RX) and transmit (TX) TTL serial data. These pins are connected to the TX-0 and RX-1 pins of the six pin header.
// External Interrupts: 2 and 3. These pins can be configured to trigger an interrupt on a low value, a rising or falling edge, or a change in value. See the attachInterrupt() function for details.
// PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM output with the analogWrite() function.// 
// SPI: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK). These pins support SPI communication, which, although provided by the underlying hardware, is not currently included in the Arduino language.
// LED: 13. There is a built-in LED connected to digital pin 13. When the pin is HIGH value, the LED is on, when the pin is LOW, it's off.


const int doorServoStartPos = 35;
const int doorServiDeltaPos = 50;

const int switchServoStartPos = 65;
const int switchServoDeltaPos = 60;

static int cnt = 0;

Servo switchServo;
Servo doorServo;	 
int switchActive=LOW;
 
static void MoveServo( Servo& servo, int fromAngle, int toAngle, unsigned int usec, int postDelayInMs );
static void ExecuteSequence( int sequence );

int sequence = 0;


static int DoorPos(int percentage)
{
  return doorServoStartPos + (doorServiDeltaPos * percentage ) / 100;
}

static int SwitchPos(int percentage)
{
  return switchServoStartPos + (switchServoDeltaPos * percentage ) / 100;
}

const int switchServoPin = 13;
const int doorServoPin = 12;
const int relayPin = 8;
const int buzzerPin = 6;
const int switchPin = 2;


void SetRelay( bool on)
{
  if ( on )
  {
    Serial.println("Relay On");
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
  }
  else
  {
    Serial.println("Relay Off");
    pinMode(relayPin, INPUT);
    digitalWrite(relayPin, HIGH);    
  }
  
}

void setup() 
{
   
  pinMode(switchPin, INPUT); 
  digitalWrite(switchPin, HIGH);       // turn on pullup resistors

  switchServo.attach(switchServoPin);
  doorServo.attach(doorServoPin); 
  
  SetRelay( HIGH );
    
  // move servo's to zero position
  switchServo.write(SwitchPos(0));
  doorServo.write(DoorPos(0));

  delay(300);
  SetRelay( LOW );

  // Save power, set unused pins to input and set high
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
  pinMode(5, INPUT);
  digitalWrite(5, HIGH);
  pinMode(6, INPUT);
  digitalWrite(6, HIGH);
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  pinMode(9, INPUT);
  digitalWrite(9, HIGH);
  pinMode(10, INPUT);
  digitalWrite(10, HIGH);
  pinMode(11, INPUT);
  digitalWrite(11, HIGH);
  DDRC = 0;               //Analog input 1/6 (PortC) set to input high also
  PORTC = 63;
  Serial.begin(9600);  


  pinMode(doorServoPin, INPUT);
  pinMode(switchServoPin, INPUT);
  
  digitalWrite(doorServoPin, HIGH);
  digitalWrite(switchServoPin, HIGH);
  
  Serial.println("Version 0.38" );

  //External interrupt INT0
  EICRA=0;   //The low level of INT0 generates an interrupt request
  EIMSK=1;   //External Interrupt Request 0 Enable

  switchActive=!digitalRead(switchPin);
} 


ISR(INT0_vect)
{
  EIMSK=0;   //Turn off interrupt
}


void PlaySound( int sound ) ;

// Main loop  
void loop() 
{ 
  Serial.print("Cnt loop "); Serial.print( cnt, DEC);Serial.print("Switch ");Serial.println( switchActive );
 
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    int inp = Serial.read();
		
    switch ( inp )
    {
      case 'q':
      break;   
      case 'r':
      break;   
      case 's':
      break;   
      case 'p':
        if ( sequence > 0 ) sequence--;
	ExecuteSequence(sequence);
	break;   
			  
      case 'h': 
        ExecuteSequence(sequence++);
	break;   
      default:
        Serial.println("Unknown command");
	break;
    }
  } 
  
  if(switchActive)
  {
    ExecuteSequence(sequence++);	
  }
 
  if ( ( cnt == 50 ) && (switchActive == 0 ))
  {
    Serial.print("Sleep ... flush now ");
    Serial.flush();
    
    //Set sleep mode, turn off MOSFET and servos
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    PRR = 255;
    MCUCR |= (1<<BODS) | (1<<BODSE);
    MCUCR &= ~(1<<BODSE);   
    EIMSK=1;
    sleep_mode();
    // ZZZzzz…
    sleep_disable();     //Awake again…
    PRR = 0;

    cnt = 0;
    Serial.print("Awake ... ");
  }
  
  delay(100);
  switchActive=!digitalRead(switchPin);
  cnt++;
}



static void MoveServo( Servo& servo, int fromAngle, int toAngle, unsigned int usec, int postDelayInMs )  
{
  //Serial.print("MoveServo from (angle)  "); Serial.print( fromAngle, DEC);
  //Serial.print(" to  "); Serial.println( toAngle, DEC);
 
  if(fromAngle <= toAngle)
  {
    for(int pos = fromAngle; pos < toAngle; pos += 1)
    {
      servo.write(pos);
      delayMicroseconds(usec);
    }
  }
  else
  {
    for(int pos = fromAngle; pos>=toAngle; pos-=1)
    {
      servo.write(pos);
      delayMicroseconds(usec); 
    }
  }
  delay( postDelayInMs );
}





void MoveDoor(int fromAngle, int toAngle, int innerWaitInuSec, int outerWaitInmSec)
{
  //Serial.print("MoveDoor from (oerc)  "); Serial.print( fromAngle, DEC);
  //Serial.print(" to  "); Serial.println( toAngle, DEC);
  MoveServo( doorServo, DoorPos(fromAngle),DoorPos(toAngle),innerWaitInuSec, outerWaitInmSec);
}

void MoveSwitch(int fromAngle, int toAngle, int innerWaitInuSec, int outerWaitInmSec)
{
  //Serial.print("MoveSwitch from (oerc)  "); Serial.print( fromAngle, DEC);
  //Serial.print(" to  "); Serial.println( toAngle, DEC);
  MoveServo( switchServo, SwitchPos(fromAngle),SwitchPos(toAngle),innerWaitInuSec, outerWaitInmSec);
}

void PushSwitch()
{
  switchServo.write(SwitchPos(70));
  delay(200);
  switchServo.write(SwitchPos(140));
  delay(100);
  switchServo.write(SwitchPos(100));
  delay(100);
}


static void ExecuteSequence(int sequence)
{
  delay(300);
  pinMode(doorServoPin, OUTPUT);
  pinMode(switchServoPin, OUTPUT);
  SetRelay( HIGH );
  sequence = sequence % 10;
  Serial.print("ExecuteSequence "); Serial.println( sequence, DEC);
	
  switch ( sequence )
  {
    case 0:
      PlaySound(-1);
      MoveDoor(    0,100, 1000,    0);
      MoveSwitch(  0,150, 1,500);
      MoveSwitch( 150,  0, 1000,    0);
      MoveDoor(  100,  0,  500,    0);
    break;
    case 1:
      PlaySound(4);

      MoveDoor(    0, 28, 3000,    0);		
      MoveDoor(   28, 37,    1,  120);
			
      for ( int i =0; i< 12; i++ )
      {
        MoveDoor(   60, 20,  0,  220);
        MoveDoor(   20, 60,  0,  220);
      }
			
      MoveSwitch(   0, 100,    0, 500);
      PushSwitch();
      MoveSwitch( 100,  0,  5000,   0);

      MoveDoor(   100,  0,  500,   0);
    break;
    case 2:
      PlaySound(2);

      delay(780);
      MoveDoor(     0,80,    1,    1);

      MoveSwitch(   0,100, 5000,    0);
      MoveSwitch( 100,  0, 5000,    0);
      MoveSwitch(   0,100, 5000,    0);
      PushSwitch();
      MoveSwitch(100,  0,    1,  200);

      MoveDoor(  100,  0,    1,  400);
    break;
    case 3:
      delay(3000);
      PlaySound(3);
      MoveDoor(     0,100, 2000, 1500);
      MoveDoor(  100,   0,10000, 1000);
      MoveDoor(     0,100,   20,  300);

      MoveSwitch(   0, 100,   1,  450);
      PushSwitch();
      MoveSwitch( 100,  0,   1,  300);

      MoveDoor(   100,  0,   1,  400);
    break;
    
    case 4:
      delay(1000);
      PlaySound(-1);
			
      MoveDoor(    0,100,    1,    1);
      MoveSwitch(  0,100,    1,  450);
			
      for (int i =0; i<10; i++ )
      {
        MoveSwitch( 70, 30, i * 1000, 100 );
	MoveSwitch( 30, 70, i * 1000, 100 );
      }
			
      PushSwitch();
      MoveSwitch( 100, 0, 1, 200);

      MoveDoor(   100, 0, 1, 400);
    break;
   
    case 5:
      PlaySound(-1);
      delay(1500);

      for (int i =0; i<10; i++ )
      {
        MoveDoor( 0, i * 10 , 200, 500 );
        MoveDoor( i * 10,100, 200, 500 );
      }

      MoveSwitch(   0, 70,   1, 1000);
      PushSwitch();
      MoveSwitch( 100,   0, 200, 200);

      MoveDoor(   100, 0, 1, 400);
    break;
    
    case 6:
      PlaySound(0);
      delay(500);
      MoveDoor(0, 62, 1,200);
			
      for (int i =0; i<10; i++ )
      {
        MoveDoor( 28, 62, 1, 100 );
        MoveDoor( 62, 28, 1, 100 );
      }
			
      MoveDoor(62, 0, 1, 200);
      MoveDoor(0, 100, 1, 1);
      MoveSwitch( 0, 70, 1, 450);
      PushSwitch();
      MoveSwitch( 100, 0, 1, 200);
      MoveDoor(100, 0, 1, 400);
    break;
    
    case 7:
      PlaySound(-1);
      delay(200);
			
      MoveDoor(  0,  62, 1, 200);
      MoveDoor( 62,  28, 1, 100);
      MoveDoor( 28,  62, 1, 100);
      MoveDoor( 62,  28, 1, 100);
			
      for (int i =0; i<10; i++ )
      {
        MoveDoor( 28, 37, 1, 50 );
        MoveDoor( 37, 28, 1, 50 );
      }
			
      MoveDoor(   28,   0, 1, 200 );
      MoveDoor(    0, 100, 1,  50 );
			
      MoveSwitch(   0, 70, 1, 450);
      PushSwitch();
      MoveSwitch( 100,   0, 1, 200);
			
      MoveDoor(  100,   0, 1, 400);		
      break;
      
    case 8:
      PlaySound(1);
      delay(1000);
			
      MoveDoor( 0,  62, 2000,500);
      MoveDoor( 62, 28, 1000,  1);
			
      for (int i =0; i<10; i++ )
      {
        MoveDoor( 28, 37, 1, 50 );
        MoveDoor( 37, 28, 1, 50 );
      }
      delay(3000);

      MoveDoor(  28,  62, 5000,  1);
      MoveDoor(  62, 100, 1000,  1);
			
      MoveSwitch(  0, 70, 1, 450);
      PushSwitch();
      MoveSwitch(100,   0, 1, 200);

      MoveDoor( 100, 0, 1, 400 );
      break;

    case 9:
      PlaySound(4);
      delay(800);
      MoveDoor(     0,  50,   65000,  1);
      MoveDoor(     50,100,   65000,  1);
      MoveSwitch(   0,  25,   65000,  1);
      MoveSwitch(  25,  50,   65000,  1);
      MoveSwitch(  50,  75,   65000,  1);
      MoveSwitch(  75, 100,   65000,  1);
      MoveSwitch( 100,  75,   65000,  1);
      PushSwitch();
      MoveSwitch( 100,   0, 160000,  1);
      MoveDoor(   100,  62, 160000,  1);
      MoveDoor(   62,  0,       1, 300);
      break;
    default:
      Serial.println("Error in ExecuteSequence, unknown sequence "); Serial.print( sequence, DEC);
    break;
  }
  
  delay(500);
  SetRelay(LOW);
  
  pinMode(doorServoPin, INPUT);
  pinMode(switchServoPin, INPUT);
  
  digitalWrite(doorServoPin, HIGH);
  digitalWrite(switchServoPin, HIGH);
 
  switchActive=!digitalRead(switchPin);
 
}


int counter = 0;
 
void PlaySound(int sound)
{
  digitalWrite(buzzerPin, LOW);
  pinMode(buzzerPin, OUTPUT);
 
 switch( sound )
 {
 case 0:
  beep(NOTE_A4, 500);
  beep(NOTE_A4, 500);    
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);  
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
 
  delay(500);
 
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);  
  beep(NOTE_F5, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_GS4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
 
  delay(500);
 break;
 case 1:
  beep(NOTE_A5, 500);
  beep(NOTE_A4, 300);
  beep(NOTE_A4, 150);
  beep(NOTE_A5, 500);
  beep(NOTE_GS5, 325);
  beep(NOTE_G5, 175);
  beep(NOTE_FS5, 125);
  beep(NOTE_F5, 125);    
  beep(NOTE_FS5, 250);
 
  delay(325);
 
  beep(NOTE_AS4, 250);
  beep(NOTE_DS5, 500);
  beep(NOTE_D5, 325);  
  beep(NOTE_CS5, 175);  
  beep(NOTE_C5, 125);  
  beep(NOTE_B4, 125);  
  beep(NOTE_C5, 250);  
 
  delay(350);
 break;
case 2: 
  //Variant 1
  beep(NOTE_F4, 250);  
  beep(NOTE_G5, 500);  
  beep(NOTE_F4, 350);  
  beep(NOTE_A4, 125);
  beep(NOTE_C5, 500);
  beep(NOTE_A4, 375);  
  beep(NOTE_C5, 125);
  beep(NOTE_E5, 650);
  delay(100);
 
 break;
 
 case 3:
  beep(NOTE_D4, 350);  
  beep(NOTE_CS4, 350);  
  beep(NOTE_C4, 350);  
  beep(NOTE_B3, 700);
  delay(100);
   break;
case 4:
   //Variant 2
  beep(NOTE_F4, 250);  
  beep(NOTE_G5, 500);  
  beep(NOTE_F4, 375);  
  beep(NOTE_C5, 125);
  beep(NOTE_A4, 500);  
  beep(NOTE_F4, 375);  
  beep(NOTE_C5, 125);
  beep(NOTE_A4, 650);  
 
  delay(650);
 break; 
case 5:
  beep(NOTE_E4, 150);  
  beep(NOTE_C4, 150);  
 break; 
  
default:
  beep(NOTE_C4, 150);  
  beep(NOTE_E4, 150);  
 break; 

 }

  pinMode(buzzerPin, INPUT);
  digitalWrite(buzzerPin, HIGH);
}
 
void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);
 
  //Play different LED depending on value of 'counter'
  if(counter % 2 == 0)
  {
    delay(duration);
  }else
  {
    delay(duration);
  }
 
  //Stop tone on buzzerPin
  noTone(buzzerPin);
 
  delay(50);
 
  //Increment counter
  counter++;
}
 

