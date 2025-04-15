#ifndef LedToggle_h
#define LedToggle_h

#include "Arduino.h"

class LedToggle {
	public:
		LedToggle(int pin); // ������
		void toggle();		// LED ���� ���
	
 	private:
 		int _pin;
 		bool _state;
};
