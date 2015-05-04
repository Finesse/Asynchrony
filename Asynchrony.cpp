#include <Asynchrony.h>

#ifndef NULL
#define NULL 0
#endif

namespace Asynchrony {

	identificator Asynchrony::addListener(Listener* listener, void (*callback)(), int priority) {
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



	identificator Asynchrony::getIdentificator() {
		return ++lastIdentificator;
	}



	void Asynchrony::removeListener(identificator id, bool deleteListener) {
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
			} {
				itPrev = itNext;
				++itNext;
			}
		}
	}
}

Asynchrony::Asynchrony Asyn;