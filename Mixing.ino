#define MOTORPIN 9

enum State { IDLE, MIXING, COMPLETE };
State currentState = IDLE;

void mixing() {
  if (currentState != MIXING) return;

  if (mixTimer == 0) {                    
    digitalWrite(MOTORPIN, HIGH);
    mixTimer = millis();
  }

  if (millis() - mixTimer > MIX_TIME) {   
    digitalWrite(MOTORPIN, LOW);
    mixTimer = 0;
    currentState = COMPLETE;
  }
}
