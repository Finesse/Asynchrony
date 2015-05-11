/*
	Asynchrony is tool for hooking actions to different events by using listeners.
	You can:
		* Add listeners that means assigning action (any function you like) to event (for example, key pressing).
		* Remove listener.

	Some common event listeners are included (list of them is located in this code below). You can create your own listeners by implementing abstract class Listener. Each required file is already included (no need to add extra #include, only #include <Asynchrony.h>).

	Every actions should be done through the global object Asyn which is instanse of Asynchrony class.

	The tool is planform indepanded. Some listeners are platform depanded so they are automaticaly included only if supported by platform.
*/

#ifndef Asynchrony_h
#define Asynchrony_h



#include <utility/Listener.h>
#include <utility/ForwardList.h>



// Listeners for Arduino
#if defined(ARDUINO)
	#include <utility/Click.h>
	#include <utility/Interval.h>
	#include <utility/Timeout.h>
#endif



namespace Asynchrony {

	/*
		Type for added listeners identificators. Identificators are used to remove listeners.
	*/
	typedef unsigned int identificator;

	class Asynchrony {
		public:
			/*
				Method that should be call in infinite cycle in main program. For proper work no delays, sleeps and etc. functions should be used in that cycle. Instead of them create interval or timeout listeners.
				On Arduino it showld be called in loop function.
			*/
			void loop();

			/*
				Registers event listener.

				Parameters:
					Listener* listener — Pointer to event listener object that is instance of one of classes that implements class Listener.
					void (*callback)() — Function called on event triggering.
					int priority — Priority of listener. If some listeners trigger event at the same time, callback of the listener with higher priority will be called earlier. Default is 0.

				Returns:
						Asynchrony::identificator — Listener identificator.
			*/
			identificator add(Listener* listener, void (*callback)(), int priority = 0);

			/*
				Removes event listener.

				Parameters:
					Asynchrony::identificator id — Listener identificator given on listener registration.
					bool deleteListener — Whether listener object should be deleted. Default is true. If listener was created using quick method, this parameter must be true.
			*/
			void remove(identificator id, bool deleteListener = true);


			
			/*
				There are only method for quick event listeners creating below untill protected section.
			*/

			// Listeners for Arduino
			#if defined(ARDUINO)

				/*
					Creates event listener that watches button state, filters bounce and triggers event when button is in specified state.

					Parameters:
						void (*callback)() — Function called on event triggering.
						int pin — Button pin.
						bool eventState — Button state in which event triggers.
						char mode — In which mode button pin should be turned. Variants are: INPUT, INPUT_PULLUP and Asynchrony::UNDEFINED (where pin mode shouldnot be changed). Default is Asynchrony::UNDEFINED.
						unsigned long bounce — Bounce duration in microseconds. Default is 10000.

					Returns:
						Asynchrony::identificator — Listener identificator.
				*/
				identificator click(void (*callback)(), int pin, bool eventState = HIGH, char mode = UNDEFINED, unsigned long bounce = Click::DEFAULT_BOUNCE);

				/*
					Creates event listener that infinitely triggers events on the same time interval.

					Parameters:
						void (*callback)() — Function called on event triggering.
						unsigned long time — Interval duration in units specified in timeUnit parameter.
						char timeUnit — Unit in which time parameter is specified. Variants: Asynchrony::MICROSECOND, Asynchrony::MILLISECOND and Asynchrony::SECOND. Default is Asynchrony::MILLISECOND.

					Returns:
						Asynchrony::identificator — Listener identificator.
				*/
				identificator interval(void (*callback)(), unsigned long time, char timeUnit = MILLISECOND);

				/*
					Creates event listener that triggers single event after specified time runs out. After triggering listener is removed.

					Parameters:
						void (*callback)() — Function called on event triggering.
						unsigned long time — Interval duration in units specified in timeUnit parameter.
						char timeUnit — Unit in which time parameter is specified. Variants: Asynchrony::MICROSECOND, Asynchrony::MILLISECOND and Asynchrony::SECOND. Default is Asynchrony::MILLISECOND.

					Returns:
						Asynchrony::identificator — Listener identificator.
				*/
				identificator timeout(void (*callback)(), unsigned long time, char timeUnit = MILLISECOND);

			#endif

		protected:
			// Structure for containing listener in added listeners list.
			struct ListenerItem {
				Listener* listener;
				void (*callback)();
				int priority;
				identificator id;
			};

			// Added listeners list in priority descending order.
			ForwardList<ListenerItem> listeners = ForwardList<ListenerItem>();

			// Number of last given identificator
			identificator lastIdentificator = 0;

			/*
				Returns new untaken identificator
			*/
			identificator getIdentificator();
	};

}



extern Asynchrony::Asynchrony Asyn;



#endif