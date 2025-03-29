// esp32 board version must be 2.0.11
// otherwise the code will not compile


#include "BluetoothSerial.h"
#include <Arduino.h>
BluetoothSerial serialBT;

// Bluetooth signal Store in this variable
char btSignal;

// initial Speed
int Speed = 100;

// declare channel for pwm Output
#define R 0
#define L 1

// PWM Pin for Controlling the speed
int enA = 5;
int enB = 23;

// motor controlling pin
int IN1 = 22;
int IN2 = 21;
int IN3 = 19;
int IN4 = 18;

void setup()
{
  Serial.begin(115200);

  // Bluetooth Name
  serialBT.begin("Mrad");

  // output pin declare
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Setup PWM channels
  ledcSetup(R, 5000, 8); // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(enA, R);
  ledcSetup(L, 5000, 8); // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(enB, L);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Intial State of Car
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop()
{

  while (serialBT.available())
  {
    btSignal = serialBT.read();
    // Serial.println(btSignal);

    if (btSignal >= '0' && btSignal <= '9')
      Speed = 100 + (btSignal - '0') * 20;
    else if (btSignal == 'q')
      Speed = 255;

    // to see the incoming signal in serial monitor
    Serial.println(btSignal);
    switch (btSignal)
    {
    case 'B':
      backward();
      break;
    case 'F':
      forward();
      break;
    case 'L':
      left();
      break;
    case 'R':
      right();
      break;
    case 'S':
      stop();
      break;
    }
  }
}

// function for control motor
void backward()
{
  ledcWrite(R, Speed);
  ledcWrite(L, Speed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void forward()
{
  ledcWrite(R, Speed);
  ledcWrite(L, Speed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left()
{
  ledcWrite(R, Speed);
  ledcWrite(L, Speed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right()
{
  ledcWrite(R, Speed);
  ledcWrite(L, Speed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop()
{
  ledcWrite(R, Speed);
  ledcWrite(L, Speed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
