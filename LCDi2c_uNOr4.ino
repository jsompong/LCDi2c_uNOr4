#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
int LEDpin = 13;
int led_state = LOW;   // led_state used to set the LED
int elloUNOr = 1;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

static uint8_t Digit5th = 0; // Defines the 5th digit weight
static uint8_t Digit4th = 0; // Defines the 4th digit weight
static uint8_t Digit3rd = 0; // Defines the 3rd digit weight
static uint8_t Digit2nd = 0; // Defines the 2nd digit weight
static uint8_t tempC = 0; // Defines the last digit weight

void setup() {
lcd.begin();       // initialize the LCD
lcd.backlight();    // Turn on the blacklight and print a message.    
lcd.setCursor(0, 0);      lcd.print("UNO r4 LCD");
lcd.setCursor(0, 1);      lcd.print("IIC address 0x27");
pinMode(LEDpin, OUTPUT);     // set the digital pin as output
Serial.begin(2400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Arduino UNO R4");
}

void loop() {
 led_state = (led_state == LOW) ? HIGH : LOW;  // if the LED is off turn it on and vice-versa
 digitalWrite(LEDpin, led_state);     // set the LED with the led_state of the variable 
 delay(30);  
 lcd.setCursor(0, 0);
 lcd.print("Weight ");
 lcd.print(Digit5th);     lcd.print(Digit4th);        lcd.print(Digit3rd);      lcd.print(Digit2nd);      lcd.print(tempC);
 lcd.print(" kg."); 
 lcd.setCursor(0, 1);     lcd.print("| Count ");      lcd.print(elloUNOr);      lcd.print("      |");
 elloUNOr++;
 delay(30);
 for (int i=0; i<30; i++) {
 Serial.print(Digit5th, DEC);
 Serial.print(Digit4th, DEC);
 Serial.print(Digit3rd, DEC);
 Serial.print(Digit2nd, DEC);
 Serial.println(tempC, DEC);
 ++tempC; // increment last digit weight by one and returns the new value of x
if (tempC > 9) {
  tempC = 0;        //last digit statement(s)
  ++Digit2nd;   }
if (Digit2nd > 9) {
  Digit2nd = 0;        //2nd digitstatement(s)
  ++Digit3rd;   }
if (Digit3rd > 9) {
  Digit3rd = 0;        //3rd digitstatement(s)
  ++Digit4th;   }
if (Digit4th > 9) {
  Digit4th = 0;        //4th digitstatement(s)
  ++Digit5th;   }
if (Digit5th > 6) {
  Digit5th = 0;        //5th digits max = 60 tonne
  }   }
}
