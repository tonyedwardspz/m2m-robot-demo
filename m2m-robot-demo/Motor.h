#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor
{
  private:
    int speed = 0;
    int enable_pin = 0;
    int forward_pin = 0;
    int reverse_pin = 0;
    volatile unsigned long pulse_count = 0;

    const byte interrupt_pin_2 = 2;
    const byte interrupt_pin_3 = 3;
    
    const byte left_motor_pin_enable = 9;
    const byte left_motor_pin_forward = 8;
    const byte left_motor_pin_reverse = 7;
    const byte right_motor_pin_enable = 10;
    const byte right_motor_pin_forward = 12;
    const byte right_motor_pin_reverse = 11;
  
  public:
    static const int default_speed = 100;
    Motor(String side);
  
    void set_speed(int speed = default_speed);
    int get_speed() const { return speed; }
    void forward(int speed = default_speed);
    void reverse(int speed = default_speed);
    void stop(int speed = default_speed);
    void disable();
    
    void inc_pulse() { pulse_count++; }
    unsigned long get_pulse_count() const { return pulse_count; }
};
 
#endif

