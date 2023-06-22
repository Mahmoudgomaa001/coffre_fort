#include <Keypad.h>
const char* correctPassword = "1234";  // Mot de passe correct
const byte ROWS = 4;
const byte COLS = 10;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {A1, 8, 7, 6};
byte colPins[COLS] = {A0, 4, 10};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

bool checkPassword()
{
  String enteredPassword;
  char key = keypad.getKey();

  while (key != '#')
  {
    if (key)
    {
      Serial.println(key);
      lcd.print(key);
      enteredPassword += key;
    }
    key = keypad.getKey();
  }
  lcd.println();
  return enteredPassword.equals(correctPassword);
}

return enteredPassword.equals(correctPassword);
}
bool waitForButtonD()
{
  char key = keypad.getKey();
  while (key != 'D')
  {
    if (key == 'B')
    {
      lcd.clear();
      lcd.print("Fermeture !");
      //      myservo.write(0);   // Ramener le servo-moteur à sa position initiale
      delay(1000);
      lcd.print("posez votre doit!");
      return false;

    }
    key = keypad.getKey();
  }
  return true;
}
