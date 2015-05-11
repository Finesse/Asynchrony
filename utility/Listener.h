/*
	Implement this class to create custom event listeners.
*/

#ifndef Asynchrony_Listener_h
#define Asynchrony_Listener_h



namespace Asynchrony {

	class Listener {
		public:
			/*
				Must check whether event has happened.

				Parameters:
					bool *selfDestruct — Set the value of variable that this pointer points true to remove event listener from events list.

				Returns:
					bool — Whether event has happened.
			*/
			virtual bool check(bool *selfDestruct) = 0;
	};

}



#endif