#include <IRremote.h>  
#include <Servo.h>
#include <Motor298.h>
#include "pitches.h"

#define BT_ENABLE (1)

static const int distancelimit = 33;
static const int sidedistancelimit = 12; 

int defaultSpeed = 230;


//Motor A 
int speedPinA = 5;
int speedPinB = 6;


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

void PlaySound(int sound);


Motor298 motor;

// Motor driver L298N driver
// 
// EN DIR1 DIR2
// 0    0     0  Fast stop
// 0    1     0  Forwards
// 0    0     1  Backwards
// 0    1     1  Fast stop
// 1    x     x  Free running


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

  motor.stop(255);

  Serial.println("Hoi hoi ik ben Robot versie 0.334");
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

const int buzzerPin = 10;


static long SetMotorStopTime(long intervalInMs)
{
   motor_stop_time = millis() + intervalInMs;
}

static long SetNextActionTime(long intervalInMs)
{
   next_action_time = millis() + intervalInMs;
}


bool autodrive = false;


void SetLamps(int la )
{
   pinMode(A0, OUTPUT);
   pinMode(A1, OUTPUT);
   
//  Serial.println("La is ");
 // Serial.print(la, DEC);
   
  if ( la == 0 )
  {
    digitalWrite(A0,0);
    digitalWrite(A1,0);
  }
  if ( la == 1 )
  {
    digitalWrite(A0,1);
    digitalWrite(A1,0);
  }
  if ( la == 2 )
  {
    digitalWrite(A0,0);
    digitalWrite(A1,1);
  }
  if ( la == 3 )
  {
    digitalWrite(A0,1);
    digitalWrite(A1,1);
  }
}




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

bool isStopped = false;

void SelfDrive()
{
    int dist = PingDistance();
	
	if ( millis() < next_action_time)  
	{
	  if ( action_state == 0 )
	  {
		if( dist < distancelimit) 
		{
                  if   ( ! isStopped )
                  {
		      Serial.println("STOP_1"); 
                SetLamps(0);
		      motor.stop(0); 
                    isStopped = true;
                   }
		}
		else
		{
                  Serial.println("START_1"); 
                  isStopped = false;
                SetLamps(3);
                  
                  motor.onFwd(0,180);
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
        if( dist < distancelimit) { motor.stop(255);   SetLamps(0);}

        myservo.write(135-15);
      break;
      case 3:
        dist_135 = dist;
        if(dist<distancelimit) { motor.stop(255);   SetLamps(0);}
        myservo.write(175-15);
      break;
      case 4:
        dist_180 = dist;
        if(dist<sidedistancelimit) { motor.stop(255);   SetLamps(0);}
        myservo.write(0);
      break;
      case 5:
        if ( dist_90 > dist ) dist_90 = dist;
        if( dist < distancelimit) { motor.stop(255);   SetLamps(0);}
        myservo.write(45-10);
      break;
      case 6:
        dist_45 = dist;
        if( dist < distancelimit) { motor.stop(255);   SetLamps(0);}
        myservo.write(0);
      break;      
      case 7:
        dist_0 = dist;
        if( dist < sidedistancelimit) { motor.stop(255);   SetLamps(0);}
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
            Serial.print("turn right: "); 
            motor.turnRight(255);
            SetLamps(1);
            delay(300);
            motor.stop(255);
            SetLamps(0);
        }
        else if( dist_0 <sidedistancelimit || dist_45 < distancelimit) 
        {
            Serial.print("turn left: "); 
            SetLamps(2);
            
            motor.turnLeft(255);
            delay(300);
            motor.stop(255);
            SetLamps(0);
            
        }
        else
        {
          if ( dist_90 > dist ) dist_90 = dist;
          
          if( dist < distancelimit) 
          {
            Serial.print("STOP_2"); 
            motor.stop(255);
            SetLamps(0);
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

int snd = 0;

void loop() 
{
  
  if ( millis() > motor_stop_time )
  {
    motor.stop(255);
    SetLamps(0);
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
          motor.onFwd(0,200);
          SetLamps(3);
          SetMotorStopTime(900);
        break;
        
        case IR_KEY_DOWN:
          Serial.print("IR_KEY_DOWN");
          ServoAtAngle(45);
          motor.onRev(0,200);
          SetLamps(3);
          SetMotorStopTime(900);
        break;
        
        case IR_KEY_LEFT: 
          Serial.print("IR_KEY_LEFT");
          ServoAtAngle(90);
          motor.turnLeft(255);
          SetLamps(1);
          SetMotorStopTime(400);
        break;
        
        case IR_KEY_RIGHT:
          Serial.print("IR_KEY_RIGHT");
          ServoAtAngle(135);
          motor.turnRight(255);
          SetLamps(2);
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
          motor.stop(255);
          motor.turnLeft(255);
          delay(1500);
          motor.turnRight(255);
          delay(1500);
          
          Serial.print("Servo Snelle draai");
          myservo.write( 0 ); 
          delay(500);
          myservo.write( 180 ); 
          delay(500);
          myservo.write( 0 ); 
          delay(500);
          motor.stop(255);
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
      case 'o':
          Serial.println("Lampjes testn");
      
          
         pinMode(A0, OUTPUT);
         pinMode(A1, OUTPUT);
         
         for ( int la = 0; la < 4; la++)
         {
        Serial.println("La is ");
        Serial.print(la, DEC);
 
          PlaySound(snd++);
          if ( la == 0 )
          {
            digitalWrite(A0,0);
            digitalWrite(A1,0);
          }
          if ( la == 1 )
          {
            digitalWrite(A0,1);
            digitalWrite(A1,0);
          }
          if ( la == 2 )
          {
            digitalWrite(A0,0);
            digitalWrite(A1,1);
          }
          if ( la == 3 )
          {
            digitalWrite(A0,1);
            digitalWrite(A1,1);
          }
          delay(5000);
         }
          
      break;       case 'z':
          Serial.print("Z = IR_KEY_STAR");
          autodrive = true;
          action_state = 0;
          SetNextActionTime(0);
      break;      
      case 'a':
          Serial.print("onFwd");
          motor.onFwd(0,defaultSpeed);
         //SetMotorStopTime(900);
      break;
      case 's':
          Serial.print("onRev");
          motor.onRev(0,defaultSpeed);
         // SetMotorStopTime(900);
      break;
      case 'd':
          Serial.print("turnLeft");
          motor.turnLeft(defaultSpeed);
          //SetMotorStopTime(900);
      break;
      case 'f':
          Serial.print("furnRight");
          motor.turnRight(defaultSpeed);
          //SetMotorStopTime(900);
      break;
      case 'g':
          Serial.print("revLeft");
          motor.revLeft(defaultSpeed);
          //SetMotorStopTime(900);
      break;
      case 'h':
          Serial.print("revRight");
          motor.revRight(defaultSpeed);
          //SetMotorStopTime(900);
      break;
      
      case ' ':
          motor.stop(255);
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

void beep(int note, int duration)
{
  //Play tone on buzzerPin
// AF TODO   tone(buzzerPin, note, duration);
 
  delay(duration);
 
  //Stop tone on buzzerPin
 //noTone(buzzerPin);
 
  delay(50);
}
 


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
 












