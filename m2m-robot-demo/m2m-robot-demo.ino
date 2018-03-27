#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace 
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;
  
  auto speed = 200;
  auto light_speed = 150;
  
  volatile char command[2] = " ";
  unsigned long start_time = 0;

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
    left_motor.reverse(speed);
    right_motor.forward(speed);
    break;
  case 'e': // right
    left_motor.forward(speed);
    right_motor.reverse(speed);
    break;
  case 's': // stop
    left_motor.stop();
    right_motor.stop();
    break;
  case 'a':
    start_time = millis();
    action_a();
    break;
  case 'b':
    action_b();
    break;
  case 'x':
    start_time = millis();
    action_x();
    break;
  case 'y':
    start_time = millis();
    action_y();
    break;
  }
}

// Follow the light for 20 seconds
void action_a()
{
  while (millis() - start_time <= 20000){
    // Do stuff
    
    if(sensor.center_light_sensor() < sensor.right_light_sensor() && 
       sensor.center_light_sensor() < sensor.left_light_sensor()){
        
      left_motor.forward(light_speed);
      right_motor.forward(light_speed);
      delay(100);
    }
    else if(sensor.left_light_sensor() < sensor.center_light_sensor()){
      left_motor.reverse(light_speed);
      right_motor.forward(light_speed);
      delay(100);
    }
    else if(sensor.right_light_sensor() < sensor.center_light_sensor()){
      left_motor.forward(light_speed);
      right_motor.reverse(light_speed);
      delay(100);
    }

  }
  left_motor.stop();
  right_motor.stop();
}

// User programmed
void action_b()
{
  
}

// Run away
void action_x()
{
  while (millis() - start_time <= 10000){
    if (sensor.distance_forwards() < 15){
      left_motor.reverse(speed);
      right_motor.reverse(speed);
    } else {
      left_motor.forward(speed);
      right_motor.forward(speed);
    }
  }
  left_motor.stop();
  right_motor.stop();
}

// Avoid obstacles
void action_y()
{
  while (millis() - start_time <= 20000){
    // Do stuff
    delay(50);
    if (sensor.distance_forwards() > 15){
      left_motor.forward(speed);
      right_motor.forward(speed);
    } else {
      left_motor.reverse(speed);
      right_motor.reverse(speed);
      delay(400);
      left_motor.forward(speed);
      right_motor.reverse(speed);
      delay(1000);
    }
  }
  left_motor.stop();
  right_motor.stop();
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
