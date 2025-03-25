// 미세먼지 센서를 이용한 아날로그 값 측정 (Arduino)
// A0 핀에서 먼지 센서 값을 읽고 시리얼 모니터에 출력

int Vo = A0;
int V_LED = 2;

float Vo_value;

void setup() {
  Serial.begin(9600);
  pinMode(V_LED, OUTPUT);
  pinMode(Vo, INPUT); 
}

void loop() {
  digitalWrite(V_LED, LOW);
  delayMicroseconds(280);
  Vo_value = analogRead(Vo);   // 센서 값 읽기 (아날로그 입력)
  delayMicroseconds(40);
  digitalWrite(V_LED, HIGH);
  delayMicroseconds(9680);

  Serial.println(Vo_value);

  delay(1000);
}
