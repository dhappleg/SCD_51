/*
 * Author: Drew Applegath
 * Project: Senior Capstone Design - Team 51
 * Updated: 11/30/2018
 * 
 * About: 
 * Runs the cycles for the test stand and tracks the value of the number
 * of runs of the cycles. 
 */
 
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define _RESET_ 2
#define _COUNTADDR 0
#define _SIGNAL_ 3

LiquidCrystal lcd(13, 12, 4, 5, 6, 7); 
int cycleCount = 0;  

void setup() {
  lcd.begin(16, 2); 
  lcd.print("Initializing...");
  pinMode(_RESET_, INPUT); 
  pinMode(_SIGNAL_, OUTPUT); 
//cycleCount = EEPROM.read(_COUNTADDR); 
  delay(1000); 
}

void loop() {
//poll_input(); 
  update_display(); 
  run_cycle(); 
  update_memcount(); 
}
void poll_input() {
  if(digitalRead(_RESET_)) {
    
    reset_interrupt(); 
  }
}

void reset_interrupt() {
  cycleCount = 0;
}
void update_display() {
  lcd.clear(); 
  lcd.print("Cycles:"); 
  lcd.setCursor(0,1); 
  lcd.print((String) cycleCount); 
}
void run_cycle() {
  analogWrite(_SIGNAL_, 128); // %50 duty cycle
  delay(1000); 
  analogWrite(_SIGNAL_, 34); // %10 duty cycle
  delay(2000); 
  analogWrite(_SIGNAL_, 128); // %50 duty cycle
  delay(2000); 
  analogWrite(_SIGNAL_, 221); // %90 duty cycle
  delay(2000); 
  analogWrite(_SIGNAL_, 128); // %50 duty cycle
  delay(1000); 
  cycleCount++; 
}
void update_memcount() {
  EEPROM.write(_COUNTADDR, cycleCount); 
}
