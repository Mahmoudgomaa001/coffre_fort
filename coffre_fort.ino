#define IN1   22
#define IN2   24
#define IN3   26
#define IN4   28
#define DOOR_SWITCH_PIN 30

int Steps = 0;
int Direction = 0;
const int number_steps = 2048; //= 2048/4
boolean door_closed = false;

void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(DOOR_SWITCH_PIN, INPUT_PULLUP);

  closeDoor();
  delay(1000);
  stepper(number_steps);
  delay(1000);
  closeDoor();
  // delay(1000);
}
void loop()
{
  //  //1 rotation counter clockwise
  //  stepper(number_steps);
  //  delay(1000);
  //  //1 rotation clockwise
  //  stepper(-number_steps);
  //  delay(1000);
  //  //Keep track of step number
  //  for (int thisStep = 0; thisStep < number_steps; thisStep++) {
  //    stepper(1);
  //  }
  //  delay(1000);
  //  for (int thisStep = number_steps; thisStep > 0; thisStep--) {
  //    stepper(-1);
  //  }
  //  delay(1000);
}

void closeDoor() {
  while (!door_closed) {
    stepper(-1);
    updateDoorStatus();

  }

}

void stepper(double nbStep) {
  if (nbStep >= 0) {
    Direction = 1;
  } else {
    Direction = 0;
    nbStep = -nbStep;
  }
  for (int x = 0; x < nbStep * 8; x++) {
    switch (Steps) {
      case 0:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      case 1:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
        break;
      case 2:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 3:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 4:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 5:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 6:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 7:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      default:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
    }
    delayMicroseconds(1000);
    if (Direction == 1) {
      Steps++;
    }
    if (Direction == 0) {
      Steps--;
    }
    if (Steps > 7) {
      Steps = 0;
    }
    if (Steps < 0) {
      Steps = 7;
    }
  }
}

void updateDoorStatus() {
  // Update the status of the door
  if (digitalRead(DOOR_SWITCH_PIN) == LOW) {
    door_closed = true;
  } else {
    door_closed = false;
  }

}
