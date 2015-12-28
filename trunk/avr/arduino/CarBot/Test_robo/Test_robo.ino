#include <IRremote.h>  
#include <Servo.h>
#include <Motor298.h>


Motor298 motor;

#define BT_ENABLE (1)

static const int distancelimit = 33;
static const int sidedistancelimit = 12; 

int defaultSpeed = 128;

//speedBinB	D5
//dir2PinB	D2
//dir1PinB	D3
//dir2PinA	D4
//dir1PinA	D7
//speedPinA	D6


//Motor A 
int dir1PinA = 7;
int dir2PinA = 4; 
int speedPinA = 6;

//motor B 
int dir1PinB = 3;
int dir2PinB = 2; 
int speedPinB = 5;


const int USServoPin = 9;
const int USTriggerPin = 12;
const int USEchoPin = 13;

const int IRRecvPin = 8;

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

IRrecv irrecv(IRRecvPin);
Servo myservo;


const int LED_PIN = 13;
int randomValue = 0;
// 1000 ms of no data transmission required before and after the escape sequence
int cmdDelay = 1000; 
// Change these two paramaters to anything you want
int pin = 1234;
char* name = "AutoRobot";


// Motor driver L298N driver
// 
// EN DIR1 DIR2
// 0    0     0  Fast stop
// 0    1     0  Forwards
// 0    0     1  Backwards
// 0    1     1  Fast stop
// 1    x     x  Free running

void motor_off();
void motor_init();
void motor_forwards(int speed);
void motor_backwards(int speed);
void motor_turnleft(int speed);
void motor_turnaround(int speed);
void motor_turnright(int speed);


void motor_init()
{
  // setup motor
  pinMode (dir1PinA, OUTPUT); 
  pinMode (dir2PinA, OUTPUT); 
  pinMode (speedPinA, OUTPUT); 
  
  pinMode (dir1PinB, OUTPUT); 
  pinMode (dir2PinB, OUTPUT); 
  pinMode (speedPinB, OUTPUT); 

  motor_off();
}


void motor_off()
{
  Serial.print(" <<MTO>> "); 
  digitalWrite (speedPinA, LOW); 
  digitalWrite (speedPinB, LOW);
  digitalWrite (dir1PinA , LOW); 
  digitalWrite (dir2PinA, LOW); 
  digitalWrite (dir1PinB, LOW); 
  digitalWrite (dir2PinB, LOW); 
}

void motor_faststop()
{
  Serial.print(" <<MFS>> "); 
  digitalWrite (speedPinA, HIGH); 
  digitalWrite (speedPinB, HIGH);
  digitalWrite (dir1PinA , LOW); 
  digitalWrite (dir2PinA, LOW); 
  digitalWrite (dir1PinB, LOW); 
  digitalWrite (dir2PinB, LOW); 
}

void motor_forwards(int speed)
{
  Serial.print(" <<MTF>> "); 
  
  analogWrite (speedPinA, speed); 
  analogWrite (speedPinB, speed);
  digitalWrite (dir1PinA, LOW); 
  digitalWrite (dir2PinA, HIGH); 
  digitalWrite (dir1PinB, LOW); 
  digitalWrite (dir2PinB, HIGH);
}

void motor_backwards(int speed)
{
  Serial.print(" <<MTB>> "); 
  
  analogWrite (speedPinA, speed); 
  analogWrite (speedPinB, speed);
  digitalWrite (dir1PinA , HIGH); 
  digitalWrite (dir2PinA, LOW); 
  digitalWrite (dir1PinB, HIGH); 
  digitalWrite (dir2PinB, LOW);  
}

void motor_turnleft(int speed)
{
  Serial.print(" <<MTL>> "); 
  analogWrite (speedPinA, LOW); 
  analogWrite (speedPinB, speed);
  digitalWrite (dir1PinA , HIGH); 
  digitalWrite (dir2PinA, LOW); 
  digitalWrite (dir1PinB, HIGH); 
  digitalWrite (dir2PinB, LOW);  
}

void motor_turnaround(int speed)
{
  Serial.print(" <<MTA>> "); 
  analogWrite (speedPinA, speed); 
  analogWrite (speedPinB, speed);
  digitalWrite (dir1PinA , HIGH); 
  digitalWrite (dir2PinA, LOW); 
  digitalWrite (dir1PinB, LOW); 
  digitalWrite (dir2PinB, HIGH);  
}


void motor_turnright(int speed)
{
  Serial.print(" <<MTR>> "); 
  
  analogWrite (speedPinA, speed); 
  analogWrite (speedPinB, LOW);
  digitalWrite (dir1PinA , HIGH); 
  digitalWrite (dir2PinA, LOW); 
  digitalWrite (dir1PinB, HIGH); 
  digitalWrite (dir2PinB, LOW); 
}


void setup()
{  
  // setup bluetooth modile
  pinMode(LED_PIN, OUTPUT);
  // Turn on LED to signal programming start
  digitalWrite(LED_PIN, HIGH);

  Serial.begin(9600); 
  
  #if ( BT_ENABLE == 1 )
    delay(cmdDelay);
    Serial.print("AT");
    delay(cmdDelay);
    Serial.print("AT+PIN"); 
    Serial.print(pin); 
    delay(cmdDelay);
    Serial.print("AT+NAME");
    Serial.print(name); 
    delay(cmdDelay);
  #endif
  
  // Turn off LED to signal programming end
  digitalWrite(LED_PIN, LOW); 
  
  myservo.attach(USServoPin);
  myservo.write(0);
  delay(150);
  myservo.write(90-15);
  delay(150);

  pinMode (USTriggerPin, OUTPUT);
  pinMode (USEchoPin, INPUT) ;

  irrecv.enableIRIn(); // Start the receiver

  motor_init();

  Serial.println("Hoi hoi ik ben Robot versie 0.333");
  Serial.println("dus zeg het maar !");
}



int idx = 0;
int cnt = 0;
int inp = 0;


static const unsigned int NO_MOTOR_STOP = 4294967295;

static unsigned long motor_stop_time = NO_MOTOR_STOP;
static unsigned long last = millis();
static decode_results results;
static unsigned long next_action_time  = NO_MOTOR_STOP;


void ServoAtAngle(int angle)
{
  Serial.println("Set servo to angle ");
  Serial.print(angle, DEC);
  myservo.write( angle ); 
}


const unsigned long IR_KEY_0 = 0xFF4AB5;
const unsigned long IR_KEY_1 = 0xFF6897;
const unsigned long IR_KEY_2 = 0xFF9867;
const unsigned long IR_KEY_3 = 0xFFB04F;
const unsigned long IR_KEY_4 = 0xFF30CF;

const unsigned long IR_KEY_UP    = 0xFF629D;
const unsigned long IR_KEY_DOWN  = 0xFFA857;
const unsigned long IR_KEY_LEFT  = 0xFF22DD;
const unsigned long IR_KEY_RIGHT = 0xFFC23D;
const unsigned long IR_KEY_OK    = 0xFF02FD;
const unsigned long IR_KEY_STAR  = 0xFF42BD;


static long SetMotorStopTime(long intervalInMs)
{
   motor_stop_time = millis() + intervalInMs;
}

static long SetNextActionTime(long intervalInMs)
{
   next_action_time = millis() + intervalInMs;
}


bool autodrive = false;


int PingDistance()
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
     //Serial.println("out of range");
   }
   else 
   {
     //Serial.println(distance);
   }
   return (distance + 0.5);
}


static int action_state = -1;  


static int dist_180;
static int dist_135;
static int dist_90;
static int dist_45;
static int dist_0;

int inrange = 0;

void SelfDrive()
{
    int dist = PingDistance();
	
	if ( millis() < next_action_time)  
	{
	  if ( action_state == 0 )
	  {
		if( dist < distancelimit) 
		{
			inrange++;
			if (inrange >  2 )
			{
				Serial.println("STOP_1"); 
				motor_off();
				inrange = 0;
			}
		}
		else
		{
            Serial.println("START_1"); 
            motor_forwards(255);
		}
	  }
	  return;
	}
  
    
    switch ( action_state )
    {
	  case 0:
	  
      break;

		
      case 1:
        myservo.write(90-15);
      break;
      case 2:
        dist_90 = dist;
        if( dist < distancelimit) motor_off();
        myservo.write(135-15);
      break;
      case 3:
        dist_135 = dist;
        if(dist<distancelimit) motor_off();
        myservo.write(175-15);
      break;
      case 4:
        dist_180 = dist;
        if(dist<sidedistancelimit) motor_off();
        myservo.write(0);
      break;
      case 5:
        if ( dist_90 > dist ) dist_90 = dist;
        if( dist < distancelimit) motor_off();
        myservo.write(45-10);
      break;
      case 6:
        dist_45 = dist;
        if( dist < distancelimit) motor_off();
        myservo.write(0);
      break;      
      case 7:
        dist_0 = dist;
        if( dist < sidedistancelimit) motor_off();
        myservo.write(90-15);
        
      break;       
      case 8:
        Serial.print("dist_0:   "); Serial.println (dist_0, DEC);
        Serial.print("dist_45:  "); Serial.println (dist_45, DEC);
        Serial.print("dist_90:  "); Serial.println (dist_90, DEC);
        Serial.print("dist_135: "); Serial.println (dist_135, DEC);
        Serial.print("dist_180: "); Serial.println (dist_180, DEC);
        
        
        if( dist_180 <sidedistancelimit || dist_135<distancelimit) 
        {
			Serial.print("turn left: "); 
            motor_turnleft(255);
            delay(200);
            motor_off();
        }
        else if( dist_0 <sidedistancelimit || dist_45 < distancelimit) 
        {
          Serial.print("turn right: "); 
            motor_turnright(255);
            delay(200);
            motor_off();
        }
        else
        {
          if ( dist_90 > dist ) dist_90 = dist;
          
          if( dist < distancelimit) 
          {
            Serial.print("STOP_2"); 
            motor_off();
          }
          else
          {
            //Serial.print("START!!!: "); 
            //motor_forwards(255);
          }
        }
		
        break;       
    }
    
    action_state++;
    if ( action_state > 8 ) action_state=0;  
    Serial.print("action state set to  "); Serial.println (action_state, DEC);
	SetNextActionTime(200);
}

void loop() 
{
  if ( false)
  {  
  while ( true )
  {
    pinMode(3,OUTPUT);
    for (int i=0;i<3000;i++)
    {
      delay(1);
        digitalWrite (3, LOW);          
        delay(1);
        digitalWrite (3, HIGH);          
    }
    analogWrite(3, 128);
    delay(10000);
    
  }
  

    
  while (true)
  {
      ServoAtAngle(90);
      delay(10000);
      motor_forwards(defaultSpeed);
      
      ServoAtAngle(45);
      delay(10000);
      motor_backwards(defaultSpeed);
      
      ServoAtAngle(0);
      delay(10000);
      motor_turnleft(defaultSpeed);

      ServoAtAngle(180);
      delay(10000);
      motor_turnright(defaultSpeed);
      
      defaultSpeed +=10;
      if ( defaultSpeed > 255 ) defaultSpeed = 105;
      
  }
  }
  
  if ( millis() > motor_stop_time )
  {
    motor_off();
    autodrive = false;
    motor_stop_time = NO_MOTOR_STOP;
  }
  
  if (irrecv.decode(&results)) 
  {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250) 
    {
      Serial.print("He er is op de afstandsbediening gedrukt, hex code: ");
      //dump(&results);
      Serial.println (results.value, HEX); //display HEX
       
 
      switch( results.value)
      {
        case 0xFF4AB5:
          Serial.print("Servo langzamer ");
          for ( idx = 0; idx < 180; idx += 10 ) 
          {
            myservo.write( idx ); 
            delay(50);
          }
          for ( idx = 180; idx > 0; idx -= 10 ) 
          {
            myservo.write( idx ); 
            delay(50);
          }
          myservo.write( 90 ); 
        break;
        
        case IR_KEY_UP:
          Serial.print("IR_KEY_UP");
          ServoAtAngle(0);
          motor_forwards(255);
          SetMotorStopTime(900);
        break;
        
        case IR_KEY_DOWN:
          Serial.print("IR_KEY_DOWN");
          ServoAtAngle(45);
          motor_backwards(255);
          SetMotorStopTime(900);
        break;
        
        case IR_KEY_LEFT: 
          Serial.print("IR_KEY_LEFT");
          ServoAtAngle(90);
          motor_turnleft(255);
          SetMotorStopTime(400);
        break;
        
        case IR_KEY_RIGHT:
          Serial.print("IR_KEY_RIGHT");
          ServoAtAngle(135);
          motor_turnright(255);
          SetMotorStopTime(400);
        break;

        case IR_KEY_OK:
          Serial.print("IR_KEY_OK");
          autodrive = false;
          SetMotorStopTime(0);
        break;

        case IR_KEY_STAR:
          Serial.print("IR_KEY_STAR");
          autodrive = true;
          action_state = 0;
          SetNextActionTime(0);
        break;
        
        case 0xFF18E7: 
          ServoAtAngle(180);
        break;
        
        case 0xFF5AA5: 
          motor_off();
          motor_turnaround(255);
          
          Serial.print("Servo Snelle draai");
          myservo.write( 0 ); 
          delay(500);
          myservo.write( 180 ); 
          delay(500);
          myservo.write( 0 ); 
          delay(500);
          motor_off();
        break;
      } 
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
      case 'z':
          Serial.print("Z = IR_KEY_STAR");
          autodrive = true;
          action_state = 0;
          SetNextActionTime(0);
      break;      
      case 'a':
          motor_forwards(defaultSpeed);
         //SetMotorStopTime(900);
      break;
      case 's':
          motor_backwards(defaultSpeed);
         // SetMotorStopTime(900);
      break;
      case 'd':
          motor_turnleft(defaultSpeed);
          //SetMotorStopTime(900);
      break;
      case 'f':
          motor_turnright(defaultSpeed);
          //SetMotorStopTime(900);
      break;
      
      case ' ':
          motor_off();
          //SetMotorStopTime(900);
      break;

      case '+':
        defaultSpeed += 10;
        if ( defaultSpeed >255) defaultSpeed = 255;
        Serial.println("Increased default speed to ");
        
        Serial.print(defaultSpeed, DEC);
      pinMode (speedPinB, OUTPUT); 
      pinMode (speedPinA, OUTPUT); 
        digitalWrite (speedPinA, HIGH); 
        digitalWrite (speedPinB, HIGH);          
        digitalWrite (5, HIGH);          

        analogWrite (speedPinA, defaultSpeed); 
        analogWrite (speedPinB, defaultSpeed);          
        analogWrite (5, defaultSpeed);          
      break;

      case '-':
        defaultSpeed -= 10;
        if ( defaultSpeed <0 ) defaultSpeed = 0;
        Serial.println("Decreased default speed to ");
        Serial.print(defaultSpeed, DEC);
        analogWrite (speedPinA, defaultSpeed); 
        analogWrite (speedPinB, defaultSpeed);          
      break;
      
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
        Serial.print("Servo langzamer ");
        for ( idx = 0; idx < 180; idx += 10 ) 
        {
          myservo.write( idx ); 
          delay(50);
        }
        for ( idx = 180; idx > 0; idx -= 10 ) 
        {
          myservo.write( idx ); 
          delay(50);
        }
        myservo.write( 90 ); 
        break;
      case '9':
        Serial.print("Servo Snelle draai");
        myservo.write( 0 ); 
        delay(500);
        myservo.write( 180 ); 
        delay(500);
        myservo.write( 0 ); 
        delay(500);
        break;

      case 'q':
        Serial.println("Motor right backwards");
        break;
      case 'w':
        Serial.println("Motor right forwards");
        break;
      case 'e':
         Serial.println("Motor left backwards");
        break;
      case 'r':
         Serial.println("Motor left forwards");
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
          SetMotorStopTime(0);
             Serial.println("Unknown command");
     break;
    }
  }
  
  if ( autodrive )
  {
    SelfDrive();
  }
}














