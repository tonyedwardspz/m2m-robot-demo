#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace 
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 200;

  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};
}

void setup()
{
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
}

void loop()
{  
  delay(1000);

  // Motor Usage
  left_motor.forward(speed);
  right_motor.forward(speed);

  delay(1000);

  left_motor.reverse(speed);
  right_motor.reverse(speed);

  delay(1000);

  left_motor.stop();
  right_motor.stop();


  // Distance sensor usage
  int dist_forwards = sensor.distance_forwards();
  int dist_down = sensor.distance_down();

  Serial.print("\n");
  Serial.print("\nDistance Forwards: ");
  Serial.print(dist_forwards);
  Serial.print("\nDistance Down: ");
  Serial.print(dist_down);


  // Light Sensor Usage
  int left_light = sensor.left_light_sensor();
  int center_light = sensor.center_light_sensor();
  int right_light = sensor.right_light_sensor();

  Serial.print("\nLeft: ");
  Serial.print(left_light);
  Serial.print("\nCenter: ");
  Serial.print(center_light);
  Serial.print("\nRight: ");
  Serial.print(right_light);


  // Interupt Usage
  int left_pulses = left_motor.get_pulse_count();
  int right_pulses = right_motor.get_pulse_count();

  Serial.print("\nLeft Pulse Count: ");
  Serial.print(left_pulses);
  Serial.print("\nRight Pulse Count: ");
  Serial.print(right_pulses);
}

void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
