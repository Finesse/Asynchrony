#ifndef Asynchrony_Interval_h
#define Asynchrony_Interval_h



#include <utility/Listener.h>



namespace Asynchrony {

	class Interval : public Listener {
		public:
			Interval(unsigned long time, char timeUnit = MILLISECOND);

			virtual bool check(bool *selfDestruct);

			static const char SECOND = 0;
			static const char MILLISECOND = 1;
			static const char MICROSECOND = 2;

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