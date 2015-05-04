#ifndef Asynchrony_h
#define Asynchrony_h



#include <utility/Listener.h>
#include <utility/ForwardList.h>



namespace Asynchrony {

	typedef unsigned int identificator;

	class Asynchrony {
		public:
			// Регистрирует слушатель события. Параметры: слушатель, функция выполняемая при срабатывании, приоритет
			identificator addListener(Listener* listener, void (*callback)(), int priority = 0);

			// Метод, который нужно вызывать в функции loop ардуинки.
			void loop();

			// Убирает слушатель.
			void removeListener(identificator id, bool deleteListener = true);

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



#include <utility/Click.h>
#include <utility/Interval.h>
#include <utility/Timeout.h>



extern Asynchrony::Asynchrony Asyn;



#endif