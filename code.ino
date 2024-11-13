#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

const int servoPin = 8;
const int trigPin = 7;
const int echoPin = 6;
long duration;
int distance;
int thresholdDistance = 10;

void setup() {
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Fabric Inspection");
  delay(2000);
  lcd.clear();
  
  servo.attach(servoPin);
  servo.write(0);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > thresholdDistance) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Defect Detected!");
    servo.write(90);
    delay(1000);
    servo.write(0);
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Defects Found");
    servo.write(0);
  }

  delay(500);
}
