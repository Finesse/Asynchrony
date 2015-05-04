#ifndef Asynchrony_Listener_h
#define Asynchrony_Listener_h



namespace Asynchrony {

	class Listener {
		public:
			// Проверяет, произошло ли событие (с возможностью вернуть флаг самоуничтожения)
			virtual bool check(bool *selfDestruct) = 0;
	};

}



#endif