#define CW  0
#define CCW 1
#include <HCSR04.h>
#include <Servo.h> 
// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1
Servo servoMoteur;
int Distance;
const byte triggerPin = 8;
const byte echoPin = 7;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 5; // PWM control (speed) for motor B
const byte DIRA = 2; // Direction control for motor A
const byte DIRB = 4; // Direction control for motor B
const byte vitesse_voit=9.42478*0.03;
void setup() {
  servoMoteur.write(90);
  Serial.begin(9600);
  setupArdumoto();
  servoMoteur.attach(9);
  // put your setup code here, to run once:
 }


void loop() {
  // put your main code here, to run repeatedly:
  Distance=distanceSensor.measureDistanceCm();
  if (Distance>26){
    digitalWrite(DIRA,CW);
    digitalWrite(DIRB,CCW);
    analogWrite(PWMA,255); //roue autre coté
    analogWrite(PWMB,173); //roue coté pile
  }
  
  if (Distance<25){
    analogWrite(PWMA,0);
    analogWrite(PWMB,0);
    delay(5000);
    servoMoteur.write(180);
    analogWrite(PWMB,173);
    analogWrite(PWMA,0);
    delay(1000);
    analogWrite(PWMB,0);
    analogWrite(PWMA,0);
    
  }
  Serial.println(Distance);
}



void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
