int MotorRight1=5;
int MotorRight2=6;
int MotorLeft1=10;
int MotorLeft2=11;
const int SensorLeft = 7;      //左感測器輸入腳
const int SensorMiddle= 4 ;    //中感測器輸入腳
const int SensorRight = 3;     //右感測器輸入腳
int SL;    //左感測器狀態
int SM;    //中感測器狀態
int SR;    //右感測器狀態

void setup()
{  
  Serial.begin(9600);
  pinMode(MotorRight1, OUTPUT);  // 腳位 8 (PWM)
  pinMode(MotorRight2, OUTPUT);  // 腳位 9 (PWM)
  pinMode(MotorLeft1,  OUTPUT);  // 腳位 10 (PWM) 
  pinMode(MotorLeft2,  OUTPUT);  // 腳位 11 (PWM)
  pinMode(SensorLeft, INPUT); //定義左感測器
  pinMode(SensorMiddle, INPUT);//定義中感測器
  pinMode(SensorRight, INPUT); //定義右感測器
}

void loop() 
 {
 SL = digitalRead(SensorLeft);
 SM = digitalRead(SensorMiddle);
 SR = digitalRead(SensorRight);
                   
       if (SM == HIGH)//中感測器在黑色區域
       { 
          if (SL == LOW & SR == HIGH) // 左黑右白, 向左轉彎
          {  
             digitalWrite(MotorRight1,LOW);
             digitalWrite(MotorRight2,HIGH);
             analogWrite(MotorLeft1,0);
             analogWrite(MotorLeft2,80);
          } 
          else if (SR == LOW & SL == HIGH) //左白右黑, 向右轉彎
          {  
             analogWrite(MotorRight1,0);//右轉
             analogWrite(MotorRight2,80);
             digitalWrite(MotorLeft1,LOW);
             digitalWrite(MotorLeft2,HIGH);
          }
         else  // 兩側均為白色, 直進
          { 
             digitalWrite(MotorRight1,LOW);
             digitalWrite(MotorRight2,HIGH);
             digitalWrite(MotorLeft1,LOW);
             digitalWrite(MotorLeft2,HIGH);
             analogWrite(MotorLeft1,200);
             analogWrite(MotorLeft2,200);
             analogWrite(MotorRight1,200);
             analogWrite(MotorRight2,200);
         }      
       } 
       else // 中感測器在白色區域
      {  
         if (SL == LOW & SR == HIGH)// 左黑右白, 快速左轉 
        {  
            digitalWrite(MotorRight1,LOW);
            digitalWrite(MotorRight2,HIGH);
            digitalWrite(MotorLeft1,LOW);
            digitalWrite(MotorLeft2,LOW);
        }
         else if (SR == LOW & SL == HIGH) // 左白右黑, 快速右轉
        {  
           digitalWrite(MotorRight1,LOW);
           digitalWrite(MotorRight2,LOW);
           digitalWrite(MotorLeft1,LOW);
           digitalWrite(MotorLeft2,HIGH);
        }
         else // 都是白色, 停止
        {    
        digitalWrite(MotorRight1,HIGH);
        digitalWrite(MotorRight2,LOW);
        digitalWrite(MotorLeft1,HIGH);
        digitalWrite(MotorLeft2,LOW);;
        }}}
