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
  lcd.clear();
  lcd.print("code:");
  while (key != '#')
  {
    if (key)
    {
//      Serial.println(key);
      lcd.print("*");
      enteredPassword += key;
    }
    key = keypad.getKey();
  }
  lcd.println();
  return enteredPassword.equals(correctPassword);
}
