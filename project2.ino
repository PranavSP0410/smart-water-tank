#include <dht.h>

dht DHT;
const int trigPin = 9;
const int echoPin = 10;
const int buzz1=12;
const int buzz2=13;
// defining variables
unsigned long duration;
int distance;
#define DHT11_PIN 7

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzz1, OUTPUT); // Sets the buzz1 as an Output
  Serial.begin(9600); //Baud rate: 9600
}

void loop() {
  int sensorValue = analogRead(A0);// read the input on analog pin 0:
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(500);
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  if (voltage>=1.7){
    Serial.println("Water Safe");
    digitalWrite(buzz2, LOW);
  }
  else{
    Serial.println("Water Not Safe");
    digitalWrite(buzz2, HIGH);
    delay(1000);
    digitalWrite(buzz2, LOW);
  }
  Serial.println(voltage); // print out the value you read:
  delay(500);
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if (distance>2)
{
  Serial.println("Refill Required");
  digitalWrite(buzz1, HIGH);
  delay(1000);
  digitalWrite(buzz1, LOW);
}
else if (distance<2)
{
  Serial.println("Overflow");
  digitalWrite(buzz1, HIGH);
  delay(1000);
  digitalWrite(buzz1, LOW);
}
else
{
  Serial.println("Correct");
  digitalWrite(buzz1, LOW);
}
Serial.println("   ");
delay(1000);
}
