#include <IRremote.h>  
#include <Servo.h>

//const int LED_PIN = 13;
const int ServoSwitchPin = 13;
const int ServoDoorPin = 12;
const int cmdDelay = 1000; 
const int BTpin = 1234;
const char* name = "GrapBox";

const int door_angle_0 = 35;
const int switch_angle_0 = 65;


int inp = 0;
Servo servoDoor;
Servo servoSwitch;

void ServoDoorToAngle(int angle)
{
  Serial.println("Set door servo to angle ");
  Serial.print(angle, DEC);
  servoDoor.write( angle ); 
}

void ServoSwitchToAngle(int angle)
{
  Serial.println("Set switch servo to angle ");
  Serial.print(angle, DEC);
  servoSwitch.write( angle ); 
}


void setup()
{  
  //digitalWrite(LED_PIN, HIGH);
  Serial.begin(9600); 
  //delay(cmdDelay);
  //Serial.print("AT");
  //delay(cmdDelay);
  //Serial.print("AT+PIN"); 
  //Serial.print(BTpin); 
  //delay(cmdDelay);
  //Serial.print("AT+NAME");
  //Serial.print(name); 
  //delay(cmdDelay);
  // Turn off LED to signal programming end
  //digitalWrite(LED_PIN, LOW); 

  servoDoor.attach(ServoDoorPin);
  servoSwitch.attach(ServoSwitchPin);
  
  ServoDoorToAngle(door_angle_0);
  ServoSwitchToAngle(switch_angle_0);
  delay(300);


  Serial.println("Grapbox test applicatie");
  Serial.println("dus zeg het maar !");
}



int i;


void loop() 
{
  
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
      case '6': 
      case '7': 
      {
        int angle = door_angle_0 + (inp - '0' - 1)  * 10;  
        Serial.println("Set servo to angle ");
        Serial.print(angle, DEC);
        servoDoor.write( angle ); 
        
        angle = switch_angle_0 + (inp - '0' - 1)  * 15;  
         ServoSwitchToAngle(angle);
        delay(200);
    }
      break; 
      case '0': 
      {
        Serial.println("Klapperen ");
        for (int i=0;i<30;i++)
        {
          servoDoor.write( door_angle_0 + 50 ); 
          delay(50);          
          servoDoor.write( door_angle_0 + 10 ); 
          delay(50);          
        }
          servoDoor.write( door_angle_0 ); 
        

      }
      break;   
      case 'a': 
      case 'A': 
      {
        Serial.println("T0 ");
        servoDoor.write( door_angle_0 + 60 ); 
        delay(250);          
        servoSwitch.write( switch_angle_0 + 7 * 15 ); 
       delay(1000);          
        servoSwitch.write( switch_angle_0  ); 
        delay(500);          
        servoDoor.write( door_angle_0 ); 
        delay(500);          
      }
      break; 
      case 'b': 
      case 'B': 
      {
        Serial.println("T1 ");
        for (int i=0;i<20;i++)
        {
          servoDoor.write( door_angle_0 + 50 ); 
          delay(50);          
          servoDoor.write( door_angle_0 + 10 ); 
          delay(50);          
        }
        servoDoor.write( door_angle_0 + 60 ); 


        for (i=0;i<4;i++)
        {
          delay(150);          
          servoSwitch.write( switch_angle_0 + i * 15 ); 
        }
        for (i=0;i<4;i++)
        {
          delay(50);          
          servoSwitch.write( switch_angle_0 + 60 - i * 15 ); 
        }
        servoSwitch.write( switch_angle_0 + 2 * 15 ); 
       delay(100);          
        servoSwitch.write( switch_angle_0 + 7 * 15 ); 
              delay(1000);          
        servoSwitch.write( switch_angle_0); 
              delay(500);          
        servoDoor.write( door_angle_0 ); 
              delay(500);          
      }
      break;   
      default:
             Serial.println("Unknown command");
     break;
    }
  }
}

 

