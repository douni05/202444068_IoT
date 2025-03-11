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
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, HIGH); // 343mls
  
  distance = duration * 17 / 1000; 
  Serial.println(distance );
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
