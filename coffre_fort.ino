
#include "LCDIC2.h"

#define IN1   11
#define IN2   12
#define IN3   13
#define IN4   5

#define DOOR_SWITCH_PIN A2

int Steps = 0;
int Direction = 0;
const int number_steps = 2048; //= 2048/4
boolean door_closed = false;
const int Open_Time = 5000; //= 2048/4
LCDIC2 lcd(0x27, 16, 2);

///
#include <Adafruit_Fingerprint.h>


#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(2, 3);

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define mySerial Serial1

#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//

void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(DOOR_SWITCH_PIN, INPUT_PULLUP);
  lcd.begin();  // Initialisation de l'écran LCD

  fingerSetup();
  updateLCD("HI","Waiting FingerP");
  closeDoor();
//  delay(1000);
//
//  delay(1000);
//  closeDoor();
  // delay(1000);
}
void loop()
{
  fingerLoop();
}

void closeDoor() {
  updateDoorStatus();
  while (!door_closed) {
    updateDoorStatus();
    stepper(-1);


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
void updateLCD(String msg1,String msg2) {

  // Update the LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg1);
  lcd.setCursor(0, 1);
  lcd.print(msg2);

}

void openDoor() {

  stepper(number_steps);
}
