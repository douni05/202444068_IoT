# 라즈베리파이 OpenCV && USB Camera &&Telegram
1. pip OpenCV 설치
   - sudo rm /usr/lib/python3.11/EXTERNALLY-MANAGED
   - free -m : 메모리 확인
   - sudo vim /etc/dphys-swapfile  
   - CONF_SWAPSIZE = 200 -> 2048로 변경
   - pip install opencv-contrib-python
   - sudo apt-get install python3-opencv
2. 라즈베리파이 + 텔레그램 연동
   - 텔레그램 봇 만들기 /start, /newbot
   - pip install python-telegram-bot --upgrade : telegram API 설치
   - git clone https://github.com/python-telegram-bot/python-telegram-bot --recursive
   - TimerBot.py 텔레그램봇 토큰 수정
   
