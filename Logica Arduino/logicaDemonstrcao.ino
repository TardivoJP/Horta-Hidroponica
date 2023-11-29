#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

RTC_DS3231 rtc;

const int RELAY_PIN = 2; // o pino do Arduino, que se conecta ao pino IN do relé
const int ANALOG_THRESHOLD = 150; // constante que estabelece o limite de luminosidade
const int LIGHT_SENSOR_PIN = A0; // pino do Arduino conectado ao pino do sensor de luz
int analogValue; // valor de leitura da luminosidade
long startTime;
unsigned long previousMillis = 0;
const long interval = 10000; // tempo em milisegundos para ligar e desligar a bomba
int booleanValue = 0; // estado de liga e desliga da bomba

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(4, OUTPUT);

  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  startTime = millis();

  dht.begin();
}

void setRelayState(int state) {
  digitalWrite(RELAY_PIN, state);
}

void loop() {
  unsigned long currentMillis = millis();

  analogValue = analogRead(LIGHT_SENSOR_PIN);

  if (analogValue < ANALOG_THRESHOLD) {
    setRelayState(LOW);  // ligar o relé
  } else {
    setRelayState(HIGH);  // desligar o relé
  }
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (booleanValue == 0) {
      digitalWrite(4, HIGH);
      booleanValue = 1;
    } else {
      digitalWrite(4, LOW);
      booleanValue = 0;
    }
  }


  // Enviar os dados pela porta serial
  Serial.print("L:");
  Serial.print(analogValue);
  Serial.print("|T:");

  float tempC = dht.readTemperature();

  if (isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print(tempC);
  }

  // Enviar dados do estado do pino 4
  Serial.print("|D4:");
  Serial.print(digitalRead(4));

  Serial.println(); // Fim da linha de dados
  delay(1000); // Delay de 1 segundo

}
