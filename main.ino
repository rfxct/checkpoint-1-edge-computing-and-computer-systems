#define LED_OK 4
#define LED_ALERTA 3
#define LED_PROBLEMA 2

#define LDR_SENSOR A0
#define BUZZER 5

long tempoInicio = 0;
bool buzzerAtivo = false;
bool aguardandoReset = false;

void setup()
{
  pinMode(LED_OK, OUTPUT);
  pinMode(LED_ALERTA, OUTPUT);
  pinMode(LED_PROBLEMA, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  // MIN: 6 - MAX: 679
  int luminosidade = analogRead(LDR_SENSOR);

  // 6 - 200
  if (luminosidade < 200) {
    // LED OK
    digitalWrite(LED_OK, HIGH);

    // RESET
    digitalWrite(LED_ALERTA, LOW);
    digitalWrite(LED_PROBLEMA, LOW);
    // 200 - 450
  } else if (luminosidade < 450) {
    // LED Alerta
    digitalWrite(LED_ALERTA, HIGH);

    // RESET
    digitalWrite(LED_OK, LOW);
    digitalWrite(LED_PROBLEMA, LOW);

    Serial.println("AGUARDANDO-RESET = " + String(aguardandoReset));
    // Caso o LED ainda esteja em estado de Alerta, ele espera 1,5s para reiniciar o buzzer após ele tocar por 3s
    if (!aguardandoReset) {
      Serial.println("BUZZER-ATIVO = " + String(buzzerAtivo));

      if (!buzzerAtivo) {
        tempoInicio = millis();
        buzzerAtivo = true;
      } else if (millis() - tempoInicio <= 3000) {
        digitalWrite(BUZZER, HIGH); // Liga o buzzer
      } else {
        // Desliga o buzzer após 3 segundos
        digitalWrite(BUZZER, LOW);
        buzzerAtivo = false;
        aguardandoReset = true;
      }
    } else if (millis() - tempoInicio >= 1500) {
      aguardandoReset = false;
    }
    // 450 - 679
  } else {
    // LED Problema
    digitalWrite(LED_PROBLEMA, HIGH);

    // RESET
    digitalWrite(LED_OK, LOW);
    digitalWrite(LED_ALERTA, LOW);
  }
}