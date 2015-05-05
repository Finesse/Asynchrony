#ifndef Asynchrony_h
#define Asynchrony_h



#include <utility/Listener.h>
#include <utility/ForwardList.h>



// Слушатели для Arduino
#if defined(ARDUINO)
	#include <utility/Click.h>
	#include <utility/Interval.h>
	#include <utility/Timeout.h>
#endif



namespace Asynchrony {

	typedef unsigned int identificator;

	class Asynchrony {
		public:
			// Метод, который нужно вызывать в функции loop ардуинки.
			void loop();

			// Регистрирует слушатель события. Параметры: слушатель, функция выполняемая при срабатывании, приоритет
			identificator add(Listener* listener, void (*callback)(), int priority = 0);

			// Убирает слушатель.
			void remove(identificator id, bool deleteListener = true);

			// Методы для быстрой привязки событий
			#if defined(ARDUINO)

				identificator click(void (*callback)(), int pin, bool eventState = HIGH, char mode = UNDEFINED, unsigned long bounce = Click::DEFAULT_BOUNCE);

				identificator interval(void (*callback)(), unsigned long time, char timeUnit = MILLISECOND);

				identificator timeout(void (*callback)(), unsigned long time, char timeUnit = MILLISECOND);

			#endif

		protected:
			// Структура, являющаяся элементом списка слушателей
			struct ListenerItem {
				Listener* listener;
				void (*callback)();
				int priority;
				identificator id;
			};

			// Список слушателей в порядке уменьшения приоритета
			ForwardList<ListenerItem> listeners = ForwardList<ListenerItem>();

			// Номер последнего выданного идентификатора
			identificator lastIdentificator = 0;

			// Выдаёт новый незанятый идентификатор
			identificator getIdentificator();
	};

}



extern Asynchrony::Asynchrony Asyn;



#endif