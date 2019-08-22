/*
  PWM Motor Test
  pwm_motortest.ino
  Uses LCD Keypad module
  Modified from Cytron example code

  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
// Include libraries for LCD Display
#include <LiquidCrystal.h>
#include <LCD_Key.h>

// Define keycodes
#define None     0
#define Select   1
#define Left     2
#define Up       3
#define Down     4
#define Right    5

// Pin for analog keypad
#define diy_pwm  A2
// PWM output pin
#define pwm      3
// Motor direction pin
#define dir      2

// Define LCD display connections
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Setup LCD Keypad object
LCD_Key keypad;

// Variable to represent PWM value
int pwm_value = 0;

// Variable to represent Keypad value
int localKey;

void setup() {

  // Setup LCD
  lcd.begin(16, 2);
  lcd.clear();

  // Define Pins
  pinMode(pwm, OUTPUT);
  pinMode(dir, OUTPUT);

}

void loop()
{
  while (1)
  {
    // Scan keypad to determine which button was pressed
    localKey = keypad.getKey();

    // Toggle motor direction if LEFT button pressed
    if (localKey == Left) {
      digitalWrite(dir, !digitalRead(dir));
      delay(200);
    }

    // Increase motor speed if UP button pressed
    if (localKey == Up) {
      pwm_value++;
      delay(200);
      lcd.clear();
    }

    // Decrease motor speed if DOWN button pressed
    else if (localKey == Down) {
      pwm_value--;
      delay(200);
      lcd.clear();
    }

    // Ensure PWM value ranges from 0 to 255
    if (pwm_value > 255)
      pwm_value = 255;
    else if (pwm_value < 0)
      pwm_value = 0;

    // Send PWM to output pin
    analogWrite(pwm, pwm_value);

    // Display results on LCD
    lcd.setCursor(0, 0);
    lcd.print("PWM:");
    lcd.print(pwm_value);
    lcd.setCursor(0, 1);
    lcd.print("DIR:");
    lcd.print(digitalRead(dir));
  }
}
