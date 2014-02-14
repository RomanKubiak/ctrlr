#ifndef __CTRLR_LUA_OBJECT_WRAPPER__
#define __CTRLR_LUA_OBJECT_WRAPPER__


#include "JuceHeader.h"

//==============================================================================
/** \brief A wrapper class for luabind::object class

*/
class CtrlrLuaObjectWrapper
{
	public:
		CtrlrLuaObjectWrapper() {}
		CtrlrLuaObjectWrapper(luabind::object const& other)
		{
			o = other;
		}
		operator luabind::object &()
		{ 
			return o; 
		}
		operator luabind::object ()
		{ 
			return o; 
		}

		/** @brief Get the original object

			@return the luabind::object inside the wrapper
		*/
		const luabind::object &getLuabindObject() const 
		{ 
			return o; 
		}

		/** @brief Get the original object

			@return the luabind::object inside the wrapper
		*/
		const luabind::object &getObject() const
		{
			return o;
		}

		JUCE_LEAK_DETECTOR(CtrlrLuaObjectWrapper)

	private:
		luabind::object o;
};

#endif