#include <Arduino.h>

#include <LiquidCrystal.h>


#define buttonUp 11
#define buttonDown 13
#define LedRed 3
#define LedGreen 1
#define LedBlue 2

LiquidCrystal lcd(9,8,7,6,5,4);
int menu =1;
float temperature;

bool psButtonUp;
bool psButtonDown;

void lcdClear(void);

void setup() {
  lcd.begin(16, 2);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(LedBlue, OUTPUT);

}

void loop() {
  dispMenu();
  changeMenu();
  readTemperature();
  changeRGBLed();

}

void dispMenu(void){
  switch (menu){
  case 1:
  	lcd.setCursor(0,0);
  	lcd.print("Temperature:");
  	lcd.setCursor(0,1);
  	lcd.print(temperature);  	
    break;
  case 2:
    lcd.setCursor(0,0);
  	lcd.print("Menu 2");
  	break;
    
  case 3:
    lcd.setCursor(0,0);
  	lcd.print("Menu 3");
  	break;
  }

}

void changeMenu(void){
  if(digitalRead(buttonUp)==HIGH && psButtonUp == LOW){
  psButtonUp =  HIGH;
    menu =menu +1;
    if (menu>3){
    menu =1;}
    lcdClear();
  }

  if(digitalRead(buttonDown)==HIGH && psButtonDown == LOW){
  psButtonDown =  HIGH;
    menu =menu -1;
    if (menu<1){
    menu =3;}
    lcdClear();
  }
 
 psButtonUp = digitalRead(buttonUp);
  psButtonDown = digitalRead(buttonDown);
 
}

void readTemperature(void){
  unsigned int digital = analogRead(A5);
  float resolution = (5.0f/1024.0f);
  float voltage = resolution*digital;
  temperature=(voltage-0.1f)*(125.0f+40.0f)/(1.75f-0.1f)-40.0f;

}

void changeRGBLed(void){
  float change = (temperature+40.0f)*255.0f/(125.0f+40.0f);
  analogWrite(LedRed,0+change);
  analogWrite(LedGreen,0);
  analogWrite(LedBlue,255-change);

}

void lcdClear(void){
lcd.setCursor(0,0);
lcd.print("..............");
lcd.setCursor(0,1);
lcd.print("..............");
}