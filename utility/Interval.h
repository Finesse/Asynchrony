#ifndef Asynchrony_Interval_h
#define Asynchrony_Interval_h



#include <utility/Listener.h>



namespace Asynchrony {

	const char SECOND = 0;
	const char MILLISECOND = 1;
	const char MICROSECOND = 2;

	class Interval : public Listener {
		public:
			Interval(unsigned long time, char timeUnit = MILLISECOND);

			virtual bool check(bool *selfDestruct);

		protected:
			static const char LONG_LENGTH = 32;

			// Интервал между срабатываниями в микросекунд
			unsigned long long interval;

			// Последнее измеренное
			unsigned long lastBlock = 0;
			unsigned long lastMicros = 0;

			// Номер микросекунды, когда должно произойти срабатывание
			unsigned long targetBlock = 0;
			unsigned long targetMicros = 0;

			void increaseTarget();
	};

}



#endif