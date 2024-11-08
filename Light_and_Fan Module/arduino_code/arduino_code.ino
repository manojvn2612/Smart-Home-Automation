#include <DHT.h>

#define DHTPIN 5       // DHT sensor pin
#define DHTTYPE DHT22  // DHT sensor type
#define FAN_PIN 9      // Fan connected to PWM pin 9

DHT dht(DHTPIN, DHTTYPE);

float thresholdTemp = 30.0; // Temperature threshold
int fanSpeed = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(FAN_PIN, OUTPUT);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Control fan speed based on temperature
  fanSpeed = map(constrain(temperature, 20, thresholdTemp), 20, thresholdTemp, 0, 255);
  analogWrite(FAN_PIN, fanSpeed);

  // Send data to ESP8266 via serial
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(fanSpeed);

  delay(2000); // Delay to avoid flooding the serial communication
}
