
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <LiquidCrystal_PCF8574.h>

Adafruit_SHT31 sth31 = Adafruit_SHT31();
LiquidCrystal_PCF8574 lcd(0x27);

int lcd_error = -1;
int sth31_error = -1;

void setup() {
  Serial.begin(9600);

  while(!Serial)
    delay(10);

// Połączenie z czujnikiem temperatury i wilgotności SHT31
  Serial.println("Test SHT31");
  if (!sth31.begin(0x44)) {
    Serial.println("Nie znaleziono SHT31");
    while(1)
      delay(1);
  }
  else {
    sth31_error = 0;
    Serial.println("Znaleziono SHT31");
  }

// Połączenie z wyświetlaczem LCD 4x20 
  Serial.println("Test LCD");
  Wire.begin();
  Wire.beginTransmission(0x27);
  if (Wire.endTransmission() == 0) {
    Serial.println("Znaleziono LCD");
    lcd_error = 0;
    lcd.begin(20, 4);
  }
  else {
    Serial.println("Nie znaleziono LCD");
  }

  if (lcd_error == 0) {
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("Dzien dobry");
    delay(10);
    lcd.clear();
  }
}

void loop() {
  if (lcd_error == 0) {
    if (sth31_error == 0) {
      float temp = sth31.readTemperature();
      float humi = sth31.readHumidity();
      
      if (! isnan(temp)) {  
        lcd.setCursor(0, 0);
        lcd.print("Temp = ");
        lcd.setCursor(7, 0);
        lcd.print(temp);
        lcd.setCursor(13,0);
        lcd.print("*C");
      } 
      else { 
        lcd.setCursor(0, 0);
        lcd.print("Blad odczytu temp");
      }
  
      if (! isnan(humi)) {  
        lcd.setCursor(0, 2);
        lcd.print("Wilg = ");
        lcd.setCursor(7, 2);
        lcd.print(humi);
        lcd.setCursor(13,2);
        lcd.print("%RH");
      } 
      else { 
       lcd.setCursor(0, 2);
        lcd.print("Blad odczytu wilgo");
      }

      delay(1000);
    }
  }
}
