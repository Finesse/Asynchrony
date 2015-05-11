Documentation on languages: [english](README.md), [русский](README-RU.md).

# What is it?

Asynchrony is tool for hooking actions to different events by using listeners.

Using asynchrony you can:
* Add listeners that means assigning action (any function you like) to event (for example, key pressing).
* Remove listener.

Some event listeners are included ([listeners list](#event_listeners)):
* Arduino listeners.

You can create your own listeners.

This tool is planform indepanded. Some listeners are platform depanded but they are included only if supported by platform.


# How to insall

1. Download. Click "Download ZIP" on the right side to do it.
2. Install. In Arduino IDE: top menu — Sketch — Import Library... — Add Library — choose downloaded ZIP or library directory.
3. Import. In Arduino IDE: top menu — Sketch — Import Library... — Asynchrony.


# How to use

First include library header to your program:

	#include <Asynchrony.h>

Each library file is already included so there is no need to add extra `#include`. Don't worry, is won't take effect on size of compiled program bacause compilatore includes only used classes, functions, method, etc.

Library is contained in namespace `Asynchrony` so yiu can optionaly add this namespace:

	using namespace Asynchrony

Each action is done through the global object `Asyn` which is instance of `Asynchrony::Asynchrony` class.

Than add calling of method `Asyn.loop()` in infinite cycle in main program. No delays, sleeps and etc. should be usen in this cycle. Instead of them use [Interval](#interval) and [Timeout](#timeout) listeners.

Example for Arduino:

	// ...

	void loop() {
		// ...

		Asyn.loop();

		// ...
	}

#### Adding event

	Asynchrony::identificator Asyn.add(Asynchrony::Listener* listener, void (*callback)(), int priority = 0)

Parameters:
* `Asynchrony::Listener* listener` Pointer to event listener object that is instance of one of classes implementing class `Asynchrony::Listener`. [Event listeners list](#event_listeners).
* `void (*callback)()` Function called on event triggering.
* `int priority` Priority of listener. If some listeners trigger event at the same time, callback of the listener with higher priority will be called earlier. Default is `0`.

Returns: `Asynchrony::identificator` Listener identificator that is used to remove listener.

Example:
	
	// For Arduino

	#include <Asynchrony.h>
	using namespace Asynchrony;

	function blink() {
		static bool state = false;
		digitalWrite(3, state);
		state = !state;
	}

	void setup() {
		Asyn.add(new Interval(1000), blink); // Blink every second
	}

	void loop() {
		Asyn.loop();
	}

Some events listeners can be hooked using quick methods (full documentation is in [event listeners list](#event_listeners)):

	// For Arduino

	#include <Asynchrony.h>
	using namespace Asynchrony;

	function blink() {
		static bool state = false;
		digitalWrite(3, state);
		state = !state;
	}

	void setup() {
		Asyn.interval(blink, 1000); // Blink every second
	}

	void loop() {
		Asyn.loop();
	}

#### Removing events

	void Asyn.remove(Asynchrony::identificator id, bool deleteListener = true)

Parameters:
* `Asynchrony::identificator id` Listener identificator given on listener adding.
* `bool deleteListener` Whether listener object should be deleted and memory should be freed. Default is true. If listener was created using quick method, this parameter must be true, otherwise memory won't be freed and pointer to it will be lost.

Example:

	// For Arduino

	#include <Asynchrony.h>
	using namespace Asynchrony;

	identificator blinking;

	function blink() {
		static bool state = false;
		digitalWrite(3, state);
		state = !state;
	}

	function stopBlinking() {
		Asyn.remove(blinking);
	}

	void setup() {
		blinking = Asyn.interval(blink, 1000); // Blink every second
		Asyn.timeout(stopBlinking, 10000); // Stops blinking after 10 seconds
	}

	void loop() {
		Asyn.loop();
	}

#### Creating custom event listener

Create class implementing `Asynchrony::Listener` to create your own listener.

`Asynchrony::Listener` contains only one method to implement:
	
	virtual bool check(bool *selfDestruct)

It is called in every moment by `Asyn.loop()` and it should check whether event has happened. Parameters:
* `bool *selfDestruct` — Points to boolean which is default `false`. If set `true` event listener will be removed and is's object will be deleted.

Returns: `bool` Whether event has happened.

Example:

	#include <Asynchrony.h>
	using namespace Asynchrony;

	// Listeners checkes whether variable is below zero.
	class NegativeListener : public Listener {
		public:
			NegativeListener(int *variable) {
				variableToWatch = variable;
			}

			virtual bool check(bool *selfDestruct) {
				if(*variableToWatch < 0)
					return true;
				else
					return false;
			}

		protected:
			int *variableToWatch;
	}

	// ...

	int var = 0;

	function action() {
		// ...
	}

	Asyn.add(new NegativeListener(&var), action);


## Event listeners

Coming soon...