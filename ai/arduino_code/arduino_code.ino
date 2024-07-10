#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

byte state = 0;
byte once = 0;

const int sw1 = 2;
const int en = 7;  // 스테퍼모터 온/오프 핀
const int val = A5;  // 가변 저항 값

void Change() {
  if (state == 0) {
    State1();
  } else {
    State0();
  }
}

void State0() {
  delay(200);
  digitalWrite(en, LOW);
  Serial.println("STOP");
  once = 0;
  state = 0;
}

void State1() {
  delay(200);
  digitalWrite(en, HIGH);
  Serial.println("START");
  state = 1;
}

void setup() {
  Serial.begin(9600);
  pinMode(en, OUTPUT);
  digitalWrite(en, LOW);

  pinMode(sw1, INPUT);
  attachInterrupt(digitalPinToInterrupt(sw1), Change, FALLING);

  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);
  resetServos();

  pinMode(val, INPUT);

  Serial.println("Device's ready");
  delay(1000);
}

void loop() {
  once = 0;
  while (state == 0) {
    if (once == 0) {
      resetServos();
      once = 1;
    }
    Serial.println(analogRead(val));
  } 

  while (state == 1) {
    runServoCycle();
  }
}

void resetServos() {
  servo1.write(90);
  delay(15);
  servo2.write(90);
  delay(15);
  servo3.write(90);
  delay(15);
  servo4.write(90);
  delay(15);
}

void runServoCycle() {
  Serial.println("Servo 1");
  servo1.write(30);
  delay(2000);
  servo1.write(90);
  delay(5000);
  if (state == 0) return;

  Serial.println("Servo 2");
  servo2.write(150);
  delay(2000);
  servo2.write(90);
  delay(5000);
  if (state == 0) return;

  Serial.println("Servo 3");
  servo3.write(30);
  delay(2000);
  servo3.write(90);
  delay(5000);
  if (state == 0) return;

  Serial.println("Servo 4");
  servo4.write(150);
  delay(2000);
  servo4.write(90);
  delay(5000);
}
