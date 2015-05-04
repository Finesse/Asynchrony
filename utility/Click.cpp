#include <Click.h>



namespace Asynchrony {

	Click::Click(int pin, bool pullup, bool eventState, unsigned long bounce) {
		buttonPin = pin;
		event = eventState;
		bounceDuration = bounce;
		state = !eventState;

		pinMode(pin, pullup ? INPUT_PULLUP : INPUT);
	}



	bool Click::check(bool *selfDestruct) {
		if(checking) {

			if(micros() >= checkTime) {
				checking = false;
				bool stateCur = digitalRead(buttonPin);
				if(stateCur != state) {
					state = stateCur;
					if(stateCur == event)
						return true;
				}
			}

		} else {

			if(digitalRead(buttonPin) != state) {
				checking = true;
				checkTime = micros() + bounceDuration;
			}

		}

		return false;
	}

}