#ifndef Asynchrony_Click_h
#define Asynchrony_Click_h




#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <utility/Listener.h>



namespace Asynchrony {

	class Click : public Listener {
		public:
			Click(int pin, bool pullup = false, bool eventState = HIGH, unsigned long bounce = 10000);

			virtual bool check(bool *selfDestruct);

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