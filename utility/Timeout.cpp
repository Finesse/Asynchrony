#include <Timeout.h>



namespace Asynchrony {

	bool Timeout::check(bool *selfDestruct) {
		if(Interval::check(selfDestruct)) {
			*selfDestruct = true;
			return true;
		} else {
			return false;
		}
	}

}