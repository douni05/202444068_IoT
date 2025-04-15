#ifndef LedToggle_h
#define LedToggle_h

#include "Arduino.h"

class LedToggle {
	public:
		LedToggle(int pin); // »ý¼ºÀÚ
		void toggle();		// LED »óÅÂ Åä±Û
	
 	private:
 		int _pin;
 		bool _state;
};

#endif
