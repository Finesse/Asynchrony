/*
	Implement this class to create custom event listeners.
*/

#ifndef Asynchrony_Listener_h
#define Asynchrony_Listener_h



namespace Asynchrony {

	class Listener {
		public:
			/*
				Called in every moment. Must check whether event has happened.

				Parameters:
					bool *selfDestruct — Points to boolean which is default `false`. If set `true` event listener will be removed and is's object will be deleted.

				Returns:
					bool — Whether event has happened.
			*/
			virtual bool check(bool *selfDestruct) = 0;
	};

}



#endif