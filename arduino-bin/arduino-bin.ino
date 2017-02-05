#include <Servo.h>

int SERVO_PIN = 6;
int LED_G_PIN = 9;
int ECHO_PIN = 12;
int TRIGGER_PIN = 13;

int DISTANCE_MAX = 6; // max 174
int POS_BOTTOM = 10; // servo bottom pos
int POS_TOP = 60; // servo top pos
int DELAY_UP = 20;
int DELAY_DOWN = 50;
int SEGMENT_CLOSE = 5; // close in several times of SEGMENT_CLOSE

Servo myservo;
int servo_pos = 10;
long duration, distance;
int to_close = 0;
int init_servo_pos = 0;
int nb_times_ok = 0; // need several times ok to open

//
void setup()
{
  Serial.begin(9600);

  pinMode(LED_G_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(SERVO_PIN);

  myservo.write(POS_BOTTOM);
  digitalWrite(LED_G_PIN, LOW);
}

//
void loop() 
{
  // DETECTION
  digitalWrite(TRIGGER_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 58.2;
  Serial.println(distance);

  if (distance > DISTANCE_MAX) {
    digitalWrite(LED_G_PIN, LOW);
    nb_times_ok = 0;
  }
  else {
    nb_times_ok += 1;
  }

  if (nb_times_ok > 1) {
    digitalWrite(LED_G_PIN, HIGH);
    for (; servo_pos <= POS_TOP; servo_pos += 1) {
      myservo.write(servo_pos);
      delay(DELAY_UP);
    }
    to_close = 1;
    delay(3000);
    nb_times_ok = 0;
  }

  if (to_close == 1) { // closing a little by loop
    init_servo_pos = servo_pos;
    for (; servo_pos >= POS_BOTTOM && servo_pos > init_servo_pos - SEGMENT_CLOSE ; servo_pos -= 1) {
      myservo.write(servo_pos);
      delay(DELAY_DOWN);
    }
    if (servo_pos <= POS_BOTTOM) {
      to_close = 0;
    }
  }

  if (to_close == 1 || nb_times_ok > 0) {
    delay(100);
  }
  else {
    delay(200);
  }
}

