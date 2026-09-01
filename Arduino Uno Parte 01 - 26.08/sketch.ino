#include "DHT.h"

// Configuração e E/S digital e analógica
const int BTN = 2;
const int LED = 13; // Mantido pino 13 conforme sua montagem
const int POT = A0;
const int DHTPIN = 7;

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // configuração executada uma vez
  Serial.begin(9600);
  
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  dht.begin();
  
  Serial.println("--- Sistema Iniciado ---");
}

void loop() {
  // lógica repetida continuamente
  
  // Leitura do Botão com inversão de estado
  bool ativo = digitalRead(BTN) == LOW;
  digitalWrite(LED, ativo ? HIGH : LOW);

  // Leitura analógica introdutória
  int bruto = analogRead(POT);

  // Leitura do DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Impressão dos dados
  Serial.print("Botao ativo: ");
  Serial.print(ativo);
  Serial.print(" | Potenciometro (bruto): ");
  Serial.print(bruto);
  Serial.print(" | Temp: ");
  Serial.print(temperature);
  Serial.print(" C | Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(1000);
}