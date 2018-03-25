#include "Arduino.h"
#include "Motor.h"

namespace {
  static const byte max_speed_value = 255;
}

Motor::Motor(String side)
{
  // Setup the pins dependent upon which motor is instantiated
  if (side == "left") {
    pinMode(left_motor_pin_enable, OUTPUT);
    pinMode(left_motor_pin_forward, OUTPUT);
    pinMode(left_motor_pin_reverse, OUTPUT);

    enable_pin = left_motor_pin_enable;
    forward_pin = left_motor_pin_forward;
    reverse_pin = left_motor_pin_reverse;
  } else if (side == "right"){
    pinMode(right_motor_pin_enable, OUTPUT);
    pinMode(right_motor_pin_forward, OUTPUT);
    pinMode(right_motor_pin_reverse, OUTPUT);

    enable_pin = right_motor_pin_enable;
    forward_pin = right_motor_pin_forward;
    reverse_pin = right_motor_pin_reverse;
  }
  disable();
}

void Motor::set_speed(int _speed)
{
  speed = _speed;
  analogWrite(enable_pin, speed);
}

void Motor::forward(int speed)
{
  set_speed(speed);
  digitalWrite(forward_pin, HIGH);
  digitalWrite(reverse_pin, LOW);
}

void Motor::reverse(int speed)
{
  set_speed(speed);
  digitalWrite(forward_pin, LOW);
  digitalWrite(reverse_pin, HIGH);
}

void Motor::stop(int speed)
{
  set_speed(speed);
  digitalWrite(forward_pin, HIGH);
  digitalWrite(reverse_pin, HIGH);    
}

void Motor::disable()
{
  set_speed(0);
  digitalWrite(forward_pin, LOW);
  digitalWrite(reverse_pin, LOW);      
}
