#include <Servo.h> 
#include <avr/sleep.h>


const int doorServoStartPos = 35;
const int doorServoEndPos = doorServoStartPos + 60;

const int switchServoStartPos = 65;
const int switchServoEndPos = switchServoStartPos + 105;

#define DBG_ON 1
#define DOORPOS(a) ( doorServoStartPos + ((doorServoEndPos-doorServoStartPos)*a) / 100)
#define SWITCHPOS(a) ( switchServoStartPos + ((switchServoEndPos-switchServoStartPos)*a) / 100)


Servo switchServo;
Servo doorServo;	 
int boxon=1;
 
static void MoveServo( Servo& servo, int fromAngle, int toAngle, int usec, int postDelayInMs );
static void ExecuteSequence( int sequence );

int sequence = 0;
  
void setup() 
{ 
	switchServo.attach(13);  // attaches the servo on pin 13 to the servo object (PB5)
	doorServo.attach(12);  // attaches the servo on pin 12 to the servo object (PB4)
	pinMode(8, OUTPUT);   // For the MOSFET
	pinMode(2, INPUT);    // For the switch interrupt
	digitalWrite(2, HIGH);
	switchServo.write(SWITCHPOS(0));
	doorServo.write(DOORPOS(0));
	delay(600);
	digitalWrite(8, HIGH);
	delay(300);
	digitalWrite(8, LOW);


	// Put all unused pins to input high to save power.
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

  #ifdef DBG_ON
	Serial.begin(9600);  
	Serial.println("DP   0 "); Serial.print( DOORPOS(0), DEC);
	Serial.println("DP  28 "); Serial.print( DOORPOS(28), DEC);
	Serial.println("DP  37 "); Serial.print( DOORPOS(37), DEC);
	Serial.println("DP  62 "); Serial.print( DOORPOS(62), DEC);
	Serial.println("DP 100 "); Serial.print( DOORPOS(100), DEC);
	
	Serial.println("SP   0 "); Serial.print( SWITCHPOS(0), DEC);
	Serial.println("SP  50 "); Serial.print( SWITCHPOS(50), DEC);
	Serial.println("SP  80 "); Serial.print( SWITCHPOS(80), DEC);
	Serial.println("SP 100 "); Serial.print( SWITCHPOS(100), DEC);
	 
   #else
	  //External interrupt INT0
	  EICRA=0;   //The low level of INT0 generates an interrupt request
	  EIMSK=1;   //External Interrupt Request 0 Enable
  #endif
} 



int inp = 0;
  

// Main loop  
void loop() 
{ 
  #ifdef DBG_ON
	  if (Serial.available() > 0) 
	  {
		// read the incoming byte:
		inp = Serial.read();
		
		switch ( inp )
		{
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
		delay(100);
	  }
  #else
	  if(!boxon) //boxon should actually be called boxoff. Did a mistake here.
	  {
		delay(500);
		digitalWrite(8, HIGH);
		//seq = int(random(0,10)); //If you want random...
		ExecuteSequence(sequence++);	

		delay(100);
		digitalWrite(8, LOW);
		boxon=digitalRead(2);
	  }
	  else
	  {
		//Set sleep mode, turn off MOSFET and servos
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_enable();
		pinMode(12, INPUT);
		digitalWrite(12, HIGH);
		pinMode(13, INPUT);
		digitalWrite(13, HIGH);
		PRR = 255;
		MCUCR |= (1<<BODS) | (1<<BODSE);
		MCUCR &= ~(1<<BODSE);    
		EIMSK=1;
		sleep_mode();
		// ZZZzzz...
		sleep_disable();     //Awake again...
		PRR = 0;
		pinMode(12, OUTPUT);
		pinMode(13, OUTPUT);
	  }
	  boxon=digitalRead(2); //If pin 2 is low, box is on and bonxon=flase
	#endif
}



static void MoveServo( Servo& servo, int fromAngle, int toAngle, int usec, int postDelayInMs )  
{
	usec *= 6;
	
	if(fromAngle <= toAngle)
	{
		for(int pos = fromAngle; pos < toAngle; pos += 1)
		{
			servo.writeMicroseconds(pos);
			delayMicroseconds(usec);
		}
	}
	else
	{
		for(int pos = fromAngle; pos>=toAngle; pos-=1)
		{
			servo.writeMicroseconds(pos);
			delayMicroseconds(usec); 
		}
	}
	delay( postDelayInMs );
}



ISR(INT0_vect)   // Step rising edge interrupt. Switch flipped.
{
  EIMSK=0;   //Turn off interrupt
  boxon=digitalRead(2);  //Read the switch a couple of times to avoid a nasty non working thing some times.
  boxon=digitalRead(2);
  boxon=digitalRead(2);
  boxon=digitalRead(2);
  boxon=digitalRead(2);
  boxon=digitalRead(2);
  boxon=digitalRead(2);
  boxon=digitalRead(2);
  boxon=digitalRead(2);
  boxon=digitalRead(2);
}



void MoveDoor(int fromAngle, int toAngle, int innerWaitInuSec, int outerWaitInmSec)
{
  MoveServo( doorServo, DOORPOS(fromAngle),DOORPOS(toAngle),innerWaitInuSec, outerWaitInmSec);
}

void MoveSwitch(int fromAngle, int toAngle, int innerWaitInuSec, int outerWaitInmSec)
{
  MoveServo( switchServo, SWITCHPOS(fromAngle),SWITCHPOS(toAngle),innerWaitInuSec, outerWaitInmSec);
}



static void ExecuteSequence(int sequence)
{
	sequence = sequence % 10;
	#ifdef DBG_ON
		Serial.println("ExecuteSequence "); Serial.print( sequence, DEC);
	#endif
	
	switch ( sequence )
	{
		case 0:
			delay(700);
			MoveDoor(    0, 62, 3000, 1000);
			MoveDoor(   62,  0,  500, 1000);
			MoveDoor(    0,100, 1000,    0);
			
			MoveSwitch(   0, 50, 1800,    0);
			MoveSwitch(  50,100,  500,  100);
			MoveSwitch( 100,  0,  500,    0);
			
			MoveDoor(  100,  0,  500,    0);
			break;
		case 1:
			delay(800);
			
			MoveDoor(    0, 28, 3000,    0);		
			MoveDoor(   28, 37,    1,  120);
			
			MoveDoor(   37, 28,    1,  120);
			MoveDoor(   28, 37,    1,  120);
			MoveDoor(   37, 28,    1,  120);
			MoveDoor(   28, 37,    1,  120);
			MoveDoor(   37, 28,    1,  120);

			MoveDoor(   28,  0, 3000,    0);
			MoveDoor(    0, 62, 3000, 1000);
			MoveDoor(   62,100, 1000,    0);
			
			MoveSwitch( 0,   50, 1800,   0);
			MoveSwitch( 50, 100,  500, 100);
			MoveSwitch( 100,  0,  500,   0);
			MoveDoor(   100,  0,  500,   0);
			break;
		case 2:
			delay(50);
			MoveDoor(    0,100,    1,    1);
			MoveSwitch(  0,100,    1,  450);
			MoveSwitch(100,  0,    1,  200);
			MoveDoor(  100,  0,    1,  400);
			break;
		case 3:
			delay(500);
			MoveDoor(     0,100,   1,    1);
			MoveSwitch(   0, 70,   1,  450);
			MoveSwitch(  70,100,3000,    1);
			MoveSwitch( 100,  0,   1,  200);
			MoveDoor(   100,  0,   1,  400);
			break;
		case 4:
			delay(1000);
			
			MoveDoor(    0,100,    1,    1);
			MoveSwitch(  0,100,    1,  450);
			
			for (int i =0; i<5; i++ )
			{
				MoveSwitch( 100, 70, 1, 110 );
				MoveSwitch(  70,100, 1, 110 );
			}
			
			MoveSwitch( 100, 0, 1, 200);
			MoveDoor(   100, 0, 1, 400);
			
			break;
		case 5:
			delay(1500);
			//------(     ,   ,     ,     );
			MoveDoor(   0, 100, 1, 1);
			MoveSwitch(  0, 100, 1, 450);
			MoveDoor(  100, 0, 1000, 2000);
			MoveDoor(    0, 100, 1000, 2000);
			MoveSwitch( 100, 0, 1, 200);
			MoveDoor(   100, 0, 1, 400);
			break;
		case 6:
			delay(500);
			MoveDoor(0, 62, 1,200);
			
			for (int i =0; i<10; i++ )
			{
				MoveDoor( 28, 62, 1, 100 );
				MoveDoor( 62, 28, 1, 100 );
			}
			
			MoveDoor(62, 0, 1, 200);
			MoveDoor(0, 100, 1, 1);
			MoveSwitch( 0, 100, 1, 450);
			MoveSwitch( 100, 0, 1, 200);
			MoveDoor(100, 0, 1, 400);
			break;
		case 7:
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
			
			MoveSwitch(   0, 100, 1, 450);
			MoveSwitch( 100,   0, 1, 200);
			
			MoveDoor(  100,   0, 1, 400);
			
			break;
		case 8:
			delay(1000);
			
			MoveDoor( 0,  62, 2000,500);
			MoveDoor( 62, 28, 1000,  1);
			
			for (int i =0; i<10; i++ )
			{
				MoveDoor( 28, 37, 1, 50 );
				MoveDoor( 37, 28, 1, 50 );
			}
			
			MoveDoor(  28,  62, 5000,  1);
			MoveDoor(  62, 100, 1000,  1);
			
			MoveSwitch(  0, 100, 1, 450);
			MoveSwitch(100,   0, 1, 200);

			MoveDoor( 100, 0, 1, 400 );

			break;
		case 9:
			delay(800);
			MoveDoor(     0, 100,  3000,  1);
			MoveSwitch(   0, 100,  3000,  1);
			MoveSwitch( 100,   0,  3000,  1);
			
			MoveDoor(   100,  62,  3000,  1);
			MoveDoor(   62,  0,       1, 300);
			break;
		default:
			#ifdef DBG_ON
				Serial.println("Error in ExecuteSequence, unknown sequence "); Serial.print( sequence, DEC);
			#endif		
			break;
	}
}


