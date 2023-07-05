// C++ code
//
#include <Servo.h>

int usr = 0;
int usd = 0;
int unnamed = 0;
int i = 0;
int j = 0;
int k = 0;
int isBuzzer = 0;
int m = 0;
int n = 0;
bool buzzcond=false;
int gate=0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_9;

void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(4, OUTPUT);
  servo_9.attach(9, 500, 2500);
}

void loop()
{
  int a=(17-0.01723 * readUltrasonicDistance(10, 11));
  int b=(17-0.01723 * readUltrasonicDistance(13, 12));
  usr = (a<=0?0:a);
  usd = (b<=0?0:b);
  Serial.print(usd);
  Serial.print(',');
  Serial.print(usr);
  Serial.print(',');
  Serial.println(gate);
  if (usd < 4) {
    digitalWrite(5, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    buzzcond=false;
    noTone(4);
    gate=0;
    servo_9.write(0);
  } else {
    if (usd >= 4 && usd < 10) {
      if (usr < 4) {
        digitalWrite(5, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(6, LOW);
        gate=1;
        servo_9.write(90);
        if(!buzzcond){
          tone(4, 523, 1000); // play tone 60 (C5 = 523 Hz)
          delay(1000);
          noTone(4);
          buzzcond=true;
        }
      } else {
        digitalWrite(5, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(6, LOW);
        gate=0;
        servo_9.write(0);
        buzzcond=false;
        noTone(4);
      }
    } else {
      gate=1;
      servo_9.write(90);
      digitalWrite(5, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      if(!buzzcond){
        tone(4, 523, 1000); // play tone 60 (C5 = 523 Hz)
        delay(1000);
        noTone(4);
        buzzcond=true;
      }
    }
  }
  delay(1000); // Delay a little bit to improve simulation performance
}

