includes Test;  // Test.h 헤더 파일 포함. Test.h에서 정의된 상수와 메시지 구조(test_data_msg_t)를 사용하기 위함

configuration TestAppC  // 구성 컴포넌트 정의 시작. TestAppC는 애플리케이션의 컴포넌트를 조합하는 역할
{
}
implementation  // 구현 블록 시작. 컴포넌트 선언과 와이어링 정의
{
    components TestC, MainC;  // TestC(센서 로직 모듈)와 MainC(TinyOS 부팅 관리 컴포넌트) 선언
    components LedsC, new TimerMilliC();  // LedsC(LED 제어), TimerMilliC(밀리초 단위 타이머) 선언. 'new'는 인스턴스 생성

    components ActiveMessageC as AMC;  // ActiveMessageC(무선 통신 제어) 선언. 별칭 AMC로 사용
    components new AMSenderC(AM_TEST_DATA_MSG) as ASMC;  // AMSenderC(메시지 전송 컴포넌트) 선언. AM_TEST_DATA_MSG(0xA4) 타입의 메시지 전송용. 별칭 ASMC

    TestC.Boot -> MainC;  // TestC의 Boot 인터페이스를 MainC의 Boot 인터페이스에 연결. 부팅 이벤트 처리
    TestC.Leds -> LedsC;  // TestC의 Leds 인터페이스를 LedsC에 연결. LED 제어(켜기/끄기/토글)
    TestC.MilliTimer -> TimerMilliC;  // TestC의 MilliTimer 인터페이스를 TimerMilliC에 연결. 주기적 타이머 동작

    TestC.RadioControl -> AMC;  // TestC의 RadioControl 인터페이스를 AMC에 연결. 무선 모듈 켜기/끄기 제어
    TestC.RadioSend -> ASMC;  // TestC의 RadioSend 인터페이스를 ASMC에 연결. 센서 데이터 메시지 전송

    components new SensirionSht11C() as Sht11Ch0C;  // SensirionSht11C(SHT11 온도/습도 센서) 선언. 별칭 Sht11Ch0C
    TestC.Temp -> Sht11Ch0C.Temperature;  // TestC의 Temp 인터페이스를 Sht11Ch0C의 Temperature 인터페이스에 연결. 온도 읽기
    TestC.Humi -> Sht11Ch0C.Humidity;  // TestC의 Humi 인터페이스를 Sht11Ch0C의 Humidity 인터페이스에 연결. 습도 읽기

    components new IlluAdcC() as Illu;  // IlluAdcC(조도 센서) 선언. 별칭 Illu
    TestC.Illu -> Illu;  // TestC의 Illu 인터페이스를 IlluAdcC에 연결. 조도 읽기

    components BatteryC;  // BatteryC(배터리 전압 측정 컴포넌트) 선언
    TestC.Battery -> BatteryC;  // TestC의 Battery 인터페이스를 BatteryC에 연결. 배터리 전압 읽기
}
