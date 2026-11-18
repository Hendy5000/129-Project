#define SUBMERSIBLEPUMPPIN
#define DIAPHRAGMPUMPPIN   

const int PUMPSPEED = 255;              // 0-255, full speed
long pumpTimer = 0;            // 0 = pump not started yet
long waterPumpTime = 1000;    // Jack's sensing state should set this
long mixturePumpTime = 1000;  // from flow calibration
AF_DCMotor spump(2);
AF_DCMotor dpump(3);

else if (stateMachine == 1){
      //water pump (Caleb) code
      if (pumpTimer == 0){                       // first time in this state
        spump.run(FORWARD);                        // start submersible pump
            spump.setSpeed(255);
        pumpTimer = millis();                    // remember start time
      }
      if (millis() - pumpTimer > waterPumpTime){ // time is up
        spump.run(RELEASE);            // stop pump
        pumpTimer = 0;                           // reset for the next state
        stateMachine = 2;                        // go to pH pumping
      }
    }

 else if (stateMachine == 5){
      //mixture pumping state (Caleb)
      if (pumpTimer == 0){
        dpump.run(FORWARD); // start diaphragm pump
            dpump.setSpeed(255);
        pumpTimer = millis();
      }
      if (millis() - pumpTimer > mixturePumpTime){
        dpump.run(RELEASE);         // stop diaphragm pump
        pumpTimer = 0;
        stateMachine = 6;                         // go to nutrient absorption
      }
    }
