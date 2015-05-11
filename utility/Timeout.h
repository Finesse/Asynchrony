/*
	Event listener that triggers single event after specified time runs out. After triggering listener is removed.
*/

#ifndef Asynchrony_Timeout_h
#define Asynchrony_Timeout_h



#include <utility/Interval.h>



namespace Asynchrony {

	class Timeout : public Interval {
		public:
			/*
				Creates event listener that triggers single event after specified time runs out. After triggering listener is removed.

				Parameters:
					unsigned long time — Interval duration in units specified in timeUnit parameter.
					char timeUnit — Unit in which time parameter is specified. Variants: Asynchrony::MICROSECOND, Asynchrony::MILLISECOND and Asynchrony::SECOND. Default is Asynchrony::MILLISECOND.
			*/
			Timeout(unsigned long time, char timeUnit = MILLISECOND);

			/*
				(watch Listener documentation)
			*/
			virtual bool check(bool *selfDestruct);
	};

}



#endif