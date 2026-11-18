#define SUBMERSIBLEPUMPPIN
#define DIAPHRAGMPUMPPIN   

const int PUMPSPEED = 255;              // 0-255, full speed
long pumpTimer = 0;            // 0 = pump not started yet
long waterPumpTime = 1000;    // Jack's sensing state should set this
long mixturePumpTime = 1000;  // from flow calibration

else if (stateMachine == 1){
      //water pump (Caleb) code
      if (pumpTimer == 0){                       // first time in this state
        analogWrite(WATERPUMPPIN, PUMPSPEED);    // start submersible pump
        pumpTimer = millis();                    // remember start time
      }
      if (millis() - pumpTimer > waterPumpTime){ // time is up
        analogWrite(WATERPUMPPIN, 0);            // stop pump
        pumpTimer = 0;                           // reset for the next state
        digitalWrite(MOTORPIN, HIGH);            // flowchart: turn on mixing motor
        stateMachine = 2;                        // go to pH pumping
      }
    }

 else if (stateMachine == 5){
      //mixture pumping state (Caleb)
      if (pumpTimer == 0){
        analogWrite(DIAPHRAGMPUMPPIN, PUMPSPEED); // start diaphragm pump
        pumpTimer = millis();
      }
      if (millis() - pumpTimer > mixturePumpTime){
        analogWrite(DIAPHRAGMPUMPPIN, 0);         // stop diaphragm pump
        pumpTimer = 0;
        stateMachine = 6;                         // go to nutrient absorption
      }
    }
