

void fingerSetup()
{
  //  //  Serial.begin(9600);
  //  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  //  delay(100);
  //  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  //  delay(5);
  //  if (finger.verifyPassword()) {
  //    Serial.println("Found fingerprint sensor!");
  //  } else {
  //    Serial.println("Did not find fingerprint sensor :(");
  //    while (1) {
  //      delay(1);
  //    }
  //  }



  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}

void fingerLoop()                     // run over and over again
{
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      //      Serial.println("Imaging error");
      return p;
    default:
      //      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    updateLCD("Welcome", "FingerP " + String(finger.fingerID));
    delay(1000);
    updateLCD("Please", "Insert Password");
    if (checkPassword()) {
      Serial.println("Found a print match!");

      openDoor();
      // Generate a tone of 1000Hz for 1 second
      tone(buzzerPin, 1000);
      delay(1000);
      // Stop the tone
      noTone(buzzerPin);
      delay(Open_Time);
      closeDoor();
      updateLCD("HI", "Waiting FingerP");
    }


  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    updateLCD("Sorry ", "Not found!");
    delay(3000);
    updateLCD("HI", "Waiting FingerP");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }


  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;


  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
