//Name: Ricky
//E-mail: shenricky06@gmail.com
//Project: DistanceTempHumidMonitor

#include <DHT.h> //Include library to use DHT commands
#include <LiquidCrystal.h> //Include library for the LCD Display Commands
#define DHTTYPE DHT11 //Declare what type of DHT it is.

//Declare Variables
const int trigPin = 5;
const int echoPin = 4;
const int dhtPin = 3;
const int buzzerAct = 2;
const int tempThreshold = 30;
const int distanceThreshold = 15;

//Delcare Variables for LCD Display
const int rs = 12;
const int e = 11;
//const int ct = 8;
const int d4 = 10;
const int d5 = 9;
const int d6 = 7;
const int d7 = 6;

LiquidCrystal mylcd(rs, e, d4, d5, d6, d7);

float temp;
float hum;
long duration;
float distance;

DHT dht(dhtPin, DHTTYPE); //Create the object called "dht"

void setup() {

  Serial.begin(9600);   //Starts serial communication with Arduino and computer with the USB. 9600 is the baud rate (9600 bits/second), the speed of how fast data transfers.

  //Ultra Sonic Sonar
  pinMode(trigPin, OUTPUT); //Set trigger pin as an OUTPUT device
  pinMode(echoPin, INPUT);  //Set echo pin as an INPUT device

  //Buzzer
  pinMode(buzzerAct, OUTPUT);

  //DHT11
  dht.begin();

  //LCD Display
  //pinMode(ct, OUTPUT);
  //analogWrite(ct,60);

  mylcd.begin(16,2);
  mylcd.clear();

}

void loop() {

  //Distance Measurer
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); //Turn off for 2 microseconds to reset
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Turn on for 10 microseconds to fire the ultrasonic pulse
  digitalWrite(trigPin, LOW); //Turn off to allow it to read
  duration = pulseIn(echoPin, HIGH);

  //speed of sound = 343m/s. 
  //pulseIn measures time in microseconds. 1 second = 1,000,000 microseconds.
  //we want to figure out the distance in cm.
  //distance = time * speed. convert it to cm and microseconds. -> 343m/s * 100cm/m = 34,300cm/s. 34,300cm/s * 1 second/1,000,000 microseconds = 0.034 cm/microsecond.
  //divide by 2 since the sound is tracked for there and back but we only want the distance there.
  distance = duration * 0.034 / 2;
  
  if (distance >= 2 && distance <= 400) { //Create a boolean expression since it can't read within a certain range.
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print("cm ");
  } else {
    Serial.print("Distance: Out of range. ");
  }

  if (distance > 0 && distance < distanceThreshold){ //Buzzer turns on when distance is too close
    digitalWrite(buzzerAct, HIGH);
    Serial.print("(Too close!) ");
  } else {
    digitalWrite(buzzerAct, LOW);
  }

  //Temperature and Humidity Reader
  temp = dht.readTemperature(); //Command from library, set it to the temp variable to attach the reading value
  hum = dht.readHumidity(); //Command from library, set it to the hum variable to attach the reading value

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" C ");

  if (temp > tempThreshold){ //Buzzer turns on when temperature is too high
    digitalWrite(buzzerAct, HIGH);
    Serial.print("Too hot! ");
    delay(40);
    digitalWrite(buzzerAct, LOW);
  } else {
    digitalWrite(buzzerAct, LOW);
  }

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println("% ");

//LCD output

  //Top Row (Temperature and Humidity)
  mylcd.setCursor(0,0);
  mylcd.print("T:");
  if (temp > tempThreshold){
    mylcd.print("Too hot");
  } else
  mylcd.print(temp, 1);
  mylcd.print("C ");

  mylcd.print("H:");
  mylcd.print(hum, 1);
  mylcd.print("%");

  // Bottom Row (Distance)
  mylcd.setCursor(0,1);
  mylcd.print("D:");
  if (distance < distanceThreshold){
    mylcd.print("Too close!");
  } else if (distance >= 2 && distance < 400){
    mylcd.print(distance);
    mylcd.print("cm");
  } else
  mylcd.print("Out of range");
  mylcd.print("                ");
  delay(2000);



}
