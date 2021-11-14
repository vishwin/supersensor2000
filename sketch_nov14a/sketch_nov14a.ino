#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);

#define RED 13
#define GREEN 12
#define BLUE 11
#define WHITE 10
#define LIGHT A5

bool red=0;
bool green=0;
bool blue=0;
bool white=0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RED, OUTPUT);
  digitalWrite(RED, LOW);
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN, LOW);
  pinMode(BLUE, OUTPUT);
  digitalWrite(BLUE, LOW);
  pinMode(WHITE, OUTPUT);
  digitalWrite(WHITE, LOW);
  pinMode(LIGHT, INPUT);
}

void loop() {
  int lightLevel=analogRead(A5);
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.println("<p id='humDC' data-color='60'>Humidity</p>");
  Serial.print("<p id='humidity'>");
  Serial.print(h);
  Serial.println("%</p>");
  Serial.println("<p data-color='60'>Air Temperature</p>");
  Serial.print("<p id='airtemp'>");
  Serial.print(t);
  Serial.println("°C</p>");
  Serial.println("<p data-color='19'>Light On</p>");
  Serial.print("<p id='light'>");
  if (lightLevel > 440) {
    digitalWrite(WHITE, HIGH);
    Serial.print("On");
  }
  else {
    digitalWrite(WHITE, LOW);
    Serial.print("Off");
  }
  Serial.println("</p>");
  Serial.println("");

  delay(2000);
}
