#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace 
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 200;

  volatile char command[2] = " ";

  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};
}

void setup()
{
  Serial.begin(115200);
  serial_flush();
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
}

void loop()
{  
  check_for_keypress();
}

void check_for_keypress() 
{
  if(Serial.available()>0) {
    command[2] = Serial.read();
    Serial.flush();
  }
  switch(command[2]) {
  case 'u':// up
    left_motor.forward(speed);
    right_motor.forward(speed);
    break;
  case 'd':// down
    left_motor.reverse(speed);
    right_motor.reverse(speed);
    break;
  case 'q': // left
    left_motor.forward(speed);
    right_motor.reverse(speed);
    break;
  case 'e': // right
    left_motor.reverse(speed);
    right_motor.forward(speed);
    break;
  case 's': // stop
    left_motor.stop();
    right_motor.stop();
    break;
  case 'a':
    action_a();
    break;
  case 'b':
    action_b();
    break;
  case 'x':
    action_x();
    break;
  case 'y':
    action_y();
    break;
  }
}

// Follow the light
void action_a()
{
  
}

// User programmed
void action_b()
{
  
}

// Run away
void action_x()
{
  
}

// Follow the light
void action_y()
{
  
}




void serial_flush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
} 


void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
