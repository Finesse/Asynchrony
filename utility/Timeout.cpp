#include <Timeout.h>



namespace Asynchrony {

	Timeout::Timeout(unsigned long time, char timeUnit) : Interval(time, timeUnit) {}

	bool Timeout::check(bool *selfDestruct) {
		if(Interval::check(selfDestruct)) {
			*selfDestruct = true;
			return true;
		} else {
			return false;
		}
	}

}