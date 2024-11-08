// Blynk Template and Auth settings
#define BLYNK_TEMPLATE_ID "TMPL3Om3gqo3H"
#define BLYNK_TEMPLATE_NAME "Mini project"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Iy-W8eTvWX3S8UP_HNtUzKbOPt8x8UA3"; // Blynk Auth Token
char ssid[] = "Anti-Virus";                    // Wi-Fi SSID
char pass[] = "12345678";                       // Wi-Fi password

#define RED_PIN D0
#define GREEN_PIN D2
#define BLUE_PIN D1

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

// Blynk virtual pin controls for RGB sliders
BLYNK_WRITE(V0) { redValue = param.asInt(); updateColor(); }
BLYNK_WRITE(V1) { blueValue = param.asInt(); updateColor(); }
BLYNK_WRITE(V2) { greenValue = param.asInt(); updateColor(); }

void updateColor() {
  analogWrite(RED_PIN, 255 - redValue);
  analogWrite(GREEN_PIN, 255 - greenValue);
  analogWrite(BLUE_PIN, 255 - blueValue);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  updateColor();
}

void loop() {
  Blynk.run();

  // Check if data is available from Arduino
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    float temperature, humidity;
    int fanSpeed;

    // Parse the data
    sscanf(data.c_str(), "%f,%f,%d", &temperature, &humidity, &fanSpeed);

    // Update Blynk with the received data
    Blynk.virtualWrite(V3, temperature);
    Blynk.virtualWrite(V4, humidity);
    Blynk.virtualWrite(V5, fanSpeed);
  }
}
