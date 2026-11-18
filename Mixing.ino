else if (stateMachine == 4) {        // main loop that jack made
                                     // my code that goes inside the else   
  if (mixTimer == 0) {               // when the mixTimer reads 0 the moter and the timer will start
  motor.setSpeed(255);               // set motor speed
  motor.run(FORWARD);                // start motor, moving forward
  mixTimer = millis();               // records the time that the mixing starts at
  }

  if (millis() - mixTimer > MIX_TIME) {    // Will check if 110 s has passed, the mix time needs to be defined somewhere in the setup
    motor.run(RELEASE);                    // Will stop the motor
    mixTimer = 0;                          // resets the mixing timer to 0
    stateMachine = 5;                      // move on to mixture pumping out of the mixing tank
  }
}
