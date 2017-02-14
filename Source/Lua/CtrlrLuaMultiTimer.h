#ifndef __CTRLR_LUA_MULTI_TIMER__
#define __CTRLR_LUA_MULTI_TIMER__

#ifdef _WIN32
#pragma warning(disable:4100)
#endif // _WIN32
#include "luabind/object_fwd.hpp"
extern "C"
{
#include "lua.h"
}

struct LuaTimerCallback
{
	bool isValid;
	luabind::object o;
};

//==============================================================================
/** \brief A class for timers.

*/
class CtrlrLuaMultiTimer : public MultiTimer
{
	public:
		/** @brief Internal

		*/
		CtrlrLuaMultiTimer();

		/** @brief Internal

		*/
		~CtrlrLuaMultiTimer();

		/** @brief Internal

		*/
		static void wrapForLua(lua_State *L);

		/** @brief Used internaly by the class, not exported to LUA

			@param	timerId		numeric id of the timer
		*/
		void timerCallback(int timerId);

		/** @brief Set a LUA function as a callback for a timer

			@param	timerId		numeric id of the timer
			@param	callback	LUA function as a luabind object
		*/
		void setCallback (const int timerId, luabind::object callback);

		/** @brief Starts a timer with a given interval in milliseconds

			@param	timerId		numeric id of the timer
			@param	interval	time interval in milliseconds
		*/
		void startTimer (const int timerId, const int interval);

		/** @brief Check if a callback for a given timer has been registered

			@param	timerId		numeric id of the timer
		*/
		const bool isRegistered(const int timerId);

		/** @brief Stop a timer

			@param	timerId		numeric id of the timer
		*/
		void stopTimer (const int timerId);

		/** @brief Check if a timer has been started

			@param	timerId		numeric id of the timer
		*/
		const bool isTimerRunning (const int timerId);

		/** @brief Get an interval used for a timer

			@param	timerId		numeric id of the timer
		*/
		const int getTimerInterval(const int timerId);

	private:
		HashMap <int, LuaTimerCallback> callbacks;
};

#endif
