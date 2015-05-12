#include <Interval.h>



#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif



namespace Asynchrony {

	Interval::Interval(unsigned long time, char timeUnit) {
		switch(timeUnit) {
			case SECOND:
				interval = time * 1000000;
				break;
			case MILLISECOND:
				interval = time * 1000;
				break;
			case MICROSECOND:
			default:
				interval = time;
		}

		targetMicros = lastMicros = micros();

		increaseTarget();
	}

	

	bool Interval::check(bool *selfDestruct) {
		unsigned long curMicros = micros();

		if(curMicros < lastMicros)
			++lastBlock;

		lastMicros = curMicros;

		if(lastBlock == targetBlock && lastMicros >= targetMicros) {
			increaseTarget();
			return true;
		}

		return false;
	}



	void Interval::increaseTarget() {
		unsigned long long target = 
			(
				((unsigned long long)targetBlock << LONG_LENGTH) |
				targetMicros
			) + interval
		;
		targetBlock = target >> LONG_LENGTH;
		targetMicros = target;
	}

}