#include <Arduino.h>
#include <Servo.h>
#include "Button.h"

#define servo_pin 9
#define led_pin 13
#define potentiometer_pin A0
#define servo_delay 1000

bool is_rotation = false;
bool is_180 = false;

button btn(A1);
Servo my_servo;

void setup()
{
  Serial.begin(9600);
  my_servo.attach(servo_pin);
  my_servo.write(0);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
}

long rotation_millis = 0;
float rotation_delay = servo_delay;
void rotate()
{ 
  float analog = analogRead(potentiometer_pin);
  float digital = (5 / 1023.0) * analog;
  rotation_delay = digital * 1000;
 
  if (millis() - rotation_millis > rotation_delay)
  {
    Serial.println(rotation_delay);
    if (is_180 == false)
    {
      my_servo.write(180);
      is_180 = true;
    }
    else
    {
      my_servo.write(0);
      is_180 = false;
    }

    rotation_millis = millis();
  }
}

void loop()
{
  if (btn.click())
  {
    is_rotation = !is_rotation;
    digitalWrite(led_pin, is_rotation ? LOW : HIGH);
  }

  if (is_rotation)
  {
    rotate();
  }
}