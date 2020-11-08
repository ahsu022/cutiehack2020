
#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo wiper;
int sensor_value = 0;
int light_input = 0;
int dark = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(10, OUTPUT); //set pin 10 as output
  wiper.attach(9); // attach servo to pin 9, a PWM output necessary to control the servo
  lcd.begin(16, 2);
}

void wipe()
{
  for(int i = 0; i < 180; i+=1)
  {
    wiper.write(i);
    delay(5);
  }
  for(int j = 180; j > 0; j-=1)
  {
    wiper.write(j);
    delay(5);
  }
}

void loop() 
{
  // put your main code here, to run repeatedly
  
      sensor_value = analogRead(A1); //read input from A1
      delay(10);
      light_input = sensor_value / 4; //divide by 4, input from photoresistor is from 0-1024, LED can only take 0-255
      analogWrite(10, light_input);   //shows brightness on LED connected to pin 10
      
      if(light_input > 45)
      {
        lcd.clear();
        lcd.setCursor(0,0);             //starts out as a clean table
        lcd.print("Please Sit");
      }
      
      if((light_input < 15) && (dark == 0))            //while dark, keep checking for removal of plate
      {
        sensor_value = analogRead(A1); //read input from A0
        delay(10);
        light_input = sensor_value / 4; //divide by 4, input from photoresistor is from 0-1024, LED can only take 0-255
        analogWrite(10, light_input);   //shows brightness on LED connected to pin 11
        dark = 1;
      }
        
          if((light_input > 45) && (dark == 1))        //checks if person left the space
          {
            delay(2000);
            lcd.clear();
            lcd.print("Do Not Sit");
            lcd .setCursor(0,1);
            lcd.print("Sanitizing");
            
            for(int k = 0; k < 3; k++)      //wipe the table 3 times
            {
                wipe();
            }
            dark = 0;
            delay(2000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Please Sit");
          }
      
  
}
