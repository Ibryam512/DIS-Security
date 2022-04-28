#include <Keypad.h>
#include <LiquidCrystal.h>

char hexaKeys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[4] = {9, 8, 7, 6}; 
byte colPins[4] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, 4, 4); 
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

String const password = "5126";
String pass = "";
bool on = true;

void success()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DIS Security");
  lcd.setCursor(0, 1);
  lcd.print("Welcome home!");
  on = false;
  digitalWrite(13, HIGH);
  noTone(11);
  delay(500);
  digitalWrite(13, LOW);
}

void fail()
{
  tone(11, 3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DIS Security");
  lcd.setCursor(0, 1);
  lcd.print("Wrong password!");
  pass = "";
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
}

void writePassword()
{
  char customKey;
  while (customKey != 'D' && pass.length() < 6)
  {
    if (customKey)
    {
      Serial.println(customKey);
      pass += customKey;
      lcd.print(customKey);
    }
    customKey = customKeypad.getKey();
  }
}

void setup()
{
  pinMode(4, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("DIS Security");
  Serial.begin(9600);
}

void loop()
{
  int status = digitalRead(10);
  if (status == 1 && on)
  {
    tone(11, 1000);
    lcd.setCursor(0, 1);
    lcd.print("Password: ");
    writePassword();
    if (pass == password)
    {
      success();
    }
    else
    {
      fail();
    }
  }
}
