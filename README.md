Documentation on languages: [english](README.md), [русский](README-RU.md).

# What is it?

Asynchrony is tool for hooking actions to different events by using listeners.

Using Asynchrony you can:
* Add listeners that means assigning action (any function you like) to event (for example, button pressing).
* Remove listener.

Some event listeners are included ([listeners list](#event-listeners)):
* Arduino listeners.

You can also create your own listeners.

This tool is planform independed. Some listeners are platform depended but they are included only if supported by platform.


# How to install

1. Download. Click "Download ZIP" on the right side to do it.
2. Install. In Arduino IDE: top menu — Sketch — Import Library... — Add Library — choose downloaded ZIP or library directory.
3. Import. In Arduino IDE: top menu — Sketch — Import Library... — Asynchrony.


# How to use

## Quick start example

```c++
// For Arduino

#include <Asynchrony.h> // Including library
using namespace Asynchrony;

#define BUTTON_PIN 2
#define LED_PIN 3

void onClick() {
	static bool state = false;
	state = !state;
	digitalWrite(LED_PIN, state);
}

void setup() {
	Asyn.click(onClick, BUTTON_PIN, LOW, INPUT_PULLUP); // Hook `onClick` action to button click event
}

void loop() {
	Asyn.loop(); // It must be called constantly for tool operation
}
```

[Full event listeners list.](#event-listeners)


## Details

First include library header to your program:

```c++
#include <Asynchrony.h>
```

Each library file is already included so there is no need to add extra `#include`. Don't worry, is won't take effect on size of compiled program bacause compilator includes only used classes, functions, method, etc.

Library is contained in namespace `Asynchrony` so you can optionaly add this namespace:

```c++
using namespace Asynchrony
```

Each action is done through the global object `Asyn` which is instance of `Asynchrony::Asynchrony` class.

Than add calling of method `Asyn.loop()` in infinite cycle in main program. Example for Arduino:

```c++
// ...

void loop() {
	Asyn.loop();
}
```

**Never use any delays, sleeps and etc**. Instead of them use [Interval](#interval) or [Timeout](#timeout) listeners. Otherwise listeners will work not exacly and with delays.

#### Adding event listeners

```c++
Asynchrony::identificator Asyn.add(Asynchrony::Listener* listener, void (*callback)(), int priority = 0)
```

Parameters:
* `Asynchrony::Listener* listener` Pointer to event listener object that is instance of one of classes implementing class `Asynchrony::Listener`. [Ready event listeners list](#event-listeners).
* `void (*callback)()` Function called on event triggering.
* `int priority` Priority of listener. If some listeners trigger event at the same time, callback of the listener with higher priority will be called earlier. Default is 0.

Returns: `Asynchrony::identificator` Listener identificator that is used to remove listener.

Example:

```c++
// For Arduino

#include <Asynchrony.h>
using namespace Asynchrony;

void blink() {
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
```

Some events listeners can be hooked using quick methods (full documentation is in [event listeners list](#event-listeners)):

```c++
// For Arduino

#include <Asynchrony.h>
using namespace Asynchrony;

void blink() {
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
```

#### Removing event listeners

```c++
void Asyn.remove(Asynchrony::identificator id, bool deleteListener = true)
```

Parameters:
* `Asynchrony::identificator id` Listener identificator given on listener adding.
* `bool deleteListener` Whether listener object should be deleted and memory should be released. Default is `true`. If listener was created using quick method, this parameter must be `true`, otherwise memory won't be released and pointer to it will be lost.

Example:

```c++
// For Arduino

#include <Asynchrony.h>
using namespace Asynchrony;

identificator blinking;

void blink() {
	static bool state = false;
	digitalWrite(3, state);
	state = !state;
}

void stopBlinking() {
	Asyn.remove(blinking);
}

void setup() {
	blinking = Asyn.interval(blink, 1000); // Blink every second
	Asyn.timeout(stopBlinking, 10000); // Stops blinking after 10 seconds
}

void loop() {
	Asyn.loop();
}
```

#### Creating custom event listener

Create class implementing `Asynchrony::Listener` to create your own listener. It contains only one method to implement:

```c++	
virtual bool check(bool *selfDestruct)
```

It is called in every moment by `Asyn.loop()` and it should check whether event has happened. Parameters:
* `bool *selfDestruct` Points to boolean which is default `false`. If set `true` event listener will be removed and is's object will be deleted.

Returns: `bool` Whether event has happened.

Example:

```c++
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
};

// ...

int var = 0;

void action() {
	// ...
}
```

Asyn.add(new NegativeListener(&var), action);

#### Checking whether listener with specified identificator exists

```c++
bool Asyn.check(Asynchrony::identificator id)
```

Example:

```c++
#include <Asynchrony.h>
using namespace Asynchrony;

void action() {
	// ...
}

identificator listener = Asyn.timeout(action, 2000);

// Some time later

if(Asyn.check(identificator)) {
	// Timeout hasn't passed
}
```


## Event listeners

* [Click](#click)
* [Interval](#interval)
* [Timeout](#timeout)

### Click

Watches button state, filters bounce and triggers event when button is in specified state.

Platforms: Arduino.

```c++
Asynchrony::Click(int pin, bool eventState = HIGH, char mode = Asynchrony::UNDEFINED, unsigned long bounce = Asynchrony::Click::DEFAULT_BOUNCE)
```

Parameters:
* `int pin` Button pin.
* `bool eventState` Button state in which event triggers.
* `char mode` In which mode button pin should be turned. Variants are: `INPUT`, `INPUT_PULLUP` and `Asynchrony::UNDEFINED` (where pin mode shouldn't be changed). Default is `Asynchrony::UNDEFINED`.
* `unsigned long bounce` Bounce duration in microseconds. Default is 10000.

Quick adding:

```c++
Asynchrony::identificator Asyn.click(void (*callback)(), int pin, bool eventState = HIGH, char mode = Asynchrony::UNDEFINED, unsigned long bounce = Asynchrony::Click::DEFAULT_BOUNCE)
```

### Interval

Infinitely triggers events on the same time interval.

Platforms: Arduino.

```c++
Asynchrony::Interval(unsigned long time, char timeUnit = Asynchrony::MILLISECOND)
```

Parameters:
* `unsigned long time` Interval duration in units specified in `timeUnit` parameter.
* `char timeUnit` Unit in which `time` parameter is specified. Variants: `Asynchrony::MICROSECOND`, `Asynchrony::MILLISECOND` and `Asynchrony::SECOND`. Default is `Asynchrony::MILLISECOND`.

Quick adding:

```c++
Asynchrony::identificator Asyn.interval(void (*callback)(), unsigned long time, char timeUnit = Asynchrony::MILLISECOND)
```

### Timeout

Triggers single event after specified time runs out. After triggering listener is removed.

Platforms: Arduino.

```c++
Asynchrony::Timeout(unsigned long time, char timeUnit = Asynchrony::MILLISECOND)
```

Parameters:
* `unsigned long time` Interval duration in units specified in `timeUnit` parameter.
* `char timeUnit` Unit in which `time` parameter is specified. Variants: `Asynchrony::MICROSECOND`, `Asynchrony::MILLISECOND` and `Asynchrony::SECOND`. Default is `Asynchrony::MILLISECOND`.

Quick adding:

```c++
Asynchrony::identificator Asyn.timeout(void (*callback)(), unsigned long time, char timeUnit = Asynchrony::MILLISECOND)
```


# License

MIT (do anything you want).
