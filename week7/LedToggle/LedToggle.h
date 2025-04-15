#ifndef LedToggle_h
#define LedToggle_h

#include "Arduino.h"

class LedToggle {
	public:
		LedToggle(int pin); // 생성자
		LedToggle(int pin, unsigned long delayTime);
		void toggle();		// LED 상태 토글
	
 	private:
 		int _pin;
 		bool _state;
 		unsigned long _delayTime;
};

#endif
