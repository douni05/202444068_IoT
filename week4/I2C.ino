#include <Wire.h>  // I2C 통신을 위한 기본 라이브러리
#include <LiquidCrystal_I2C.h> // I2C LCD 라이브러라

// I2C LCD 설정 (주소: 0x27, LCD 크기: 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);
  
void setup()
{
  lcd.init();		// I2C LCD 초기화
  lcd.backlight();	// 백라이트 초기화
  lcd.print("LCD init");
  delay (2000);
  lcd.clear();
}

void loop()
{
  lcd.setCursor(16,0); // 커서를 첫 번째 줄의 16번째 칸으로 이동
  lcd.print("Hello, World");

  // 문자열을 왼쪽으로 스크롤
  for (int position = 0; position < 16; position++) {
  	lcd.scrollDisplayLeft(); // 화면을 왼쪽으로 한 칸씩 이동
    delay(150);
  }
}
