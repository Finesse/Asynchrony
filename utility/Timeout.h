#ifndef Asynchrony_Timeout_h
#define Asynchrony_Timeout_h



#include <utility/Interval.h>



namespace Asynchrony {

	class Timeout : public Interval {
		public:
			Timeout(unsigned long time, char timeUnit = MILLISECOND);

			virtual bool check(bool *selfDestruct);
	};

}



#endif