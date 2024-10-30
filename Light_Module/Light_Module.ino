// Include the necessary libraries
#define BLYNK_TEMPLATE_ID "TMPL3Om3gqo3H"
#define BLYNK_TEMPLATE_NAME "Mini project"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_AUTH_TOKEN "" // Enter your Blynk auth token
char auth[] = BLYNK_AUTH_TOKEN;
//use 2.4 Hz wifi only as esp8266 doesn't support 5 Hz wifi signals
char ssid[] = ""; // Enter your Wi-Fi SSID
char pass[] = "";     // Enter your Wi-Fi password

#define RED_PIN D0
#define GREEN_PIN D2
#define BLUE_PIN D1

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

// Function to set RGB color based on slider values
void updateColor() {
  analogWrite(RED_PIN, 255 - redValue);
  analogWrite(GREEN_PIN, 255 - greenValue);
  analogWrite(BLUE_PIN, 255 - blueValue);
}

// Blynk virtual pin controls for RGB sliders
BLYNK_WRITE(V0) { // Red slider
  redValue = param.asInt();
  Serial.println(redValue);
  updateColor();
}

BLYNK_WRITE(V2) { // Green slider
  greenValue = param.asInt();
  Serial.println(greenValue);
  updateColor();
}

BLYNK_WRITE(V1) { // Blue slider
  blueValue = param.asInt();
  Serial.println(blueValue);
  updateColor();
}

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Starting setup...");

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to Wi-Fi successfully.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to Wi-Fi.");
  }

  updateColor(); // Initialize the LED with the current color values
}

void loop() {
  Blynk.run();
}
