#include<LiquidCrystal.h>
LiquidCrystal lcd(6,7,8,9,10,11);
int trigpin=4;
int echopin=3;
int motorpin=5;
int temp,level;
float distance,duration,voltage,millivolt,celsius;
int temp_sen() 
{
  
  temp=analogRead(A0);
  voltage=temp*5.0/1024;
  millivolt=voltage*1000;
  celsius=(millivolt-500)/10;
  Serial.print("celsius=");
  Serial.println(celsius);
}
int ults_sen() 
{
  
  digitalWrite(trigpin,HIGH);
  delay(10);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance=(duration/2)/29.1;
  Serial.print("distance=");
  Serial.println(distance);
}
int lcd_fn() 
{
  level=500-distance;
  lcd.setCursor(0,0);
  lcd.print("WATERLEVEL=");
  lcd.setCursor(12,0);
  lcd.print(level);
  lcd.setCursor(0,1);
  lcd.print("CELSIUS   =");
  lcd.setCursor(12,1);
  lcd.print(celsius);
  
}
int motor_on()
{
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("MOTOR IS ON    ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  delay(1000);
  lcd.clear();
  return lcd_fn();
}
int motor_off()
{
  delay(1000);
  if(distance<50){
    lcd.setCursor(0,0);
    lcd.print("MOTOR IS OFF     ");
    lcd.setCursor(0,1);
    lcd.print("                 ");
    delay(1000);
    lcd.clear();
    return lcd_fn();
  }
    else{
      
      lcd.setCursor(0,0);
      lcd.print("MOTOR IS OFF     ");
      lcd.setCursor(0,1);
      lcd.print("MOTOR ISOVERHEAT");
      delay(1000);
      lcd.clear();
      return lcd_fn();
    
    }

}


void setup()
{
  lcd.begin(16,2);
  pinMode(A0,INPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(motorpin,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  //Temperature Sensor
   temp_sen();
  //Ultrasonic Distance Sensor
  ults_sen();
  
  if (celsius<25)
  {    
        if (distance>50)
        {
          digitalWrite(motorpin,HIGH);
          motor_on();
        }
        else
        {
          digitalWrite(motorpin,LOW);
          motor_off();
        }
  }
  else
  {
    digitalWrite(motorpin,LOW);
    motor_off();
    
  }
  //LCD 16*2
  lcd_fn(); 

}
    
