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
			Click(int pin, bool eventState = HIGH, char mode = UNDEFINED, unsigned long bounce = DEFAULT_BOUNCE);

			virtual bool check(bool *selfDestruct);

			static const unsigned long DEFAULT_BOUNCE = 10000;

		protected:
			// Пин входного сигнала
			int buttonPin;

			// Включено ли подозрение на смену состояния
			bool checking = false;

			// Время, когда надо перепроверить подозрение на смену состояния
			unsigned long checkTime;

			// Состояние, которое нужно зафиксировать для срабатывания события
			bool event;

			// Текущее состояние
			bool state;

			// Длительность дребезга в микросекундах
			unsigned long bounceDuration;
	};

}



#endif