// LED 깜박이는 코드 (Arduino)
// 내장 LED와 7번 핀에 연결된 LED를 1초 간격으로 깜박이게 함

int led_r = 7; // 7번 핀에 연결된 LED
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // 내장 LED를 출력 모드로 설정
  pinMode(led_r, OUTPUT);       // 7번 핀 LED를 출력 모드로 설정
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // 내장 LED ON
  digitalWrite(led_r, HIGH);       // 7번 핀 LED ON
  delay(1000); // Wait for 1000 millisecond(s) 
  digitalWrite(LED_BUILTIN, LOW); // 내장 LED OFF
  digitalWrite(led_r, LOW);       // 7번 핀 LED OFF
  delay(1000); // Wait for 1000 millisecond(s) 
}
