module TestC  // 모듈 컴포넌트 정의 시작. TestC는 센서 노드의 로직을 구현
{
    uses {  // TestC가 사용할 인터페이스 목록
        interface Boot;  // 부팅 인터페이스. 시스템 시작 시 호출
        interface Leds;  // LED 제어 인터페이스. LED 켜기/끄기/토글
        interface Timer<TMilli> as MilliTimer;  // 밀리초 단위 타이머 인터페이스. 주기적 작업 실행
        interface SplitControl as RadioControl;  // 무선 모듈 제어 인터페이스. 무선 켜기/끄기
        interface AMSend as RadioSend;  // 메시지 전송 인터페이스. 센서 데이터 전송
        interface Read<uint16_t> as Temp;  // 온도 센서 읽기 인터페이스. 16비트 데이터 반환
        interface Read<uint16_t> as Humi;  // 습도 센서 읽기 인터페이스. 16비트 데이터 반환
        interface Read<uint16_t> as Illu;  // 조도 센서 읽기 인터페이스. 16비트 데이터 반환
        interface Battery;  // 배터리 전압 읽기 인터페이스
    }
}
implementation  // 구현 블록 시작. 인터페이스와 로직 정의
{
    message_t testMsgBffr;  // 메시지 버퍼. TinyOS 메시지 전송에 사용
    test_data_msg_t *testMsg;  // Test.h에서 정의된 메시지 구조체 포인터. 데이터 패킹용
    uint32_t seqNo;  // 메시지 시퀀스 번호. 전송 순서 추적
    uint8_t step;  // 센서 읽기 단계(0: 온도, 1: 습도, 2: 조도, 3: 배터리 및 전송)

    task void startTimer();  // 타이머 시작 태스크 선언. 주기적 작업 시작
    event void Boot.booted() {  // 부팅 완료 이벤트. 시스템 시작 시 호출
        testMsg = (test_data_msg_t *) call RadioSend.getPayload(&testMsgBffr, sizeof(test_data_msg_t));  // 메시지 페이로드 초기화. 버퍼에서 구조체 포인터 얻음
        testMsg->srcID = TOS_NODE_ID;  // 메시지에 현재 노드 ID 설정. TOS_NODE_ID는 노드 고유 식별자
        seqNo = 0;  // 시퀀스 번호 초기화
        post startTimer();  // startTimer 태스크 호출. 타이머 시작 준비
    }

    task void startTimer() {  // 타이머 시작 태스크 정의
        call MilliTimer.startPeriodic(TEST_PERIOD);  // Test.h의 TEST_PERIOD(10.24초) 주기로 타이머 시작
    }

    task void radioOn();  // 무선 모듈 켜기 태스크 선언
    event void MilliTimer.fired() {  // 타이머 만료 이벤트. 10.24초마다 호출
        post radioOn();  // radioOn 태스크 호출. 무선 모듈 시작
    }

    void startDone();  // 무선 모듈 시작 완료 처리 함수 선언
    task void radioOn() {  // 무선 모듈 켜기 태스크 정의
        if (call RadioControl.start() != SUCCESS) startDone();  // 무선 모듈 시작. 실패 시 startDone 호출
    }

    event void RadioControl.startDone(error_t error) {  // 무선 모듈 시작 완료 이벤트
        startDone();  // startDone 함수 호출. 성공/실패 여부 상관없이 다음 단계로
    }

    task void readTask();  // 센서 읽기 태스크 선언
    void startDone() {  // 무선 모듈 시작 완료 처리 함수
        step = 0;  // 센서 읽기 단계 초기화(0부터 시작)
        post readTask();  // readTask 호출. 센서 읽기 시작
        call Leds.led0Toggle();  // LED0 토글. 무선 시작 표시
    }

    void sendDone();  // 메시지 전송 완료 처리 함수 선언
    task void sendTask() {  // 메시지 전송 태스크 정의
        testMsg->seqNo = seqNo++;  // 메시지에 시퀀스 번호 설정 후 증가
        testMsg->type = 2;  // 메시지 타입을 2로 설정(THL: 온도/습도/조도)
        if (call RadioSend.send(AM_BROADCAST_ADDR, &testMsgBffr, sizeof(test_data_msg_t)) != SUCCESS) sendDone();  // 메시지 브로드캐스트. 실패 시 sendDone 호출
        call Leds.led2Toggle();  // LED2 토글. 전송 시작 표시
    }

    event void RadioSend.sendDone(message_t *msg, error_t error) {  // 메시지 전송 완료 이벤트
        sendDone();  // sendDone 함수 호출. 전송 완료 처리
    }

    task void radioOff();  // 무선 모듈 끄기 태스크 선언
    void sendDone() {  // 메시지 전송 완료 처리 함수
        call Leds.led0Off();  // LED0 끄기
        call Leds.led1Off();  // LED1 끄기
        call Leds.led2Off();  // LED2 끄기. 전송 완료 후 모든 LED 끄기
    }

    void stopDone();  // 무선 모듈 종료 완료 처리 함수 선언
    task void radioOff() {  // 무선 모듈 끄기 태스크 정의
        if (call RadioControl.stop() != SUCCESS) stopDone();  // 무선 모듈 끄기. 실패 시 stopDone 호출
    }

    event void RadioControl.stopDone(error_t error) {  // 무선 모듈 종료 완료 이벤트
        stopDone();  // stopDone 함수 호출. 종료 처리
    }

    void stopDone() {  // 무선 모듈 종료 완료 처리 함수
        // 현재 아무 동작 없음. 필요 시 추가 로직 삽입 가능
    }

    task void readTask() {  // 센서 읽기 태스크 정의
        switch(step) {  // step 값에 따라 센서 읽기 순서 제어
            case 0:  // 단계 0: 온도 읽기
                call Temp.read(); break;  // 온도 센서 읽기 시작
            case 1:  // 단계 1: 습도 읽기
                call Humi.read(); break;  // 습도 센서 읽기 시작
            case 2:  // 단계 2: 조도 읽기
                call Illu.read(); break;  // 조도 센서 읽기 시작
            default:  // 단계 3: 배터리 읽고 전송
                testMsg->battery = call Battery.getVoltage();  // 배터리 전압 읽어 메시지에 저장
                post sendTask();  // sendTask 호출. 데이터 전송 시작
                break;
        }
        step += 1;  // 다음 단계로 이동
    }

    event void Temp.readDone(error_t error, uint16_t val) {  // 온도 읽기 완료 이벤트
        // if (error != SUCCESS) call Leds.led0On();  // 주석 처리됨. 오류 시 LED0 켜기(디버깅용)
        testMsg->Temp = error == SUCCESS ? val : 0xFFFA;  // 성공 시 온도 값 저장, 실패 시 0xFFFA
        post readTask();  // readTask 호출. 다음 센서 읽기
    }

    event void Humi.readDone(error_t error, uint16_t val) {  // 습도 읽기 완료 이벤트
        // if (error != SUCCESS) call Leds.led1On();  // 주석 처리됨. 오류 시 LED1 켜기(디버깅용)
        testMsg->Humi = error == SUCCESS ? val : 0xFFFB;  // 성공 시 습도 값 저장, 실패 시 0xFFFB
        post readTask();  // readTask 호출. 다음 센서 읽기
    }

    event void Illu.readDone(error_t error, uint16_t val) {  // 조도 읽기 완료 이벤트
        testMsg->Illu = error == SUCCESS ? val : 0xFFFC;  // 성공 시 조도 값 저장, 실패 시 0xFFFC
        post readTask();  // readTask 호출. 다음 단계(배터리 및 전송)
    }
}
