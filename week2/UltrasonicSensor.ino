// 초음파 센서를 이용한 거리 측정 및 LED 점멸 (Arduino)

#define TRIG 13 // TRIG 판
#define ECHO 12 // ECHO 판

int led_r = 7;
int led_g = 9;

void setup()
{
  Serial.begin(9600);
  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, OUTPUT);
}

void loop()
{
  long duration, distance;
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2); // delay(2)
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10); //10 마이크로초 동안 HIGH 유지 (초음파 발사)
  digitalWrite(TRIG, LOW);
  
   // 초음파가 물체에 반사되어 돌아오는 시간 측정
  duration = pulseIn(ECHO, HIGH); // 343mls

  // 거리 계산 (음속 343m/s = 34300cm/s -> 1us당 0.0343cm 이동)
  distance = duration * 17 / 1000;
  
  // 시리얼 모니터에 거리 출력
  Serial.print("\nDistance : ");
  Serial.print(distance);
  Serial.println(" CM");
  
  digitalWrite(led_r, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(led_r, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(led_g, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(led_g, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
