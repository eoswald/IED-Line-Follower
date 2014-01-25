#define SENSOR A0
#define LED 9
#define PW_LED 10

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(LED, PW_LED);
  Serial.println(analogRead(SENSOR));
}
