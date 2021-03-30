#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "A_CXxT8QY5Nh9esYXErq0P5F9F7jMcf-";
char ssid[] = "SinyalUhu";
char pass[] = "jalanarun126";

const int trig = D7;
const int echo = D8;
const int relay = D6;
bool getV0;
long duration;
int distance;

BLYNK_WRITE(V0){
  getV0 = param.asInt();
}
WidgetLCD lcd(V1);

void setup() {
  // put your setup code here, to run once:
Blynk.begin(auth, ssid, pass);

pinMode(trig, OUTPUT);
pinMode(relay, OUTPUT);
pinMode(echo, INPUT);
Serial.begin(9600);
lcd.clear();
lcd.print(2,0,"Welcome Back");
lcd.print(5,1,"Master");
delay(3000);
lcd.clear();
digitalWrite(relay, LOW);
delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();

digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH); 
delayMicroseconds(10);
digitalWrite(trig, LOW);

duration = pulseIn(echo, HIGH);
distance = duration*(0.034/2);

Serial.print("Distance: ");
Serial.println(distance);

if (getV0 == 1){
  digitalWrite(relay, HIGH);
  delay(500);
}
else{
  digitalWrite(relay, LOW);
  delay(500);
}
if (distance <= 20){
  lcd.clear();
  lcd.print(0,0,"Water in the");
  lcd.print(0,1,"pond is enough");
  delay(200);
}
else if (distance >= 60){
  lcd.clear();
  lcd.print(0,0,"Water in the");
  lcd.print(0,1,"pond isn't enough");
  delay(200);
}
}
