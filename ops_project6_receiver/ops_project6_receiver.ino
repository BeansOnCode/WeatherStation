#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <NRF24L01_W.h>
NRF24L01_W radio(7, 8);

void setup()
{
	lcd.init(); // initialize the lcd
	lcd.backlight();
  Serial.begin(9600);

  radio.begin();
  radio.setReceiveAddress("56G78");
  radio.setTransmitAddress("56G79");
  radio.setChannel(52);
}

void loop()
{
	lcd.clear();                 
  lcd.setCursor(0, 0);
  lcd.clear();
  if (radio.available())
  {
    Serial.print("On");
    WeatherReport incomingReport = radio.read();  // Read incoming
    lcd.print("Temp: ");              // Print temperature
    lcd.print(incomingReport.temperature);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(incomingReport.humidity);
    lcd.print("%; ");
    String dayNite = incomingReport.light > 70 ? "Day" : "Night";
    lcd.print(dayNite);
    delay(10000);   
  }
  else{
    delay(1000);
  }
	               
}