#include <Stepper.h>
#include <Servo.h>
#include <SoftwareSerial.h>
extern volatile unsigned long timer0_millis;
int ENA = 8;
int INA1 = 9;
int INA2 = 10; 
int ENB = 11;
int INA3 = 42;
int INA4 = 44; 
int lock = 1;
int unlock = 1;
char automode[2] = "";
unsigned long cnt = 5500;
int servoPin=4;
Servo sun;
int val=0;
int light=A0;
int r=34;
int g=32;
int b=30;

void setup() {
sun.attach(servoPin);
pinMode(r,OUTPUT);
pinMode(g,OUTPUT);
pinMode(b,OUTPUT);

pinMode(ENA, OUTPUT);
pinMode(INA1, OUTPUT);
pinMode(INA2, OUTPUT);

pinMode(ENB, OUTPUT);
pinMode(INA3, OUTPUT);
pinMode(INA4, OUTPUT);

Serial.begin(9600);
Serial1.begin(9600); 
}

void Amode()
{
  if(val<500){
  digitalWrite(b, LOW);
  digitalWrite(g, LOW);
  digitalWrite(r, HIGH);
  sun.write(0);
  delay(100);
  }
  if(val>=500 && val<=700){
  digitalWrite(r, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
  sun.write(0);
  delay(100);
  }
  if(700<val){
  digitalWrite(g, HIGH);
  digitalWrite(r, LOW);
  digitalWrite(b, LOW);
  sun.write(180);
  delay(100);
  }
}

void fw()
{
  analogWrite(ENA, 248);
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);
  digitalWrite(ENB, HIGH);
  digitalWrite(INA3, HIGH);
  digitalWrite(INA4, LOW);
}

void rv()
{
  analogWrite(ENA, 128);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);
  analogWrite(ENB, 140);
  digitalWrite(INA3, LOW);
  digitalWrite(INA4, HIGH);
}

void stopmode()
{
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);
  digitalWrite(INA3, LOW);
  digitalWrite(INA4, LOW);
}

void loop() {
if(automode[0] == 'A')
{
  Amode();
}

if(Serial1.available() > 0)
{
  int cmd = Serial1.read();  
  if (cmd == '0' && unlock == 1) 
 {
  timer0_millis = 0;
  fw();
  lock = 1;
 }
  if (cmd == '1' && lock == 0) 
 {
  timer0_millis = 0;
  rv();
  unlock = 0;
 }
  if (cmd == '2')
 {
  automode[0] = 'A';
 }
  if (cmd =='3')
 {
  automode[0] = 'B';
 }
  if(cmd == '4')
 {
  int servoValue = Serial1.parseInt();
  if(0 <= servoValue <= 180)
  {
   sun.write(servoValue);
  }
 }
  if(cmd == '5')
 {
  sun.write(0);
 }
  if(cmd == '6')
 {
  sun.write(45);
 }
  if(cmd == '7')
 {
  sun.write(90);
 }
  if(cmd == '8')
 {
  sun.write(135);
 }
  if(cmd == '9')
 {
  sun.write(180);
 } 
}

int lightValue=analogRead(light);
val = analogRead(light);
//Serial.println(val);

if (millis() > cnt)
{
  stopmode();
  lock = 0;
  unlock = 1;
}
}
