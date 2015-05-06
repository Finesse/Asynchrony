#include <Asynchrony.h>

#ifndef NULL
	#define NULL 0
#endif

namespace Asynchrony {

	void Asynchrony::loop() {
		bool destructFlag = false;
		ForwardList<ListenerItem>::Iterator itPrev = listeners.beforeBegin(),
											itNext = itPrev;
		++itNext;

		while(true) {
			if(itNext == NULL) {
				break;
			} else {
				if((*itNext).listener->check(&destructFlag))
					(*itNext).callback();

				if(destructFlag) {
					delete (*itNext).listener;
					itPrev.eraseAfter();
					destructFlag = false;

					itNext = itPrev;
				} else {
					itPrev = itNext;
				}
				++itNext;
			}
		}
	}



	identificator Asynchrony::add(Listener* listener, void (*callback)(), int priority) {
		ListenerItem item;
		item.listener = listener;
		item.callback = callback;
		item.priority = priority;
		item.id = getIdentificator();

		ForwardList<ListenerItem>::Iterator itPrev = listeners.beforeBegin(),
											itNext = itPrev;
		++itNext;

		while(true) {
			if(itNext == NULL || priority > (*itNext).priority) {
				itPrev.insertAfter(item);
				break;
			} else {
				itPrev = itNext;
				++itNext;
			}
		}

		return item.id;
	}



	void Asynchrony::remove(identificator id, bool deleteListener) {
		ForwardList<ListenerItem>::Iterator itPrev = listeners.beforeBegin(),
											itNext = itPrev;
		++itNext;

		while(true) {
			if(itNext == NULL) {
				break;
			} else if(id == (*itNext).id) {
				if(deleteListener)
					delete (*itNext).listener;
				itPrev.eraseAfter();
				break;
			} else {
				itPrev = itNext;
				++itNext;
			}
		}
	}



	identificator Asynchrony::getIdentificator() {
		return ++lastIdentificator;
	}




	#if defined(ARDUINO)

		identificator Asynchrony::click(void (*callback)(), int pin, bool eventState, char mode, unsigned long bounce) {
			return add(new Click(pin, eventState, mode, bounce), callback);
		}



		identificator Asynchrony::interval(void (*callback)(), unsigned long time, char timeUnit) {
			return add(new Interval(time, timeUnit), callback);
		}



		identificator Asynchrony::timeout(void (*callback)(), unsigned long time, char timeUnit) {
			return add(new Timeout(time, timeUnit), callback);
		}

	#endif
}

Asynchrony::Asynchrony Asyn;