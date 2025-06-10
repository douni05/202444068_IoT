## 깃허브용 마크다운 정리 (14주차 사물인터넷 무선 프로토콜)

---

# 14주차 사물인터넷 무선 프로토콜 (Wi-Fi & ZigBee)

## 목차
- Wi-Fi
  - IEEE 표준 비교
  - MAC 서비스 세트
  - MAC 데이터 프레임
  - CSMA/CA 동작 방식
- ZigBee
  - ZigBee 물리 계층
  - MAC 계층 및 슈퍼프레임
  - 분산 주소 할당 기법
  - ZigBee 라우팅 기법 (트리, 메쉬)

---

## Wi-Fi

### IEEE 802.11 표준 비교

| 표준      | 주파수 대역           | 전송 방식/변조         | 도달거리 | MAC 방식  |
|-----------|----------------------|-----------------------|----------|-----------|
| 802.11b   | 2.4GHz               | DSSS, BPSK, QPSK, CCK | ~100m    | CSMA/CA   |
| 802.11a   | 5GHz                 | OFDM, BPSK, QPSK, QAM | ~50m     | CSMA/CA   |
| 802.11g   | 2.4GHz               | OFDM, CCK, QAM        | ~100m    | CSMA/CA   |
| 802.11n   | 2.4/5GHz             | OFDM/OFDMA, MIMO      | ~100m/~50m | CSMA/CA |

---

### Wi-Fi 구성 및 서비스 세트

- **AP(Access Point)**: 유무선 공유기  
- **STA(Station)**: 노트북, 스마트폰 등  
- **BSS(Basic Service Set)**: AP 1개와 여러 STA  
- **ESS(Extended Service Set)**: 여러 BSS가 모여 구성

---

### MAC 계층 및 데이터 프레임

- **PCF(Point Coordination Function)**: 중앙집중식 Polling 방식 (옵션)
- **DCF(Distributed Coordination Function)**: CSMA/CA 사용, 분산 방식

**Data Frame 구조**
```
| Protocol | Type | Subtype | ToDS | FromDS | ... | Address 1 | Address 2 | Address 3 | Address 4 | Frame body | FCS |
```

---

### CSMA/CA 동작 방식

1. 채널 감지 (Carrier Sense)
2. 사용 중이면 랜덤 백오프 (Backoff)
3. RTS(Request To Send) → CTS(Clear To Send) → DATA → ACK 순서로 통신
4. 숨겨진 노드 문제(Stations B, C는 서로의 통신을 감지하지 못함)는 RTS/CTS로 해결

---

## ZigBee

### ZigBee 스택 구조

- Application/Profiles
- Application Framework
- Network/Security Layers
- MAC Layer
- PHY Layer

---

### 물리(PHY) 계층

- **IEEE 802.15.4 기반**
- 3개 밴드(2.4GHz, 915MHz, 868MHz), 총 27채널
- DSSS(Direct Sequence Spread Spectrum) 사용

| 밴드      | 채널 수 | 데이터 속도 | 지역    |
|-----------|--------|-------------|---------|
| 2.4GHz    | 16     | 250kbps     | 전 세계 |
| 915MHz    | 10     | 40kbps      | 미국    |
| 868MHz    | 1      | 20kbps      | 유럽    |

---

### MAC 계층 및 슈퍼프레임

- **기기 종류**: Network Coordinator, Reduced Function Device(RFD), Full Function Device(FFD)
- **비콘 없는(Non-Beacon) 통신**: Non-slotted CSMA-CA, 단순, sleep 기능 제공 어려움
- **비콘(Beacon) 통신**: Slotted CSMA-CA, 슈퍼프레임, 에너지 절약 가능

**슈퍼프레임 구조**
- 최대 16개 슬롯
- Beacon, CAP(Contention Access Period), CFP(Contention Free Period), 비활성화 구간 포함
- GTS(Guaranteed Time Slot)로 슬롯 예약 가능

---

### MAC 프레임 종류

- 비콘 프레임
- 데이터 프레임
- 확인 프레임
- MAC 명령 프레임

---

### ZigBee 주소 체계

- **Extended Address(IEEE Address)**: 64비트, 고유 주소
- **Short Address(NWK Address)**: 16비트, 네트워크 내 할당
- **PAN ID**: 네트워크 식별자

---

### 분산 주소 할당 기법

- ZigBee 라우터가 자식 노드에 16비트 주소 할당
- Cskip(d) 공식으로 주소 공간 계산

$$
Cskip(d) = \frac{1 + Cm - Rm - Cm \times Rm^{(Lm-d-1)}}{1 - Rm}
$$

- Cm: 최대 자식 수  
- Rm: 최대 라우터 수  
- Lm: 네트워크 최대 깊이  
- d: 현재 노드 깊이

---

### 참고

- Wi-Fi와 ZigBee는 모두 2.4GHz 대역을 사용할 수 있으므로, 채널 간섭에 주의 필요
- ZigBee는 저전력, 저속, 다수 노드 네트워크에 적합, Wi-Fi는 고속, 대역폭 중심 네트워크에 적합

