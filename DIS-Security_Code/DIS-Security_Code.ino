//First section - Pre-Set Up
#include <Keypad.h> //adding library for the keypad
#include <LiquidCrystal.h> //adding library for the display

//creating two-dimentional array for the keypad
char hexaKeys[4][4] = { 
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//creating arrays for the row/col in the keypad
byte rowPins[4] = {9, 8, 7, 6}; 
byte colPins[4] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, 4, 4); //"delaring" the keypad
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); //"declaring" the display

String const password = "5126"; //seting the password - you can set your own (to be less than 7 digits)
String pass = ""; //declaring the variable that keeps the password
bool on = true;

//Second Section - Set Up
void setup()
{
  pinMode(4, INPUT); //declaring pin 4 as INPUT
  pinMode(11, OUTPUT); //declaring pin 11 - 14 as OUTPUTS
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  lcd.begin(16, 2); //initialising the display screen
  lcd.print("DIS Security"); //writing "DIS Security" on the display
}


//Third Section - The Loop
void loop()
{
  int status = digitalRead(10); //Reading the input from the PIR Sensor
  if (status == 1 && on) //3.1 - The tresspasing
  {
    tone(11, 1000); //turning the Piezo on, Frequency: 1000Hz
    char customKey; //declaring char which will keep the last entered value
    lcd.setCursor(0, 1); //Moving to the second row of the display
    lcd.print("Password: "); //Wriing "Password: "
    while (customKey != 'D' && pass.length() < 6) //Keep recieving digit while the D button isn't pressed and the password isn't more than 6 digits
    {
     if (customKey)
     {
        pass += customKey; //Adding the pressed key to the password
        lcd.print(customKey); //Writing the last pressed key on the display
      }
      customKey = customKeypad.getKey(); //actualization
    }

    //3.2 - The correct password
    if (pass == password)
    {
      lcd.clear(); //clearing the display
      lcd.setCursor(0, 0);
      lcd.print("DIS Security"); //Writing on the display "DIS Security \n Welcome home!"
      lcd.setCursor(0, 1);
      lcd.print("Welcome home!");
      on = false; //stopping the system
      digitalWrite(13, HIGH); //Turning the green diode on
      noTone(11); //stopping the Piezo
      delay(500); //waiting for 1/2 second
      digitalWrite(13, LOW); //Turning the green diode off
    }
    //3.3 - The incorect passowrd
    else
    {
      tone(11, 3000); //even more deafening frequency starts
      lcd.clear(); //clearing the display
      lcd.setCursor(0, 0);
      lcd.print("DIS Security"); //Writing on the display "DIS Security \n Wrong password!"
      lcd.setCursor(0, 1);
      lcd.print("Wrong password!");
      pass = ""; //clearing the password
      digitalWrite(12, HIGH); //Turning the red diode on
      delay(500); //waiting for 1/2 second
      digitalWrite(12, LOW); // Turning the red diode off
    }
  }
}
