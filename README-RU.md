Документация на языках: [english](README.md), [русский](README-RU.md).

# Что это?

Asynchrony это инструмент для привязки действий к различным событиям с помощью создания слушателей.

Используя Asynchrony вы можете:
* Создавать слушатели, то есть назначать действие (выполнение любой функции) событию (например, нажатию кнопки).
* Удалять слушатели.

Некоторые слушатели событий включены ([список слушателей](#Список-слушателей)):
* Слушатели для Arduino.

Также вы можете создавать собственные слушатели.

Этот инструмент не зависит от платформы. Некоторые слушатели работают только на определённых платформах, но они включаются в проект только если поддерживаются платформой.


# Как установить

1. Скачать библиотеку. Это можно сделать, нажав кнопку "Download ZIP" справа.
2. Установить библиотеку. В Arduino IDE: верхнее меню — Эскиз — Импорт библиотек... — Добавить библиотеку — выбрать скачанный архив или папку с библиотекой.
3. Подключить библиотеку. В Arduino IDE: верхнее меню — Эскиз — Импорт библиотек... — — Asynchrony.


# Как пользоваться

## Пример для быстрого старта

	// Для Arduino

	#include <Asynchrony.h> // Подключаем библиотеку
	using namespace Asynchrony;

	#define BUTTON_PIN 2 // Один контакт кнопки подключен к этому пину, другой к земле
	#define LED_PIN 3 // К этому контакту подключен светодиод

	// Действие, вызываемое при нажатии кнопки
	void onClick() {
		static bool state = false;
		state = !state;
		digitalWrite(LED_PIN, state);
	}

	void setup() {
		Asyn.click(onClick, BUTTON_PIN, LOW, INPUT_PULLUP); // Привязываем функцию `onClick` нажатию кнопки
	}

	void loop() {
		Asyn.loop(); // Этот метод должен вызываться постоянно для работы инструмента
	}

[Полный список слушателей событий.](#Список-слушателей)


## Подробное описание

Первым делом нужно включить в программу заголовочный файл библиотеки:

	#include <Asynchrony.h>

Каждый файл библиотеки уже включен, поэтому не нужно прописывать дополнительные `#include`. Не беспокойтесь, это не повлияет на размер скомпилированной программы, потому что компилятор включает в неё только те классы, функции, методы и т.д., которые используются в программе.

Библиотека располагается в пространстве имён `Asynchrony`, поэтому по-желанию можно подключить его:

	using namespace Asynchrony

Все действия выполняются через глобальный объект `Asyn`, который является экземпляром класса `Asynchrony::Asynchrony`.

Затем добавьте вызов метода `Asyn.loop()` в бексонечный цикл в главной части программы. Пример для Arduino:

	// ...

	void loop() {
		Asyn.loop();
	}

**Никогда не используйте delay'и, sleep'ы и т.п.**. Вместо них используйте слушатели [Interval](#interval) или [Timeout](#timeout). Иначе слушатели будут работать некорректно и с задержками.

#### Добавление слушателей событий

	Asynchrony::identificator Asyn.add(Asynchrony::Listener* listener, void (*callback)(), int priority = 0)

Параметры:
* `Asynchrony::Listener* listener` Указатель на объект слушателя, который является экземпляром одного из классов, наследующего класс `Asynchrony::Listener`. [Список готовых слушателей](#Список-слушателей).
* `void (*callback)()` Функция, которая вызывается при срабатывании события.
* `int priority` Приоритет слушателя. Если несколько слушателей сработали одновременно, то чем выше приоритет, тем раньше вызовется приклеплённая функция. По-умолчанию, 0.

Returns: `Asynchrony::identificator` Идентификатор слушателя, который используется для удаления слушателя.

Пример:
	
	// Для Arduino

	#include <Asynchrony.h>
	using namespace Asynchrony;

	void blink() {
		static bool state = false;
		digitalWrite(3, state);
		state = !state;
	}

	void setup() {
		Asyn.add(new Interval(1000), blink); // Мигать каждую секунду
	}

	void loop() {
		Asyn.loop();
	}

Некоторые слушатели событий можно привязать, используя упрощённые методы (полный список можно посмотреть в [списке слушателей](#Список-слушателей)):

	// For Arduino

	#include <Asynchrony.h>
	using namespace Asynchrony;

	void blink() {
		static bool state = false;
		digitalWrite(3, state);
		state = !state;
	}

	void setup() {
		Asyn.interval(blink, 1000); // Мигать каждую секунду
	}

	void loop() {
		Asyn.loop();
	}

#### Удаление слушателей событий

	void Asyn.remove(Asynchrony::identificator id, bool deleteListener = true)

Параметры:
* `Asynchrony::identificator id` Идентификатор слушателя, полученный при добавлении слушателя.
* `bool deleteListener` Нужно ли удалять объект слушателя и очищать от него память. По-умалчанию, `true`. Если слушатель создан через упрощённый метод, то этот параметр должен обязательно иметь значение `true`, иначе память будет оставаться занятой, а указатель на неё будет потерян.

Пример:

	// Для Arduino

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
		blinking = Asyn.interval(blink, 1000); // Мигать каждую секунду
		Asyn.timeout(stopBlinking, 10000); // Остановить мигание после 10 секунд
	}

	void loop() {
		Asyn.loop();
	}

#### Создание собственного слушателя события

Создайте класс, наслудующий `Asynchrony::Listener`, чтобы создать собственный слушатель. Он содержит только один метод, который нужно реализовать:
	
	virtual bool check(bool *selfDestruct)

Он вызывается постоянно при вызове `Asyn.loop()`. Он должен проверять, произошло ли событие. Параметры:
* `bool *selfDestruct` Указатель на булеву переменную, которая по-умолчанию равна `false`. Если установить её значение `true`, то слушатель и его объект будут удалены.

Возвращает: `bool` Произошло ли наблюдаемое событие.

Пример:

	#include <Asynchrony.h>
	using namespace Asynchrony;

	// Слушатель, который проверяет, меньше ли нуля значение переменной
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

	Asyn.add(new NegativeListener(&var), action);

#### Проверка, существует ли слушатель с указанным идентификатором

	bool Asyn.check(Asynchrony::identificator id)

Пример:

	#include <Asynchrony.h>
	using namespace Asynchrony;

	void action() {
		// ...
	}

	identificator listener = Asyn.timeout(action, 2000);

	// Некоторое время спустя

	if(Asyn.check(identificator)) {
		// Timeout hasn't passed
	}


## Список слушателей

* [Click](#click)
* [Interval](#interval)
* [Timeout](#timeout)

### Click

Наблюдает за состоянием кнопки, отфильтровывает дребезг контактов и вызывает срабатывание, если кнопка находится в нужном состоянии.

Платформа: Arduino.

	Asynchrony::Click(int pin, bool eventState = HIGH, char mode = Asynchrony::UNDEFINED, unsigned long bounce = Asynchrony::Click::DEFAULT_BOUNCE)

Параметры:
* `int pin` Пин кнопки.
* `bool eventState` Состояние кнопки, в котором должно происходить срабатывание.
* `char mode` В какой режим нужно предварительно переключить пин кнопки. Варианты: `INPUT` (прямой вход), `INPUT_PULLUP` (вход с подтягивающим резистором) и `Asynchrony::UNDEFINED` (режим не изменяется). По-умолчанию, `Asynchrony::UNDEFINED`.
* `unsigned long bounce` Длительность дребезга контактов в микросекундах. По-умолчанию, 10000.

Создание с помощью упрощённого метода:

	Asynchrony::identificator Asyn.click(void (*callback)(), int pin, bool eventState = HIGH, char mode = Asynchrony::UNDEFINED, unsigned long bounce = Asynchrony::Click::DEFAULT_BOUNCE)

### Interval

Бесконечно вызывает срабатывания через равные промежутки времени.

Платформа: Arduino.

	Asynchrony::Interval(unsigned long time, char timeUnit = Asynchrony::MILLISECOND)

Параметры:
* `unsigned long time` Интервал между срабатываниями, выраженный в единицах измерения, указанных в параметре `timeUnit`.
* `char timeUnit` Единица измерения, в которой указан параметр `time`. Варианты: `Asynchrony::MICROSECOND` (микросекунда), `Asynchrony::MILLISECOND` (миллисекунда) и `Asynchrony::SECOND` (секунда). По-умолчанию, `Asynchrony::MILLISECOND`.

Создание с помощью упрощённого метода:

	Asynchrony::identificator Asyn.interval(void (*callback)(), unsigned long time, char timeUnit = Asynchrony::MILLISECOND)

### Timeout

Вызывает одно срабатывание через заданный промежуток времени, после чего самоуничтожается.

Платформа: Arduino.

	Asynchrony::Timeout(unsigned long time, char timeUnit = Asynchrony::MILLISECOND)

Параметры:
* `unsigned long time` Время до срабатывания, выраженное в единицах измерения, указанных в параметре `timeUnit`.
* `char timeUnit` Единица измерения, в которой указан параметр `time`. Варианты: `Asynchrony::MICROSECOND` (микросекунда), `Asynchrony::MILLISECOND` (миллисекунда) и `Asynchrony::SECOND` (секунда). По-умолчанию, `Asynchrony::MILLISECOND`.

Создание с помощью упрощённого метода:

	Asynchrony::identificator Asyn.timeout(void (*callback)(), unsigned long time, char timeUnit = Asynchrony::MILLISECOND)


# Лицензия

MIT (делайте, что хотите).