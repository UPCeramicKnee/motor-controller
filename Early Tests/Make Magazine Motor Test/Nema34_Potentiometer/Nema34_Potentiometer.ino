/* Potentiometer Program
John Saunders NYCCNC http://www.nyccnc.com/
  
microstep driver ST-M5045
- Pul+ goes to +5V
- Pul- goes to Arduino Pin 22
- Dir+ goes to +5V
- Dir- goes to to Arduino Pin 24
- Enable+ to nothing
- Enable- to nothing
*/

//int sensorPin = A3;
//int sensorValue = 0;
int sensorValue = 500;

void setup() {                
  pinMode(24, OUTPUT);  //direction pin
  pinMode(22, OUTPUT); //step pin
  digitalWrite(24, LOW);
  digitalWrite(22, LOW);
}

void loop() {
  //sensorValue = analogRead(sensorPin);
  //sensorValue = map(sensorValue,0,1023,3600,1);

  digitalWrite(22, HIGH);
  delayMicroseconds(sensorValue);          
  digitalWrite(22, LOW); 
  delayMicroseconds(sensorValue);
 }
