/*
Final APSC Sketch for team 129
Hydroponics system
*/
#include <stdio.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "GravityTDS.h"

//hardware map
#define STARTBUTTONPIN
#define STOPBUTTONPIN 
#define MOTORPIN
#define OLEDPIN
#define SERVOPIN
#define PHPROBEPIN
#define 


#define SCREEN_WIDTH 128 // OLED display width, in pixels. 
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//pH probe calibration values
#define V4 1.887
#define V7 1.359

//Assorted values
#define MIX_TIME 110000

//TDS probe initiation
GravityTDS tds;
Servo myServo;
AF_DCMotor motor(1); 
AF_DCMotor spump(2);
AF_DCMotor dpump(3);

void setup() {
  // put your setup code here, to run once:
  //Initializing important variables
  int running = 0;
  int stopTimer = 0;

  //serial monitor for debug - REMOVE WHEN DONE
  Serial.begin(9600);

  //state machine: 0 = sensing state, 1 = water pumping state, 2 = pH pumping state, 3 = nutrient pumping state, 4 = mixing state, 5 = mixture pumping state, 6 = nutrient absorption state
  int stateMachine = 0;
  char[][] stateMachineText = {"sensing state", "water pumping state", "pH pumping state", "nutrient pumping state", "mixing state", "mixture pumping state", "nutrient absorption state"};

  //OLED code
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  //interupts
  attachInterrupt(digitalPinToInterrupt(STARTBUTTONPIN), startProgram, FALLING);
  attachInterrupt(digitalPinToInterrupt(STOPBUTTONPIN), emergencyStop, FALLING)

  //TDS sensor code
  tds.setPin(tdsPin);
  tds.setAref(5.0);       // The sensor needs to have the reference voltage for TDS calculation. For Arduino Mega, it is 5V
  tds.setAdcRange(1024);  
  tds.begin();

  //John's stuff
  float inputTDS;
  float targetTDS = 0.371; //mg/mL
  float massNeeded;
  float mixerVolume = 500; // (mL) calculate later
  float dispenserflowrate = 50; //mg/s
  unsigned long dispensingStartTime = 0;
  unsigned long servoOpenTime = 0;
  bool dispensingStarted = false;

  //Initial pH and TDS values, used for pH and nutrient dispensing
  float initialPH;
  float initialTDS;

  //timer for general use
  float pumpTimer = 0;
  float mixTimer = 0;
  float dpumpTimer = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

  //clears and resets display.
  display.clearDisplay(); 
  display.setCursor(0,0); 

  //running loop
  if(running){      
    display.print("Current state: ");
    display.println(stateMachineText[stateMachine]);
    display.print("pH: ");
    display.println();
    display.print("Turbidity: ");
    display.print();
    
    //State machine that processes all the states.
    if (stateMachine == 0){
      initialPH = findPH();
      initialTDS = findTDS();

      stateMachine = 1;
    }
    else if (stateMachine == 1){
      if (pumpTimer == 0){                       // first time in this state
        spump.run(FORWARD);                        // start submersible pump
        spump.setSpeed(255);
        pumpTimer = millis();                    // remember start time
      }
      if (millis() - pumpTimer > waterPumpTime){ // time is up
        spump.run(RELEASE);                       // stop pump
        pumpTimer = 0;                           // reset for the next state
        stateMachine = 2;                        // go to pH pumping
      }
    }
    else if (stateMachine == 2){
      //pH pumping (Mabel) code
    }
    else if (stateMachine == 3){
      //nutrient pumping (John) code
      // STEP 1: Calculate required nutrient mass
      if (!dispensingStarted) {
        inputTDS = initialTDS;
        massNeeded = (targetTDS - inputTDS) * mixerVolume;
        if (massNeeded > 0) {    
            servoOpenTime = (massNeeded / dispenserflowrate) * 1000;
            myServo.write(90);
            dispensingStartTime = millis();
            dispensingStarted = true;
        }
      }
      if (dispensingStarted) {
        if (millis() - dispensingStartTime >= servoOpenTime) {
            myServo.write(0);
            dispensingStarted = false;
        }
      }
    }
    else if (stateMachine == 4){
      // my code that goes inside the else
      if (mixTimer == 0) {               // when the mixTimer reads 0 the moter and the timer will start
        motor.setSpeed(255);               // set motor speed
        motor.run(FORWARD);                // start motor, moving forward
        mixTimer = millis();               // records the time that the mixing starts at
      }
      if (millis() - mixTimer > MIX_TIME) {    // Will check if 110 s has passed, the time needs to be defined somewhere in the setup
        motor.run(RELEASE);                    // Will stop the motor
        mixTimer = 0;                          // resets the mixing timer to 0
        stateMachine = 5;                      // move on to mixture pumping out of the mixing tank
      }
    }
    else if (stateMachine == 5){
      //mixture pumping state (Caleb)
      if (dpumpTimer == 0){
        dpump.run(FORWARD);     // start diaphragm pump
        dpump.setSpeed(255);
        dpumpTimer = millis();
      }
      if (millis() - dpumpTimer > mixturePumpTime){
        dpump.run(RELEASE);         // stop diaphragm pump
        dpumpTimer = 0;
        stateMachine = 6;                         // go to nutrient absorption
      }
    }
    else if (stateMachine == 6){
      //waiting code
    }
  }
  else{
    //digitalWrite(all pins, LOW) to make sure its all stopped
    display.println("Current state: ");
    display.println("OFF");
    display.print("Press start to restart");
  }

  display.display();
  delay(100);
}

void startProgram(){
  if(millis() - stopTimer > 500){
    running = 1;
  }

  //digitalWrite(all pins, HIGH);
}

void emergencyStop(){
  //digitalWrite(all pins, LOW);

  running = 0;
}

float findPH(){
  float slope = (7.0 - 4.0) / (V7 - V4);
  float voltage = analogRead(PHPROBEPIN) * (5.0 / 1023.0);
  float pH = slope * voltage + (7.0 - (slope * v7));

  return pH;
}

float findTDS(){
  float tdsValue;
  tds.update();
  tdsValue = tds.getTdsValue();

  return tdsValue;
}
