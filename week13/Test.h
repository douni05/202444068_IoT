#ifndef TEST_H  // 헤더 파일 중복 포함 방지. TEST_H가 정의되지 않았을 때만 아래 코드 포함
#define TEST_H  
// TEST_H를 정의해 중복 포함 방지
// 헤더 파일의 역할: Test.h는 애플리케이션 전체에서 공유되는 상수와 데이터 구조를 정의합니다. 다른 파일(TestC.nc, TestAppC.nc)에서 이 정의를 사용해 센서 데이터를 일관되게 처리합니다.
#include "message.h"  // TinyOS의 메시지 관련 정의를 포함. Active Message(AM) 타입과 메시지 구조를 위한 헤더 파일

enum {  // 이름 없는 열거형(enum)으로 상수 정의 시작
    TEST_PERIOD = 10240LU,  // 센서 데이터를 주기적으로 읽는 간격(밀리초). 10240ms = 10.24초. 'LU'는 unsigned long 타입 명시
};

enum {  // 또 다른 열거형으로 상수 정의
    DFLT_VAL = 0x11,  // 기본값(16진수 0x11 = 10진수 17). 이 코드에서는 사용되지 않는 것 같음. 예비 상수일 가능성
};

enum {  // 열거형으로 데이터 길이 상수 정의
    TEST_DATA_LENGTH = TOSH_DATA_LENGTH - 6,  // 메시지 페이로드 길이. TOSH_DATA_LENGTH는 TinyOS 상수(보통 28바이트). 6바이트를 빼서 실제 데이터 공간 확보
};

enum {  // 열거형으로 메시지 타입 상수 정의
    AM_TEST_DATA_MSG = 0xA4  // Active Message(AM) 타입 식별자. 0xA4는 이 애플리케이션의 센서 데이터 메시지를 구분하는 고유 값
//AM_TEST_DATA_MSG는 TinyOS의 Active Message 시스템에서 메시지 타입을 구분하는 데 사용. 0xA4는 이 애플리케이션 고유의 식별자
};

typedef nx_struct test_data_msg {  // 네트워크 바이트 순서(nx_struct)로 센서 데이터 메시지 구조 정의. 메시지 패킷 형식 지정
    nx_am_addr_t srcID;  // 소스 노드 ID(2바이트). 데이터를 보낸 센서 노드의 고유 식별자
    nx_uint32_t seqNo;   // 시퀀스 번호(4바이트). 메시지의 순서를 추적해 중복이나 손실 확인
    nx_uint16_t type;    // 메시지 타입(2바이트). 예: 2는 온도/습도/조도(THL) 데이터임을 나타냄
    nx_uint16_t Temp;    // 온도 데이터(2바이트). 센서에서 읽은 온도 값 저장
    nx_uint16_t Humi;    // 습도 데이터(2바이트). 센서에서 읽은 습도 값 저장
    nx_uint16_t Illu;    // 조도 데이터(2바이트). 센서에서 읽은 조명 밝기 값 저장
    nx_uint16_t battery; // 배터리 전압(2바이트). 노드의 배터리 상태 저장
    // nx_uint8_t testData[TEST_DATA_LENGTH];  // 주석 처리된 테스트 데이터 배열. 추가 데이터를 위한 공간(현재 사용 안 함)
} test_data_msg_t;  // 구조체 이름 정의. 이 구조체는 센서 데이터 패킷의 형식

// 네트워크 바이트 순서 (nx_): nx_ 접두사는 데이터를 네트워크에서 전송할 때 바이트 순서를 일정하게 유지(빅엔디언)하도록 합니다. 이는 서로 다른 하드웨어 간 데이터 호환성을 보장합니다.
#endif // TEST_H  // 헤더 파일 끝. TEST_H 정의로 중복 포함 방지
