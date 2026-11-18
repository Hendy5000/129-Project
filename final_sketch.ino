/*
Final APSC Sketch for team 129
Hydroponics system
*/
#include <stdio.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

  
  //interupts
  attachInterrupt(digitalPinToInterrupt(STARTBUTTONPIN), startProgram, FALLING);
  attachInterrupt(digitalPinToInterrupt(STOPBUTTONPIN), emergencyStop, FALLING)

}

void loop() {
  // put your main code here, to run repeatedly:
  if(running){
    display.clearDisplay(); 
    display.setTextSize(1);             // Control the size of text. You can use a value of 1,2,3 etc. 
    display.setTextColor(SSD1306_WHITE); // Control the colour of the text. The display is Monochrome, so you can only use white.

    /* setCursor(x,y). This determines the position x,y coordinate where your text will be placed on the screen
    * The Display is a 128x64 display. Top left corner is (0,0), bottom right corner is (128,64) */
    display.setCursor(0,0);       
    display.println(F("====== APSC 101 ====="));  // This is example of static text. Its a simple string and does not change


    display.setTextSize(2); // Display the next line in bigger size
    display.println(F("GGs"));  // This is also static Text but specific to current state
    display.print(test_counter);  // This is a variable text. It will keep changing

    display.display(); // Actually draw everything on the screen.

    
    if (stateMachine == 0){
      //sensing (Jack) code
    }
    elif (stateMachine == 1){
      //water pump (Caleb) code
    }
    elif (stateMachine == 2){
      //pH pumping (Mabel) code
    }
    elif (stateMachine == 3){
      //nutrient pumping (John) code
    }
    elif (stateMachine == 4){
      //mixing (Grace)
    }
    elif (stateMachine == 5){
      //mixing pumping state (Caleb)
    }
    elif (stateMachine == 6){
      //waiting code
    }
  }
  else{
      //digitalWrite(all pins, LOW) to make sure its all stopped
  }

  delay(100);
}

void startProgram(){
  if(millis() - stopTimer > 500){
    running = 1;
  }
}

void emergencyStop(){
  //digitalWrite(all pins, LOW)
}
