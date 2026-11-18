/*
Final APSC Sketch for team 129
Hydroponics system
*/

//hardware map
#define BUTTONPIN A5
#define MOTORPIN
#define OLEDPIN
#define SERVOPIN
#define PHPROBEPIN
#define 
Servo myServo;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(SERVOPIN);
  //serial monitor for debug - REMOVE WHEN DONE
  Serial.begin(9600);

  


}

void loop() {
  // put your main code here, to run repeatedly:

}

void servoMotor(int openTime) {
  myServo.write(90);
  delay(openTime);
  myServo.write(0);
}

void peristalticPump() {

}

void mixing() {
}
