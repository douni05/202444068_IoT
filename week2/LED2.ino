// LED 깜박이는 코드 (Arduino)
// 7번 핀(빨간 LED)과 9번 핀(초록 LED)을 1초 간격으로 번갈아가며 깜박이게 함

int led_r = 7; // 빨간색 LED (Red LED) - 7번 핀
int led_g = 9; // 초록색 LED (Green LED) - 9번 핀

void setup()
{
  pinMode(led_r, OUTPUT); // 7번 핀을 출력 모드로 설정
  pinMode(led_g, OUTPUT); // 9번 핀을 출력 모드로 설정
}

void loop()
{
  digitalWrite(led_r, HIGH); // 7번 핀 ON
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(led_r, LOW); // 7번 핀 OFF
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(led_g, HIGH); // 9번 핀 ON
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(led_g, LOW); // 9번 핀 OFF
  delay(1000); // Wait for 1000 millisecond(s)
}
