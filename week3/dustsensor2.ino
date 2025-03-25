// 먼지 센서를 이용한 먼지 농도 측정 (Arduino)
// 센서에서 읽은 값을 전압으로 변환하고, 먼지 농도로 계산하여 시리얼 모니터에 출력

int Vo = A0;
int V_LED = 2;

float Vo_value;
float Voltage = 0;
float dustDensity = 0;

void setup() {
  Serial.begin(9600);
  pinMode(V_LED, OUTPUT);
  pinMode(Vo, INPUT); 
}

void loop() {
  digitalWrite(V_LED, LOW);
  delayMicroseconds(280);
  Vo_value = analogRead(Vo);
  delayMicroseconds(40);
  digitalWrite(V_LED, HIGH);
  delayMicroseconds(9680);

  Voltage = Vo_value*5.0 / 1023.0; // 아날로그 값을 전압으로 변환 (5V 기준)
  dustDensity = (Voltage - 0.3)/0.005; // 먼지 농도 계산

  Serial.print("Voltage: ");
  Serial.println(Voltage);
  Serial.print("Dust Density: ");
  Serial.println(dustDensity);

  delay(1000);
}
