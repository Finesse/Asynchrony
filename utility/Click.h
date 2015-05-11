/*
	Event listener that watches button state, filters bounce and triggers event when button is in specified state.
*/

#ifndef Asynchrony_Click_h
#define Asynchrony_Click_h




#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#include <utility/Listener.h>



namespace Asynchrony {

	const char UNDEFINED = -1;

	class Click : public Listener {
		public:
			/*
				Creates event listener that watches button state, filters bounce and triggers event when button is in specified state.

				Parameters:
					int pin — Button pin.
					bool eventState — Button state in which event triggers.
					char mode — In which mode button pin should be turned. Variants are: INPUT, INPUT_PULLUP and Asynchrony::UNDEFINED (where pin mode shouldn't be changed). Default is Asynchrony::UNDEFINED.
					unsigned long bounce — Bounce duration in microseconds. Default is 10000.
			*/
			Click(int pin, bool eventState = HIGH, char mode = UNDEFINED, unsigned long bounce = DEFAULT_BOUNCE);

			/*
				(watch Listener documentation)
			*/
			virtual bool check(bool *selfDestruct);

			// Default bounce duration in microseconds.
			static const unsigned long DEFAULT_BOUNCE = 10000;

		protected:
			// Button pin
			int buttonPin;

			// Is state changing suspected
			bool checking = false;

			// Time when bounce shoun be over and when recheck state
			unsigned long checkTime;

			// Button state in which event triggers
			bool event;

			// Current state
			bool state;

			// Bounce duration in microseconds
			unsigned long bounceDuration;
	};

}



#endif