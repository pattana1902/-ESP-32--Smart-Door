#include <Keypad.h>
#define RELAY_PIN   14 // ESP32 pin GIOP14 connected to the IN pin of relay 
#define ROW_NUM     4  // four rows
#define COLUMN_NUM  4  // four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},   
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {21, 19, 18, 5};    // 
byte pin_column[COLUMN_NUM] = {17, 16, 4, 2}; // 

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password_1 = "12345"; // change your password here
const String password_2 = "5642CD";  // change your password here
const String password_3 = "545423";  // change your password here
String input_password;

void setup() {
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 32
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, 1); // lock the door
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print(key);

    if (key == '*') {
      input_password = ""; // reset the input password
    } else if (key == '#') {
      if (input_password == password_1 || input_password == password_2 || input_password == password_3) {
        Serial.println("Valid Password => unlock the door");
        digitalWrite(RELAY_PIN, 0);  // unlock the door for 20 seconds
        delay(20000);
        digitalWrite(RELAY_PIN, 1); // lock the door
      } else {
        Serial.println("Invalid Password => Try again");
      }

      input_password = ""; // reset the input password
    } else {
      input_password += key; // append new character to input password string
    }
  }
}
