else if (stateMachine == 4) { // main loop that jack made
// my code that goes inside the else   
  if (mixTimer == 0) {                     // when the mixTimer reads 0 the moter and the time will start
    digitalWrite(MOTORPIN, HIGH);          // send power to moter
    mixTimer = millis();                   // This does something?
  }

  if (millis() - mixTimer > MIX_TIME) {    // Will check if 110 s has passed 
    digitalWrite(MOTORPIN, LOW);           // Will turn off power to moter
    mixTimer = 0;                          // resets the mixing timer to 0
    stateMachine = 5;                      // move on to mixture pumping out of the mixing tank
  }
}
