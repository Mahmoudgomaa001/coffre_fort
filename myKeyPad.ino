#include <Keypad.h>
const char* correctPassword = "1234";  // Mot de passe correct
const byte ROWS = 4; // Nombre de lignes du clavier
const byte COLS = 4; // Nombre de colonnes du clavier
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};    // Broches des lignes connectées au clavier
byte colPins[COLS] = {5, 4, A0, A1};   // Broches des colonnes connectées au clavier
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
bool checkPassword()
{
  String enteredPassword;
  char key = keypad.getKey();

  while (key != '#')
  {
    if (key)
    {
      if (key == 'C')
      {
        enteredPassword = ""; // Effacer le code entré
        lcd.clear();
        lcd.print("Code efface !");
      }
      else
      {
        lcd.print(key);
        enteredPassword += key;
      }
    }
    key = keypad.getKey();
  }
  lcd.println();
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
