#ifndef __CTRLR_LUA_OBJECT__
#define __CTRLR_LUA_OBJECT__

#include "stdafx.h"
#include "CtrlrLuaObjectWrapper.h"

//==============================================================================
/** \brief A class that defines standard access methods for all Ctrlr-LUA based objects like Panels, Modulators, Components, MidiMessages etc.

*/
class CtrlrLuaObject
{
	public:
		/** @brief Internal

		*/
		CtrlrLuaObject();

		/** @brief Internal

		*/
		virtual ~CtrlrLuaObject();

		/** @brief This method is an internal method overloaded by any class that wants to live in the LUA state
			@see CtrlrPanel
			@see CtrlrModulator
			@see CtrlrComponent
			@see CtrlrPanelEditor
			@see CtrlrMidiMessage

			@param	propertyName	name of the property to fetch
			@param	newValue		value to set
			@param	isUndoable		the handling class can use this to find out if this can be an undo transaction
		*/

		virtual void setProperty (const Identifier &propertyName, const var &newValue, const bool isUndoable=false)=0;

		/** @brief This method is an internal method overloaded by any class that wants to live in the LUA state
			@see CtrlrPanel
			@see CtrlrModulator
			@see CtrlrComponent
			@see CtrlrPanelEditor
			@see CtrlrMidiMessage

			@param	propertyName	name of the property to fetch
		*/
		virtual const var &getProperty (const Identifier &propertyName) const = 0;

		/** @brief Remove a property

			@param	propertyName	name of the property to remove
		*/
		virtual void removeProperty (const Identifier &propertyName);

		virtual ValueTree &getObjectTree() = 0;

		/** @brief Internal

		*/
		virtual int getPropertyInt(const String &propertyName);
		virtual double getPropertyDouble(const String &propertyName);
		virtual const String getPropertyString(const String &propertyName);
		virtual void setPropertyColour(const String &propertyName, const Colour value);
		virtual void setPropertyDouble(const String &propertyName, const double value);
		virtual void setPropertyInt(const String &propertyName, const int value);
		virtual void setPropertyString(const String &propertyName, const String &value);
		static void wrapForLua(lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrLuaObject)
};

#endif
