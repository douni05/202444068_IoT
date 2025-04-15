int a1 = 2;
int a2 = 3;
int a3;

void setup() {
  Serial.begin(115200);
  Serial.println();

  //아래 a1, a2는 인수(argument)임
  a3 = sum(a1,a2);
  Serial.println(a3);
}

void loop() {
}

//아래 a,b는 매개 변수(parameter)임
int sum(int a, int b) {
  int c = a + b;
  return c;
}
