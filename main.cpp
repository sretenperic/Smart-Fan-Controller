#include <DHT.h>

#define DHTPIN 2       // Pin na koji je spojen DHT11
#define DHTTYPE DHT11  // Tip senzora
#define FANPIN 9       // Pin na koji je spojen ventilator (PWM)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(FANPIN, OUTPUT);
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  int fanSpeed = 0;

  if (temp <= 25) {
    fanSpeed = 0; 
  } else if (temp > 25 && temp < 35) {
    fanSpeed = map(temp, 25, 35, 50, 255);
  } else {
    fanSpeed = 255;
  }

  analogWrite(FANPIN, fanSpeed);

  delay(2000);
}
