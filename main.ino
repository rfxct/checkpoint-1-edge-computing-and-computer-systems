#define LED_OK 4
#define LED_ALERTA 3
#define LED_PROBLEMA 2

#define LDR_SENSOR A0

#define BUZZER 5

void setup()
{
    pinMode(LED_OK, OUTPUT);
    pinMode(LED_ALERTA, OUTPUT);
    pinMode(LED_PROBLEMA, OUTPUT);

	  Serial.begin(9600);
}

void loop()
{
  int luminosidade = analogRead(LDR_SENSOR);
  // MIN: 6 - MAX: 679

  Serial.println(luminosidade);

  // 6 - 200
  if (luminosidade < 200) {
    // LED OK
    digitalWrite(LED_OK, HIGH);

    // RESET
    digitalWrite(LED_ALERTA, LOW);
    digitalWrite(LED_PROBLEMA, LOW);
  // 200 - 400
  } else if (luminosidade < 450) {
    // LED Alerta
    digitalWrite(LED_ALERTA, HIGH);

    // RESET
    digitalWrite(LED_OK, LOW);
    digitalWrite(LED_PROBLEMA, LOW);

    // Tocar buzina durante 3 segundos
    digitalWrite(BUZZER, HIGH);
    delay(3000);

    // Parar buzina por 2 segundos depois de tocar
    digitalWrite(BUZZER, LOW);
    delay(2000);
  // 400 - 679
  } else {
    // LED Problema
	  digitalWrite(LED_PROBLEMA, HIGH);

    // RESET
    digitalWrite(LED_OK, LOW);
    digitalWrite(LED_ALERTA, LOW);
  }
