#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <NRF24L01_W.h>

NRF24L01_W radio(7, 8);

const int DHTinput = 4;
const int DAYSENS = 2;

DHT weatherSensor(DHTinput, DHT11);

void setup() {
  // put your setup code here, to run once:
  weatherSensor.begin();
  Serial.begin(9600);

  radio.begin();
  radio.setReceiveAddress("56G79");
  radio.setTransmitAddress("56G78");
  radio.setChannel(52);

}

void loop() {
  // put your main code here, to run repeatedly:
  int h = weatherSensor.readHumidity();
  int t = weatherSensor.readTemperature();

  int time = analogRead(DAYSENS);

  String dayNite = time > 100 ? "Day" : "Night";

  WeatherReport report;
  report.temperature = t;
  report.humidity = h;
  report.light = time;

  radio.write(report);

  delay(10000);
}
