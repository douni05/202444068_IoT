from influxdb_client import InfluxDBClient
import time
import serial
# === InfluxDB 2.x 설정 ===
influxdb_url = "http://localhost:8086"  # 기본 URL
influxdb_token = "tjX1Cuxp7qJs4mXx9Wkjms6nri8FhUfhyuDOk8I3BZVKOYfz7YOrHWqRxqEALXOTBtoFmIg4StdyFYaAQNzDMA=="
influxdb_org = "test"  # influxDB에서 설정한 조직 이름
influxdb_bucket = "dust"  # 데이터가 저장될 버킷 이름

# === (1) Arduino 시리얼 포트 설정 ===
serial_port = "COM3"  # 아두이노 포트
baudrate = 9600  # 시리얼 통신 속도
timeout = 2  # 타임아웃 (초)

# InfluxDB 2.0 클라이언트 생성
client = InfluxDBClient(url=influxdb_url, token=influxdb_token, org=influxdb_org)

# === (3) InfluxDB 클라이언트 설정 ===
client = InfluxDBClient(url=influxdb_url, token=influxdb_token, org=influxdb_org)
write_api = client.write_api()

# === (4) 시리얼 포트 열기 ===
try:
    ser = serial.Serial(serial_port, baudrate, timeout=timeout)
    print(f"Connected to {serial_port} at {baudrate} baud")
except serial.SerialException:
    print("Failed to connect to serial port.")
    exit()

# === (5) 시리얼 데이터 읽시 및 InfluxDB 저장 ===
try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()  # 시리얼 데이터 읽기
            print(f"Received: {line}")

            # 데이터가 "temperature=25.3" 같은 형식이라고 가정
            if "=" in line:
                key, value = line.split("=")
                try:
                    value = float(value)  # 숫자로 변환
                    # InfluxDB 2.x 데이터 포맷
                    data = f"sensor_data,device=arduino {key}={value}"
                    write_api.write(bucket=influxdb_bucket, record=data)
                    print(f"Data written to InfluxDB: {key}={value}")

                except ValueError:
                    print("Invalid data format")

        time.sleep(1)  # 1초 대기
except KeyboardInterrupt:
    print("Stopping data collection...")

finally:
    ser.close()
