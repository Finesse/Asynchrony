/*
	Event listener that infinitely triggers events on the same time interval.
*/

#ifndef Asynchrony_Interval_h
#define Asynchrony_Interval_h



#include <utility/Listener.h>



namespace Asynchrony {

	const char SECOND = 0;
	const char MILLISECOND = 1;
	const char MICROSECOND = 2;

	class Interval : public Listener {
		public:
			/*
				Creates event listener that infinitely triggers events on the same time interval.

				Parameters:
					unsigned long time — Interval duration in units specified in timeUnit parameter.
					char timeUnit — Unit in which time parameter is specified. Variants: Asynchrony::MICROSECOND, Asynchrony::MILLISECOND and Asynchrony::SECOND. Default is Asynchrony::MILLISECOND.
			*/
			Interval(unsigned long time, char timeUnit = MILLISECOND);

			/*
				(watch Listener documentation)
			*/
			virtual bool check(bool *selfDestruct);

		protected:
			static const char LONG_LENGTH = sizeof(long) << 3;

			// Time intervel in microseconds
			unsigned long long interval;

			// Last checked time
			unsigned long lastBlock = 0;
			unsigned long lastMicros = 0;

			// Time when event should be triggered
			unsigned long targetBlock = 0;
			unsigned long targetMicros = 0;

			/*
				Sets new triggering time by adding interval to previous triggering time.
			*/
			void increaseTarget();
	};

}



#endif