// C++ code

//importing relevant libraries for the screen
#include <Wire.h>
#include "grove_alphanumeric_display.h"

Seeed_Digital_Tube tube;
//Setting variables for the LEDs
int redState = 0;
int greenState = 0;
int blueState = 0;
int whiteState = 0;
//Setting variables for the DIP switch
int switch1 = 0;
int switch2 = 0;
int switch3 = 0;
int switch4 = 0;
//Setting שuxiliary variables for the function and screen
int current = 0;
int prev = 0;
int counter = 0;
//LEDs inputs
const int redled = 2;
const int greenled = 3;
const int blueled = 4;
const int whiteled = 5;
//Buttons inputs
const int redPin = 8;
const int greenPin = 9;
const int bluePin = 10;
const int whitePin = 11;
//DIP switch inputs
const int switch1Pin = 6;
const int switch2Pin = 7;
const int switch3Pin = 12;
const int switch4Pin = 13;


//First random function - hardest mode //
int random_color(int i)
{
  current = random(2, 6);
 while(current ==i)
   {
   	current = random(2, 6);
   }
 return current;
}
///Second random function - moderate mode//
int easy_random_color(int i)
{
  current = random(3, 6);
 while(current ==i)
   {
   	current = random(3, 6);
   }
 return current;
}
///Third random function - easiest mode//

int super_easy_random_color(int i)
{
  current = random(4, 6);
 while(current ==i)
   {
   	current = random(4, 6);
   }
 return current;
}
//Far buttons function //
int far_buttons_Array[2] = {2,5};
int far_buttons(int i)
{
  current = far_buttons_Array[random(0, 2)];
 while(current ==i)
   {
   	current = far_buttons_Array[random(0, 2)];
   }
 return current;
}

void setup()
{
  Serial.begin(9600);
  pinMode(redled,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(blueled,OUTPUT);
  pinMode(whiteled,OUTPUT);
  
  pinMode(redPin,INPUT);
  pinMode(greenPin,INPUT);
  pinMode(bluePin,INPUT);
  pinMode(whitePin,INPUT);
  
  pinMode(switch1Pin,INPUT);
  pinMode(switch2Pin,INPUT);
  pinMode(switch3Pin,INPUT);
  pinMode(switch4Pin,INPUT);

  Wire.begin();
  tube.setTubeType(TYPE_4, TYPE_4_DEFAULT_I2C_ADDR);
  tube.setBrightness(15);
  tube.setBlinkRate(BLINK_OFF);
  tube.displayNum(0,500);
  

}


void loop()
{
  randomSeed(analogRead(0));
  redState = digitalRead(redPin);
  greenState = digitalRead(greenPin);
  blueState = digitalRead(bluePin);
  whiteState = digitalRead(whitePin);
  switch1 = digitalRead(switch1Pin);
  switch2 = digitalRead(switch2Pin);
  switch3 = digitalRead(switch3Pin);
  switch4 = digitalRead(switch4Pin);

  if (switch1 == 0 && switch2 == 0 && switch3 == 0 && switch4 == 1) 
  {
    current = random_color(prev);
    prev = current;
    digitalWrite(current, HIGH);

    while(digitalRead(current +6) == LOW)
    {
     digitalWrite(current, HIGH); 
      //continue;
    }
    digitalWrite(current, LOW);
    counter++;
    tube.displayNum(counter,500);
    Serial.print(current);
  }
  
  else if (switch1 == 1 && switch2 == 0 && switch3 == 0 && switch4 == 0)
  {
    current = super_easy_random_color(prev);
    prev = current;
    digitalWrite(current, HIGH);

    while(digitalRead(current +6) == LOW)
    {
     digitalWrite(current, HIGH); 
      //continue;
    }
    digitalWrite(current, LOW);
    counter++;
    tube.displayNum(counter,500);
    Serial.print(counter);
  }
  
  else if (switch1 == 0 && switch2 == 1 && switch3 == 0 && switch4 == 0)
  {
    current = easy_random_color(prev);
    prev = current;
    digitalWrite(current, HIGH);

    while(digitalRead(current +6) == LOW)
    {
     digitalWrite(current, HIGH); 
      //continue;
    }
    digitalWrite(current, LOW);
    counter++;
    tube.displayNum(counter,500);
    Serial.print(counter);
  }
  
  else if (switch1 == 0 && switch2 == 0 && switch3 == 1 && switch4 == 0)
  {
    Serial.print(counter);
    current = far_buttons(prev);
    prev = current;
    digitalWrite(current, HIGH);

    while(digitalRead(current +6) == LOW)
    {
     digitalWrite(current, HIGH); 
      //continue;
    }
    digitalWrite(current, LOW);
    counter++;
    tube.displayNum(counter,500);
    Serial.print(counter);
  }

  else if (switch1 == 0 && switch2 == 0 && switch3 == 0 && switch4 == 0)
  {
    counter = 0;
    tube.displayNum(counter,500);
  }
  else
  {
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);
    digitalWrite(blueled, LOW);
    digitalWrite(whiteled, LOW);
    tube.displayNum(counter,500); 
  }
}
