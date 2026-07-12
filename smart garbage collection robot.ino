#include <ESP32Servo.h>

#define TRIG_PIN 19
#define ECHO_PIN 18
#define SERVO_PIN 21
#define wetsensor 25

Servo myServo;

float distanceCM;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(wetsensor, INPUT);

  myServo.setPeriodHertz(50);
  myServo.attach(SERVO_PIN, 500, 2400);

  myServo.write(90);
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  if (duration == 0)
    return -1;

  return duration * 0.0343 / 2.0;
}

void loop() {
  distanceCM = getDistance();

  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.println(" cm");

  if (distanceCM > 0 && distanceCM < 20) {
    delay(2000);

    if (digitalRead(wetsensor) == 0) {
      myServo.write(60);
      Serial.println("wet");
    } else {
      myServo.write(150);
      Serial.println("Dry");
    }
  } else {
    myServo.write(90);
  }

  delay(200);
}