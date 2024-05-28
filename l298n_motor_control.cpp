#include "l298n_motor_control.h"

L298NMotorControl::L298NMotorControl(int IN1_pin, int IN2_pin, int en_pin)
{
  in1Pin = IN1_pin;
  in2Pin = IN2_pin;
  enPin = en_pin;

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enPin, OUTPUT);

  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
}

void L298NMotorControl::sendPWM(int pwmVal)
{
  if (pwmVal > 0)
  {
    analogWrite(enPin, abs(pwmVal));
    setForwardDirection();
  }
  else if (pwmVal < 0)
  {
    analogWrite(enPin, abs(pwmVal));
    setReverseDirection();
  }
  else
  {
    analogWrite(enPin, 0);
    setHalt();
  }
}

int L298NMotorControl::getDirection()
{
  return dir;
}

void L298NMotorControl::test()
{
  for (int pwmVal = -255; pwmVal <= 255; pwmVal += 5)
  {
    sendPWM(pwmVal);
    delayMs(250);
  }
  for (int pwmVal = 255; pwmVal >= -255; pwmVal -= 5)
  {
    sendPWM(pwmVal);
    delayMs(250);
  }
}

void L298NMotorControl::setForwardDirection()
{
  dir = 1;
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
}

void L298NMotorControl::setReverseDirection()
{
  dir = 0;
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
}

void L298NMotorControl::setHalt()
{
  dir = 0;
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
}

void L298NMotorControl::delayMs(int ms)
{
  for (int i = 0; i < ms; i += 1)
  {
    delayMicroseconds(1000);
  }
}
