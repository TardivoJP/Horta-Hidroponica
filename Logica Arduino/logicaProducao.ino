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
int pumpState = LOW; // Estado da bomba (LOW = desligada, HIGH = ligada)
unsigned long pumpStartTime; // Momento em que a bomba foi ligada
const int pumpDuration = 25 * 1000; // Duração de irrigação (25 segundos)
const float temperatureThreshold = 30.0; // Limite de temperatura em celsius

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

  dht.begin();
}

void setRelayState(int state) {
  digitalWrite(RELAY_PIN, state);
}

void loop() {
  unsigned long currentMillis = millis();
  DateTime now = rtc.now();

  analogValue = analogRead(LIGHT_SENSOR_PIN);

  if (analogValue < ANALOG_THRESHOLD) {
    setRelayState(LOW);  // ligar o relé
  } else {
    setRelayState(HIGH);  // desligar o relé
  }

  // Verificar se é hora de ligar a bomba
  if ((now.hour() == 6 || now.hour() == 14 || now.hour() == 22) && now.minute() == 0) {
    pumpStartTime = currentMillis;
    pumpState = HIGH;
  }


  // Verificar se a temperatura excede o limite
  float tempC = dht.readTemperature();
  if (!isnan(tempC) && tempC > temperatureThreshold) {
    pumpStartTime = currentMillis;
    pumpState = HIGH;
  }

  // Berificar se já está na hora de desligar a bomba
  if (pumpState == HIGH && currentMillis - pumpStartTime >= pumpDuration) {
    pumpState = LOW;
  }

  // Atualizar o estado da bomba
  setRelayState(pumpState);

  // Enviar os dados pela porta serial
  Serial.print("L:");
  Serial.print(analogValue);
  Serial.print("|T:");
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
