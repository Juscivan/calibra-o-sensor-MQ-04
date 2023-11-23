// Defina o pino ao qual o sensor está conectado
const int pinSensor = 34; // D34 no ESP32

// Variáveis para calibração
float valorLido;
float valorLimiteInferior = 200; // Ajuste conforme necessário
float valorLimiteSuperior = 800; // Ajuste conforme necessário

void setup() {
  Serial.begin(9600);
  calibrarSensor();
}

void loop() {
  valorLido = analogRead(pinSensor);
  float ppm = map(valorLido, 0, 4095, 0, 10000); // Mapeie os valores lidos para ppm (partes por milhão)
  
  Serial.print("Valor lido: ");
  Serial.print(valorLido);
  Serial.print("\tPPM: ");
  Serial.println(ppm);

  if (ppm >= valorLimiteInferior && ppm <= valorLimiteSuperior) {
    Serial.println("Sensor regulado. Níveis de gás aceitáveis.");
  } else {
    Serial.println("Atenção! Níveis de gás fora da faixa aceitável.");
  }

  delay(1000); // Aguarde 1 segundo antes de ler novamente
}

void calibrarSensor() {
  Serial.println("Calibrando o sensor. Aguarde...");

  // Leitura inicial para obter um valor base
  valorLido = analogRead(pinSensor);
  
  // Aguarde alguns segundos para permitir a estabilização do sensor
  delay(5000);

  // Realize várias leituras e ajuste os valores limite
  for (int i = 0; i < 10; i++) {
    valorLido = analogRead(pinSensor);
    valorLimiteInferior = min(valorLimiteInferior, valorLido);
    valorLimiteSuperior = max(valorLimiteSuperior, valorLido);
    delay(500);
  }

  Serial.print("Calibração concluída. Faixa aceitável: ");
  Serial.print(valorLimiteInferior);
  Serial.print(" - ");
  Serial.println(valorLimiteSuperior);
}
